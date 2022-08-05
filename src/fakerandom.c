/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: valtzu                                                       |
   +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_fakerandom.h"
#include "fakerandom_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

zif_handler original_handler_random_bytes;
zif_handler original_handler_random_int;

/* {{{ string fake_random_bytes( int $length ) */
PHP_FUNCTION(fake_random_bytes)
{
	size_t length;
	char *retval;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(length)
	ZEND_PARSE_PARAMETERS_END();

	retval = emalloc(length);

	for (size_t i = 0; i < length; i++) {
	  retval[i] = (char)((i + 1) % 256);
	}

	retval[length] = '\0';

    RETURN_STRING(retval);
}
/* }}} */

/* {{{ int fake_random_int( int $min, int $max ) */
PHP_FUNCTION(fake_random_int)
{
	zend_long min;
	zend_long max;
	zend_long retval;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(min)
		Z_PARAM_LONG(max)
	ZEND_PARSE_PARAMETERS_END();

	retval = min + (max - min) / 2;

	RETURN_LONG(retval);
}
/* }}}*/

/* {{{ string fake_random_enable() */
PHP_FUNCTION(fake_random_enable)
{
    zend_function *zfn;

    zfn = zend_hash_str_find_ptr(CG(function_table), "random_int", sizeof("random_int")-1);

    if (zfn != NULL) {
        original_handler_random_int = zfn->internal_function.handler;
        zfn->internal_function.handler = PHP_FN(fake_random_int);
    }

    zfn = zend_hash_str_find_ptr(CG(function_table), "random_bytes", sizeof("random_bytes")-1);

    if (zfn != NULL) {
        original_handler_random_bytes = zfn->internal_function.handler;
        zfn->internal_function.handler = PHP_FN(fake_random_bytes);
    }
}
/* }}} */

/* {{{ string fake_random_disable() */
PHP_FUNCTION(fake_random_disable)
{
    zend_function *zfn;

    zfn = zend_hash_str_find_ptr(CG(function_table), "random_int", sizeof("random_int")-1);

    if (zfn != NULL && original_handler_random_int != NULL) {
        zfn->internal_function.handler = original_handler_random_int;
    }

    zfn = zend_hash_str_find_ptr(CG(function_table), "random_bytes", sizeof("random_bytes")-1);

    if (zfn != NULL && original_handler_random_bytes != NULL) {
        zfn->internal_function.handler = original_handler_random_bytes;
    }
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(fakerandom)
{
#if defined(ZTS) && defined(COMPILE_DL_FAKERANDOM)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(fakerandom)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "fakerandom support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ fakerandom_module_entry */
zend_module_entry fakerandom_module_entry = {
	STANDARD_MODULE_HEADER,
	"fakerandom",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,                           /* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(fakerandom),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(fakerandom),			/* PHP_MINFO - Module info */
	PHP_FAKERANDOM_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FAKERANDOM
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(fakerandom)
#endif
