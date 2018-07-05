#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_array.h"

PHP_FUNCTION(array_concat)
{
    zval *arr, *prefix, *entry, *prefix_entry, value;
    zend_string *string_key, *result;
    zend_ulong num_key;

#ifndef FAST_ZPP
    if(zend_parse_parameters(ZEND_NUM_ARGS(),"aa",&arr,&prefix) == FAILURE){
        return;
    }
#else
    ZEND_PARSE_PARAMETERS_START(2,2)
        Z_PARAM_ZVAL(arr)
        Z_PARAM_ZVAL(prefix)
    ZEND_PARSE_PARAMETERS_END();
#endif

    array_init_size(return_value,zend_hash_num_elements(Z_ARRVAL_P(arr)));

    
    //使用内置宏遍历数组
    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr),num_key,string_key,entry){
        //判断是否存在字符串的键，在prefix数组中是否存在这个键
        if(string_key && zend_hash_exists(Z_ARRVAL_P(prefix),string_key)){
            //如果arr数组中的值是字符串
            if(Z_TYPE_P(entry) == IS_STRING){
                //从prefix数组中查找指定键的值
                prefix_entry = zend_hash_find(Z_ARRVAL_P(prefix),string_key);
                if(Z_TYPE_P(prefix_entry) == IS_STRING){
                    //将两个值拼接
                    result = strpprintf(0,"%s%s",Z_STRVAL_P(prefix_entry),Z_STRVAL_P(entry));
                    //将字符串封装为zval结构
                    ZVAL_STR(&value,result);
                    //更新返回数组的值
                    zend_hash_update(Z_ARRVAL_P(return_value),string_key,&value);
                }
            }
        }else if(string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix),num_key)){
            //如果存在数字类型的索引
            if(Z_TYPE_P(entry) == IS_STRING){
                //从prefix数组中查找指定键的值
                prefix_entry = zend_hash_index_find(Z_ARRVAL_P(prefix),num_key);
                if(Z_TYPE_P(prefix_entry) == IS_STRING){
                    //将两个值拼接
                    result = strpprintf(0,"%s%s",Z_STRVAL_P(prefix_entry),Z_STRVAL_P(entry));
                    //将字符串封装为zval结构
                    ZVAL_STR(&value,result);
                    //更新返回数组的值
                    zend_hash_index_update(Z_ARRVAL_P(return_value),num_key,&value);
                }
            }
        }else if(string_key){
            //如果是字符串类型的键，但在prefix中不存在
            zend_hash_update(Z_ARRVAL_P(return_value),string_key,entry);
            //需要手动增加值的引用
            zval_add_ref(entry);
        }else{
             zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, entry);
            zval_add_ref(entry);
        }
    }ZEND_HASH_FOREACH_END();

/*
        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), num_key, string_key, entry) {
        if (string_key && zend_hash_exists(Z_ARRVAL_P(prefix), string_key)) {
            prefix_entry = zend_hash_find(Z_ARRVAL_P(prefix), string_key);
            if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING) {
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
                ZVAL_STR(&value, result);
                zend_hash_update(Z_ARRVAL_P(return_value), string_key, &value);
            }   
        } else if (string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix), num_key)){
            prefix_entry = zend_hash_index_find(Z_ARRVAL_P(prefix), num_key);
            if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING) {
                result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
                ZVAL_STR(&value, result);
                zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, &value);
            }
        } else if (string_key) {
            zend_hash_update(Z_ARRVAL_P(return_value), string_key, entry);
            zval_add_ref(entry);
        } else  {
            zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, entry);
            zval_add_ref(entry);
        }
    }ZEND_HASH_FOREACH_END();
    */
 
}