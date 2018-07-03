#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include "php_const.h"

PHP_MINIT_FUNCTION(php_const)
{

    REGISTER_STRINGL_CONSTANT("__SITE__", "www.imonho.me", 13, CONST_PERSISTENT);
    REGISTER_NS_STRINGL_CONSTANT("Minho", "__SITE__", "iminho.me",9, CONST_CS|CONST_PERSISTENT);
    return SUCCESS;
}