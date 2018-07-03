#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

PHP_FUNCTION(str_concat)
{
    //定义变量接受
    zend_string *prefix,*string,*result;

//如果没有定义最新的解析方式，则沿用旧的变量解析方式
#ifndef FAST_ZPP
    if(zend_parse_parameters(ZEND_NUM_ARGS(),"SS",&prefix,&string) == FAILURE){
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(2,2)
        Z_PARAM_STR(prefix)
        Z_PARAM_STR(string)
    ZEND_PARSE_PARAMETERS_END();
#endif
    //比较变量是否是按照指定前缀开始
    if(strncmp(ZSTR_VAL(prefix),ZSTR_VAL(string),ZSTR_LEN(prefix)) == 0){
        RETURN_STR(string);
    }
    result = strpprintf(0,"%s%s",ZSTR_VAL(prefix),ZSTR_VAL(string));
    //返回拼接后的变量
    RETURN_STR(result);
}