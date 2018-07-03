#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_define.h"

PHP_FUNCTION(define_var)
{
    zval var_value;//储存变量值
    zend_string *var_name;//储存变量名

    zend_string *str;

/************
 * 定义字符串变量
 * 第一步，定义变量字符串
 * 第二步，定义变量名称
 * 第三步，初始化变量的值
 * 第四步，将变量绑定到zval变量上
 * 第五步，将变量值绑定到变量名称上
 * 第六步，释放变量名称
 * 第七步，释放变量值
 * *********/
    char content[14] = "www.iminho.me";
    var_name = zend_string_init("site",4,0);
    str = zend_string_init(content,sizeof(content) - 1,0);
    ZVAL_STR(&var_value,str);

    zend_set_local_var(var_name,&var_value,0);
    zend_string_release(var_name);
    ZVAL_NULL(&var_value);

/*********
 * 定义数组变量
 * 第一步，初始化变量名称
 * 第二步，初始化数组
 * 第三步，给数组赋值
 * 第四步，释放变量名
 * 第五步，释放临时变量值
 * *****/
    var_name = zend_string_init("m_lists",7,0);
    //初始化数组
    array_init(&var_value);
    //通过索引赋值
    add_index_long(&var_value,0,15021);
    //通过键赋值
    add_assoc_stringl_ex(&var_value,"minho_key",9,"my is minho!",12);
    //设置为PHP变量
    zend_set_local_var(var_name,&var_value,0);

    zend_string_release(var_name);
    ZVAL_NULL(&var_value);


/*************
 * 定义对象变量
 * 第一步，声明储存对象类的变量
 * 第二步，声明类名称
 * 第三步，获取类的实例
 * 第四步，初始化类
 * 第五步，将类变成PHP变量
 * 第六步，释放资源
 ***********/

    zend_class_entry *obj_ce;
    zend_string *class_name;
    class_name = zend_string_init("MinhoObject",11,0);
    obj_ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
    zend_string_release(class_name);
    object_init_ex(&var_value,obj_ce);
    zend_set_local_var_str("minhoObj",8,&var_value,0);
    ZVAL_NULL(&var_value);

}
