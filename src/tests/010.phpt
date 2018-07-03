--TEST--
const Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php 
var_dump(__site__);
var_dump(Minho\__SITE__);
?>
--EXPECT--
string(13) "www.imonho.me"
string(9) "iminho.me"
