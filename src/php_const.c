#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include "php_const.h"

void minho_hash_destroy(HashTable *ht)
{
    zend_string *key;
    zval *element;
    //检查HashTable是否分配了内存空间
    if((ht)->u.flags & HASH_FLAG_INITIALIZED){
        //循环HashTable
        ZEND_HASH_FOREACH_STR_KEY_VAL(ht,key,element){
            //判断是否存在Key，如果存在则释放
            if(key){
                free(key);
            }
            switch(Z_TYPE_P(element)){
                //如果是字符串，则直接释放掉
                case IS_STRING: free(element);break;
                //如果是数组，递归调用释放
                case IS_ARRAY: minho_hash_destroy(Z_ARRVAL_P(element));break;
            }
        }ZEND_HASH_FOREACH_END();
        free(HT_GET_DATA_ADDR(ht));
    }
    free(ht);
}
//释放数组和字符串
static void minho_entry_dtor_persistent(zval *zvalue)
{
    if (Z_TYPE_P(zvalue) == IS_ARRAY) {
        minho_hash_destroy(Z_ARRVAL_P(zvalue));
    } else if (Z_TYPE_P(zvalue) == IS_STRING) {
        zend_string_release(Z_STR_P(zvalue));
    }
}

PHP_MINIT_FUNCTION(php_const)
{
    zend_constant c;
    zend_string *key;
    zval value;
    //初始化驻留内存的数组
    ZVAL_NEW_PERSISTENT_ARR(&c.value);
    //初始化这个数组
    zend_hash_init(Z_ARRVAL(c.value),0,NULL,(dtor_func_t)minho_entry_dtor_persistent,1);

    add_index_long(&c.value,0,100);
    key = zend_string_init("site",4,1);
    ZVAL_STR(&value,zend_string_init("www.iminho.me",13,1));
    //将定义的字符串更新到HashTable中
    zend_hash_update(Z_ARRVAL(c.value),key,&value);
    //设置标识
    c.flags = CONST_CS|CONST_PERSISTENT;
    //这是数组名
    c.name = zend_string_init("__ARR__", 7, 1);
    //
    c.module_number = module_number;
    //注册数组常量
    zend_register_constant(&c);

    REGISTER_STRINGL_CONSTANT("__SITE__", "www.imonho.me", 13, CONST_PERSISTENT);
    REGISTER_NS_STRINGL_CONSTANT("Minho", "__SITE__", "iminho.me",9, CONST_CS|CONST_PERSISTENT);

    return SUCCESS;
}

//扩展卸载的时候调用此方法
PHP_MSHUTDOWN_FUNCTION(php_const)
{
    zval *val;
    val = zend_get_constant_str("__ARR__", 7);
    minho_hash_destroy(Z_ARRVAL_P(val));
    ZVAL_NULL(val);
    return SUCCESS;
}