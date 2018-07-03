--TEST--
str_concat() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
echo str_concat("hello", "word"),"\n";
echo str_concat("hello", "hello bo56.com"),"\n";
echo str_concat(1069,"minho.com"),"\n";
?>
--EXPECT--
helloword
hello bo56.com
1069minho.com
