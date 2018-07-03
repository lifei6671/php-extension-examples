--TEST--
array_concat() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
$arr = array(
    0 => '0',
    1 => '123',
    'a' => 'abc',
);  
$prefix = array(
    1 => '456',
    'a' => 'def',
);  
var_dump(array_concat($arr, $prefix));
?>
--EXPECT--
array(3) {
  [0]=>
  string(1) "0"
  [1]=>
  string(6) "456123"
  ["a"]=>
  string(6) "defabc"
}
