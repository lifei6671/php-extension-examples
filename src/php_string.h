#ifndef PHP_STRING_H
#define PHP_STRING_H

PHP_FUNCTION(str_concat);

ZEND_BEGIN_ARG_INFO(arginfo_str_concat ,0)
    ZEND_ARG_INFO(0, prefix)
    ZEND_ARG_INFO(0,string)
ZEND_END_ARG_INFO()

#endif