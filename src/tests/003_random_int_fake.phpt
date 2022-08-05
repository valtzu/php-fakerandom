--TEST--
random_int() fake
--EXTENSIONS--
fakerandom
--FILE--
<?php
fake_random_enable();
echo random_int(1, 3);
?>
--EXPECT--
2
