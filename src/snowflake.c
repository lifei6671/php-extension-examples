/* snowflake extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_snowflake.h"
#include "php_parameter.h"
#include "php_types.h"
#include "php_define.h"
#include "php_string.h"
#include "php_array.h"
#include "php_const.h"

/* {{{ void snowflake_test1()
 */
PHP_FUNCTION(snowflake_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "snowflake");
}
/* }}} */

/* {{{ string snowflake_test2( [ string $var ] )
 */
PHP_FUNCTION(snowflake_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/
//定义say方法，并返回一个字符串
PHP_FUNCTION(say)
{
	zend_string *str;
	str = strpprintf(0,"Hello World!");
	RETURN_STR(str);
}
PHP_MINIT_FUNCTION(snowflake)
{
	//这里调用了在php_const.h中声明的模块初始化需要执行的方法
	PHP_MINIT(php_const)(INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(snowflake)
{
#if defined(ZTS) && defined(COMPILE_DL_SNOWFLAKE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(snowflake)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "snowflake support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_snowflake_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_snowflake_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
//定义一个无参的参数信息
ZEND_BEGIN_ARG_INFO(arginfo_say,0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ snowflake_functions[]
 */
static const zend_function_entry snowflake_functions[] = {
	PHP_FE(snowflake_test1,		arginfo_snowflake_test1)
	PHP_FE(snowflake_test2,		arginfo_snowflake_test2)
	PHP_FE(say,					arginfo_say) //公开方法
	PHP_FE(default_value,		arginfo_default_value)
	PHP_FE(get_size,			arginfo_get_size)
	PHP_FE(define_var,			NULL)
	PHP_FE(str_concat,			arginfo_str_concat)
	PHP_FE(array_concat,		arginfo_array_concat)
	PHP_FE_END
};
/* }}} */

/* {{{ snowflake_module_entry
 */
zend_module_entry snowflake_module_entry = {
	STANDARD_MODULE_HEADER,
	"snowflake",					/* Extension name */
	snowflake_functions,			/* zend_function_entry */
	PHP_MINIT(snowflake),			/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(snowflake),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(snowflake),			/* PHP_MINFO - Module info */
	PHP_SNOWFLAKE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SNOWFLAKE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(snowflake)
#endif
