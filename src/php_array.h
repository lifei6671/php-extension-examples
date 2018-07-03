#ifndef PHP_RETURN_H

#define PHP_RETURN_H

PHP_FUNCTION(array_concat);

ZEND_BEGIN_ARG_INFO(arginfo_array_concat, 0)
	ZEND_ARG_INFO(0, arr)
    ZEND_ARG_INFO(0, prefix)
ZEND_END_ARG_INFO()

#endif