#include "ext.hpp"
#include "xhp_parser.hpp"
#include "zend.h"
#include "zend_API.h"
#include "zend_compile.h"
#include "zend_hash.h"
#include "zend_extensions.h"
#include <string>

using namespace std;

typedef zend_op_array* (zend_compile_file_t)(zend_file_handle*, int TSRMLS_DC);
typedef zend_op_array* (zend_compile_string_t)(zval*, char* TSRMLS_DC);
static zend_compile_file_t* dist_compile_file;
static zend_compile_string_t* dist_compile_string;

typedef struct {
  const char* str;
  size_t pos;
  size_t len;
} xhp_stream_t;

size_t xhp_stream_reader(xhp_stream_t* handle, char* buf, size_t len TSRMLS_DC) {
  if (len > handle->len - handle->pos) {
    len = handle->len - handle->pos;
  }
  if (len) {
    memcpy(buf, handle->str + handle->pos, len);
    buf[len] = 0;
    handle->pos += len;
    return len;
  } else {
    return 0;
  }
}

long xhp_stream_fteller(xhp_stream_t* handle TSRMLS_DC) {
  return (long)handle->pos;
}

char* xhp_parse_str(const char* code, const char* filename, int firsttok) {

  // Run it through the php superset parser which may generate valid php code...
  void* scanner;
  code_rope buf;
  xhp_extra_type extra;
  extra.firsttoken = firsttok;
  extra.xhp_tag_stack = new stack<string>();
  extra.terminated = false;

  //xhpdebug = 1;
  xhplex_init(&scanner);
  xhpset_extra(&extra, scanner);
  xhp_scan_string(code, scanner);
  int ret = xhpparse(scanner, filename, &buf);
  xhplex_destroy(scanner);
  delete extra.xhp_tag_stack;
  if (ret) {
    zend_error(E_COMPILE_ERROR, buf.c_str());
    return NULL;
  } else {
    // Create a string stream with the rewritten code and give to compile_file
//printf("%s", buf.c_str());
    return estrdup(buf.c_str());
  }
}

static zend_op_array* xhp_compile_file(zend_file_handle* f, int type TSRMLS_DC) {

  if (open_file_for_scanning(f TSRMLS_CC) == FAILURE) {
    // If opening the file fails just send it to the original func
    return dist_compile_file(f, type TSRMLS_CC);
  }

  if (f->type == ZEND_HANDLE_STREAM && f->handle.stream.interactive) {
	  fprintf(stderr, "Warning: Using PHP + XHP in interactive mode will lead to undesirable behavior; execution will not commence until EOF (^D) is encountered.\n");
  }

  // Read full program from zend stream
  std::string str;
  char buf[4096];
  size_t len;
  while (len = zend_stream_read(f, (char*)&buf, 4095 TSRMLS_CC)) {
    buf[len] = 0;
    str += buf;
  }

  // Run this through xhp? Quick heuristic to determine if we can avoid a 2nd parse stage
  bool maybe_xhp = false;
  const char* cstr = str.c_str();
  const char* ii;
  for (ii = cstr; *ii; ++ii) {
    if (*ii == '<') { // </a>
      if (ii[1] == '/') {
        maybe_xhp = 1;
        break;
      }
    } else if (*ii == '/' && ii[1] == '>') { // <a />
      maybe_xhp = 1;
      break;
    }
  }

  // If this file contains xhp run through the xhp parse stage
  const char* rewrit;
  if (maybe_xhp) {
    bool old_in_comp = CG(in_compilation);
    CG(in_compilation) = true;
    rewrit = xhp_parse_str(cstr, f->filename ? f->filename : "", 0);
    if (rewrit == NULL) {
      zend_bailout();
    }
    CG(in_compilation) = old_in_comp;
    len = strlen(rewrit);
  } else {
    rewrit = cstr;
    len = ii - cstr;
  }

  // Create a fake stream
  xhp_stream_t stream_data;
  stream_data.str = rewrit;
  stream_data.pos = 0;
  stream_data.len = len;

  zend_file_handle fake_file;
  fake_file.type = ZEND_HANDLE_STREAM;
  fake_file.opened_path = f->opened_path ? estrdup(f->opened_path) : NULL;
  fake_file.filename = f->filename;
  fake_file.free_filename = false;

  fake_file.handle.stream.handle = &stream_data;
  fake_file.handle.stream.reader = (zend_stream_reader_t)&xhp_stream_reader;
  fake_file.handle.stream.closer = NULL;
  fake_file.handle.stream.fteller = (zend_stream_fteller_t)&xhp_stream_fteller;
  fake_file.handle.stream.interactive = 0;

  zend_op_array* ret = dist_compile_file(&fake_file, type TSRMLS_CC);

  if (maybe_xhp) {
    efree(const_cast<char*>(rewrit));
  }
  return ret;
}

static zend_op_array* xhp_compile_string(zval* str, char *filename TSRMLS_DC) {

  // Cast to str
  zval tmp;
  if (str->type != IS_STRING) {
    tmp = *str;
    zval_copy_ctor(&tmp);
    convert_to_string(&tmp);
    str = &tmp;
  }

  // Rewrite the string
  char* rewrit = xhp_parse_str(str->value.str.val, "", t_PHP_FAKE_OPEN_TAG);
  if (str == &tmp) {
    zval_dtor(&tmp);
  }
  if (rewrit == NULL) {
    return NULL;
  }

  // Create another tmp zval with the rewritten PHP code and pass it to the original function
  INIT_ZVAL(tmp);
  tmp.type = IS_STRING;
  tmp.value.str.val = rewrit;
  tmp.value.str.len = strlen(rewrit);
  zend_op_array* ret = dist_compile_string(&tmp, filename TSRMLS_CC);
  zval_dtor(&tmp);
  return ret;
}

static PHP_MINIT_FUNCTION(xhp) {

  // APC has this crazy magic api you can use to avoid the race condition for when an extension overwrites
  // the compile_file function. The desired order here is APC -> xhp -> PHP, that way APC can cache the
  // file as usual.
  zend_module_entry *apc_lookup;
  zend_constant *apc_magic;
  if (zend_hash_find(&module_registry, "apc", sizeof("apc"), (void**)&apc_lookup) != FAILURE &&
      zend_hash_find(EG(zend_constants), "\000apc_magic", 11, (void**)&apc_magic) != FAILURE) {
    zend_compile_file_t* (*apc_set_compile_file)(zend_compile_file_t*) = (zend_compile_file_t* (*)(zend_compile_file_t*))apc_magic->value.value.lval;
    dist_compile_file = apc_set_compile_file(NULL);
    apc_set_compile_file(xhp_compile_file);
  } else {
    dist_compile_file = zend_compile_file;
    zend_compile_file = xhp_compile_file;
  }

  // For eval
  dist_compile_string = zend_compile_string;
  zend_compile_string = xhp_compile_string;
  return SUCCESS;
}

zend_module_entry xhp_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_XHP_EXTNAME,
	NULL,
	PHP_MINIT(xhp),
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_XHP_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_XHP
ZEND_GET_MODULE(xhp)
#endif
