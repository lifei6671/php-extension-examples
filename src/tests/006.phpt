--TEST--
get_size() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
var_dump(get_size("abc"));
var_dump(get_size(array(1,2)));
var_dump(get_size(10.2));
?>
--EXPECT--
string(16) "string size is 3"
string(15) "array size is 2"
string(15) "can not support"