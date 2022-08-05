--TEST--
random_bytes() fake
--EXTENSIONS--
fakerandom
--FILE--
<?php
fake_random_enable();
echo bin2hex(random_bytes(3));
?>
--EXPECT--
010203
