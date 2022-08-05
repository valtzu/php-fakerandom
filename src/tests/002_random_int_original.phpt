--TEST--
random_int() original functionality
--EXTENSIONS--
fakerandom
--FILE--
<?php
echo random_int(10, 19);
?>
--EXPECTREGEX--
^\d\d$
