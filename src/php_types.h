#ifndef PHP_TYPES_H
#define PHP_TYPES_H
//在头文件中声明方法，这样可以在snowflake.c文件中公开该方法
PHP_FUNCTION(get_size);

ZEND_BEGIN_ARG_INFO(arginfo_get_size ,0)
    ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()


#endif

