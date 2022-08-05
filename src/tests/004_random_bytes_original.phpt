--TEST--
random_bytes() original functionality
--EXTENSIONS--
fakerandom
--FILE--
<?php
echo bin2hex(random_bytes(2));
?>
--EXPECTREGEX--
^[a-f0-9]{4}$
