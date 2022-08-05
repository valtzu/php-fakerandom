# fakerandom extension for PHP

PHP extension that mocks `random_int` & `random_bytes` for testing purposes.


## Usage

### `random_int`
```php
fake_random_enable();
echo random_int(1, 3); // will be always 1 + (3 - 1) / 2 = 2

fake_random_disable(); 
echo random_int(1, 3); // original functionality restored
```


### `random_bytes`
```php
fake_random_enable();
echo bin2hex(random_bytes(3)); // will be always 010203 (goes up until "ff" and then "00" again) 

fake_random_disable(); 
echo bin2hex(random_bytes(3)); // original functionality restored
```
