# php secure_int64 extension
I've created this package to handle UUIDs from MFRC511 module. It uses five byte ids which can not be represented by a 32bit system. (as Raspberry Pi is 32bit.)

### Installation
```bin
$ cd ~
$ git clone https://github.com/tasoftch/php-secure-int64-extension.git
$ cd php-secure-int64-extension
$ phpize
$ ./configure --enable-secure-int64
$ make
$ sudo make install
```
This compiles the source on your machine.  
Next find the php.ini file
```bin
$ php --ini
```
Will list scanned ini files.  
Add the following line to that php.ini file:
```extension=secure_int64```
```php
<?php
var_dump( extension_loaded('secure_int64') ); // Should be true
```

### Usage
The extension adds the following functions to the global scope:
1. ```sint64_array_to_string```  
   Converts an array of maximal 8 bytes into a 64bit signed integer representation as string.
1. ```uint64_array_to_string```  
   Converts an array of maximal 8 bytes into a 64bit unsigned integer representation as string.
1. ```sint64_string_to_array```  
   Interprets a string as signed 64bit integer value and returns it as array, MSB first.
1. ```uint64_string_to_array```  
   Interprets a string as unsigned 64bit integer value and returns it as array, MSB first.

### Example
```php
<?php

?>
```