--TEST--
define_var() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
class MinhoObject{}
define_var();
var_dump($site);
var_dump($m_lists);
var_dump($minhoObj);

?>
--EXPECT--
string(13) "www.iminho.me"