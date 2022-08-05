--TEST--
Check if fakerandom is loaded
--EXTENSIONS--
fakerandom
--FILE--
<?php
echo 'The extension "fakerandom" is available';
?>
--EXPECT--
The extension "fakerandom" is available
