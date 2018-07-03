--TEST--
say() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
var_dump(say());
?>
--EXPECT--
string(12) "Hello World!"
