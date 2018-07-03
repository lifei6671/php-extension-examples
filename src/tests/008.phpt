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
array(2) {
  [0]=>
  int(15021)
  ["minho_key"]=>
  string(12) "my is minho!"
}
object(MinhoObject)#1 (0) {
}
