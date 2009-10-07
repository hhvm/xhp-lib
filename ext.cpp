#include "ext.hpp"
#include "xhp/xhp_preprocess.hpp"
#include "zend.h"
#include "zend_API.h"
#include "zend_compile.h"
#include "zend_operators.h"
#include "zend_hash.h"
#include "zend_extensions.h"
#include "ext/standard/info.h"
#include <string>
#include <sstream>
#include <iostream>

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

#if PHP_VERSION_ID >= 50300
ZEND_API int zend_stream_getc(zend_file_handle *file_handle TSRMLS_DC);
// This function was made static to zend_stream.c in r255174. This an inline copy of that function.
static size_t zend_stream_read(zend_file_handle *file_handle, char *buf, size_t len TSRMLS_DC) {
    if (file_handle->type != ZEND_HANDLE_MAPPED && file_handle->handle.stream.isatty) {
        int c = '*';
        size_t n;

#ifdef NETWARE
        /*
            c != 4 check is there as fread of a character in NetWare LibC gives 4 upon ^D character.
            Ascii value 4 is actually EOT character which is not defined anywhere in the LibC
            or else we can use instead of hardcoded 4.
        */
        for (n = 0; n < len && (c = zend_stream_getc(file_handle TSRMLS_CC)) != EOF && c != 4 && c != '\n'; ++n) {
#else
        for (n = 0; n < len && (c = zend_stream_getc(file_handle TSRMLS_CC)) != EOF && c != '\n'; ++n)  {
#endif
            buf[n] = (char)c;
        }
        if (c == '\n') {
            buf[n++] = (char)c;
        }

        return n;
    }
    return file_handle->handle.stream.reader(file_handle->handle.stream.handle, buf, len TSRMLS_CC);
}
#endif

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

static zend_op_array* xhp_compile_file(zend_file_handle* f, int type TSRMLS_DC) {

  if (open_file_for_scanning(f TSRMLS_CC) == FAILURE) {
    // If opening the file fails just send it to the original func
    return dist_compile_file(f, type TSRMLS_CC);
  }

  // Grab code from zend file handle
  string original_code;
#if PHP_VERSION_ID >= 50300
  if (f->type == ZEND_HANDLE_MAPPED) {
    original_code = f->handle.stream.mmap.buf;
  }
#else
  if (0);
#endif
  else {

    // Read full program from zend stream
    char read_buf[4096];
    size_t len;
    while (len = zend_stream_read(f, (char*)&read_buf, 4095 TSRMLS_CC)) {
      read_buf[len] = 0;
      original_code += read_buf;
    }
  }

  // Process XHP
  XHPResult result;
  string rewrit, error_str;
  uint32_t error_lineno;
  string* code_to_give_to_php;
  result = xhp_preprocess(original_code, rewrit, false, error_str, error_lineno);

  if (result == XHPErred) {
    // Bubble error up to PHP
    CG(in_compilation) = true;
    CG(zend_lineno) = error_lineno;
    zend_set_compiled_filename(const_cast<char*>(f->filename) TSRMLS_CC);
    zend_error(E_PARSE, "%s", error_str.c_str());
    zend_bailout();
  } else if (result == XHPRewrote) {
    code_to_give_to_php = &rewrit;
  } else {
    code_to_give_to_php = &original_code;
  }

  // Create a fake file to give back to PHP to handle
  zend_file_handle fake_file;
  fake_file.opened_path = f->opened_path ? estrdup(f->opened_path) : NULL;
  fake_file.filename = f->filename;
  fake_file.free_filename = false;

#if PHP_VERSION_ID >= 50300
  fake_file.handle.stream.isatty = 0;
  fake_file.handle.stream.mmap.pos = 0;
  fake_file.handle.stream.mmap.buf = const_cast<char*>(code_to_give_to_php->c_str());
  fake_file.handle.stream.mmap.len = code_to_give_to_php->size();
  fake_file.handle.stream.closer = NULL;
  fake_file.type = ZEND_HANDLE_MAPPED;
#else
  // This code works fine in PHP 5.3, but the MMAP method is faster
  xhp_stream_t stream_handle;
  stream_handle.str = code_to_give_to_php->c_str();
  stream_handle.pos = 0;
  stream_handle.len = code_to_give_to_php->size();

  fake_file.type = ZEND_HANDLE_STREAM;
  fake_file.handle.stream.handle = &stream_handle;
  fake_file.handle.stream.reader = (zend_stream_reader_t)&xhp_stream_reader;
#if PHP_VERSION_ID >= 50300
  fake_file.handle.stream.fsizer = (zend_stream_fsizer_t)&xhp_stream_fteller;
#else
  fake_file.handle.stream.fteller = (zend_stream_fteller_t)&xhp_stream_fteller;
#endif
  fake_file.handle.stream.closer = NULL;
  fake_file.handle.stream.interactive = 0;
#endif

  zend_op_array* ret = dist_compile_file(&fake_file, type TSRMLS_CC);
  return ret;
}

static zend_op_array* xhp_compile_string(zval* str, char *filename TSRMLS_DC) {

  // Cast to str
  zval tmp;
  char* val;
  if (str->type != IS_STRING) {
    tmp = *str;
    zval_copy_ctor(&tmp);
    convert_to_string(&tmp);
    val = tmp.value.str.val;
  } else {
    val = str->value.str.val;; 
  }

  // Process XHP
  string rewrit, error_str;
  string* code_to_give_to_php;
  uint32_t error_lineno;
  string original_code(val);
  XHPResult result = xhp_preprocess(original_code, rewrit, true, error_str, error_lineno);

  // Destroy temporary in the case of non-string input (why?)
  if (str->type != IS_STRING) {
    zval_dtor(&tmp);
  }

  if (result == XHPErred) {

    // Bubble error up to PHP
    bool original_in_compilation = CG(in_compilation);
    CG(in_compilation) = true;
    CG(zend_lineno) = error_lineno;
    zend_error(E_PARSE, "%s", error_str.c_str());
    CG(unclean_shutdown) = 1;
    CG(in_compilation) = original_in_compilation;
    return NULL;
  } else if (result == XHPRewrote) {

    // Create another tmp zval with the rewritten PHP code and pass it to the original function
    INIT_ZVAL(tmp);
    tmp.type = IS_STRING;
    tmp.value.str.val = const_cast<char*>(rewrit.c_str());
    tmp.value.str.len = rewrit.size();
    zend_op_array* ret = dist_compile_string(&tmp, filename TSRMLS_CC);
    return ret;
  } else {
    return dist_compile_string(str, filename);
  }
}

static PHP_MINIT_FUNCTION(xhp) {

  // APC has this crazy magic api you can use to avoid the race condition for when an extension overwrites
  // the compile_file function. The desired order here is APC -> XHP -> PHP, that way APC can cache the
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

static PHP_MINFO_FUNCTION(xhp) {
  php_info_print_table_start();
  php_info_print_table_row(2, "Version", PHP_XHP_VERSION);
  php_info_print_table_end();
}

ZEND_FUNCTION(__xhp_idx) {
  zval *dict, *offset;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "az", &dict, &offset) == FAILURE) {
    RETURN_NULL();
  }
  zval **value;
  switch (Z_TYPE_P(offset)) {
    case IS_RESOURCE:
      zend_error(E_STRICT, "Resource ID#%ld used as offset, casting to integer (%ld)", Z_LVAL_P(offset), Z_LVAL_P(offset));
      /* Fall Through */
    case IS_DOUBLE:
    case IS_BOOL:
    case IS_LONG:
      long loffset;
      if (Z_TYPE_P(offset) == IS_DOUBLE) {
        loffset = (long)Z_DVAL_P(offset);
      } else {
        loffset = Z_LVAL_P(offset);
      }
      if (zend_hash_index_find(Z_ARRVAL_P(dict), loffset, (void **) &value) == SUCCESS) {
        break;
      }
      zend_error(E_NOTICE, "Undefined offset: %ld", loffset);
      RETURN_NULL();

    case IS_STRING:
      if (zend_symtable_find(Z_ARRVAL_P(dict), offset->value.str.val, offset->value.str.len+1, (void **) &value) == SUCCESS) {
        break;
      }
      zend_error(E_NOTICE, "Undefined index: %s", offset->value.str.val);
      RETURN_NULL();

    case IS_NULL:
      if (zend_hash_find(Z_ARRVAL_P(dict), "", sizeof(""), (void **) &value) == SUCCESS) {
        break;
      }
      zend_error(E_NOTICE, "Undefined index: ");
      RETURN_NULL();

    default:
      zend_error(E_WARNING, "Illegal offset type");
      RETURN_NULL();
      break;
  }
  *return_value = **value;
  zval_copy_ctor(return_value);
}

ZEND_FUNCTION(xhp_preprocess_code) {
  // Parse zend params
  char *code;
  size_t code_len;
  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &code, &code_len) == FAILURE) {
    RETURN_NULL();
  }
  string rewrit, error;
  uint32_t error_line;

  // Mangle code
  string code_str(code, code_len);
  XHPResult result = xhp_preprocess(code_str, rewrit, false, error, error_line);

  // Build return code
  array_init(return_value);
  if (result == XHPErred) {
    add_assoc_string(return_value, "error", const_cast<char*>(error.c_str()), true);
    add_assoc_long(return_value, "error_line", error_line);
  } else if (result == XHPRewrote) {
    add_assoc_string(return_value, "new_code", const_cast<char*>(rewrit.c_str()), true);
  }
}

zend_function_entry xhp_functions[] = {
  ZEND_FE(__xhp_idx, NULL)
  ZEND_FE(xhp_preprocess_code, NULL)
  {NULL, NULL, NULL}
};

zend_module_entry xhp_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_XHP_EXTNAME,
  xhp_functions,
  PHP_MINIT(xhp),
  NULL,
  NULL,
  NULL,
  PHP_MINFO(xhp),
  PHP_XHP_VERSION,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_XHP
ZEND_GET_MODULE(xhp)
#endif
