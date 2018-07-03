#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_types.h"

PHP_FUNCTION(get_size)
{
    zval *val;
    zend_string *result;
    HashTable *myht;

#ifndef FAST_ZPP
    if(zend_parse_parameters(ZEND_NUM_ARGS(),"z",&val) == FAILURE){
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(1,1)
        Z_PARAM_ZVAL_EX(val,0,1)
    ZEND_PARSE_PARAMETERS_END();
#endif

    if(Z_TYPE_P(val) == IS_STRING){
         result = strpprintf(0, "string size is %d", Z_STRLEN_P(val));
    }else if (Z_TYPE_P(val) == IS_ARRAY) {
        myht = Z_ARRVAL_P(val);
        result = strpprintf(0, "array size is %d", zend_array_count(myht));
    } else {
        result = strpprintf(0, "can not support");
    }   
    RETURN_STR(result);
}