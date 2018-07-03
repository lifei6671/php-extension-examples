#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_parameter.h"

PHP_FUNCTION(default_value)
{
    zval *value;
    zend_string *type;

#ifndef FAST_ZPP
    if(zend_parse_parameters(ZEND_NUM_ARGS(),"S|z",&type,&value) == FAILURE){
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1,2)
        Z_PARAM_STR(type)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL_EX(value,0,1)
    ZEND_PARSE_PARAMETERS_END();
#endif
    if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"int",3) == 0 && value == NULL){
        RETURN_LONG(0);
    }else if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"int",3) == 0 && value != NULL){
        RETURN_ZVAL(value,0,1);
    }else if(ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type),"bool",4) == 0 && value == NULL){
        RETURN_FALSE;
    }else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value != NULL) {
        RETURN_ZVAL(value, 0, 1); 
    } else if(ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type),"str",3) == 0 && value == NULL){
        RETURN_EMPTY_STRING();
    }else if(value == NULL){
        RETURN_ZVAL(value,0,1);
    }else{
        RETURN_NULL();
    }
}

