--TEST--
default_value() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
var_dump(default_value("int",10));
?>
--EXPECT--
string(12) "Hello World!"
