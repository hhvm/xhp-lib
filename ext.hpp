#pragma once
#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif
#include "php.h"

#define PHP_XHP_VERSION "1.3.1"
#define PHP_XHP_EXTNAME "xhp"

extern zend_module_entry xhp_module_entry;
#define phpext_xhp &xhp_module_entry
