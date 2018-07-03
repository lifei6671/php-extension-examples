#ifndef PARAM_H
#define PARAM_H
//在头文件中声明方法，这样可以在snowflake.c文件中公开该方法
PHP_FUNCTION(default_value);

//定义方法的参数，arginfo_default_value 标识订单参数的名称，第二个0表示声明这个函数的返回值需要以引用的形式返回，这个参数已经在前面章节用过了。
ZEND_BEGIN_ARG_INFO(arginfo_default_value, 0)
	ZEND_ARG_INFO(0, type)
    ZEND_ARG_INFO(0,value)
ZEND_END_ARG_INFO()


#endif

