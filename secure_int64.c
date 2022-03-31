// include the PHP API itself
#include <php.h>
// then include the header of your extension
#include "secure_int64.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <linux/types.h>

// register our function to the PHP API
// so that PHP knows, which functions are in this module
zend_function_entry secure_int64_functions[] = {
    PHP_FE(sint64_array_to_string, NULL)
    PHP_FE(sint64_string_to_array, NULL)
    PHP_FE(uint64_array_to_string, NULL)
    PHP_FE(uint64_string_to_array, NULL)
    
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry secure_int64_module_entry = {
    STANDARD_MODULE_HEADER,
    secure_int64_EXTNAME,
    secure_int64_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    secure_int64_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(secure_int64)


unsigned long long _parseBytes(zval *bytes) {
    long long number = 0;
    
}


PHP_FUNCTION(sint64_array_to_string) {
    long long number = 0;
    zval *bytes = NULL;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(bytes)
    ZEND_PARSE_PARAMETERS_END();
    
    if(Z_TYPE_P(bytes) == IS_ARRAY) {
        int len = zend_array_count( Z_ARR_P(bytes) );
        
        if(len > 8)
            zend_error(E_WARNING, "secure_int64 will only handle the first 8 bytes of passed array");
        
        for(int e=0;e<len;e++) {
            zval *data = zend_hash_index_find(Z_ARR_P(bytes), e);
            if(Z_TYPE_P(data) == IS_LONG) {
                long value = Z_LVAL_P(data);
                if(value >= 0 && value <=255) {
                    number <<= 8;
                    number += value;
                } else {
                    zend_error(E_WARNING, "secure_int64 expects an array containing integer values between 0 and 255");
                }
            }
        }
    }
    
    char buffer[40];
    sprintf(buffer, "%lld", number);
    ZVAL_STRING(return_value, buffer);
}

PHP_FUNCTION(uint64_array_to_string) {
    unsigned long long number = 0;
    zval *bytes = NULL;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(bytes)
    ZEND_PARSE_PARAMETERS_END();
    
    if(Z_TYPE_P(bytes) == IS_ARRAY) {
        int len = zend_array_count( Z_ARR_P(bytes) );
        
        if(len > 8)
            zend_error(E_WARNING, "secure_int64 will only handle the first 8 bytes of passed array");
        
        for(int e=0;e<len;e++) {
            zval *data = zend_hash_index_find(Z_ARR_P(bytes), e);
            if(Z_TYPE_P(data) == IS_LONG) {
                long value = Z_LVAL_P(data);
                if(value >= 0 && value <=255) {
                    number <<= 8;
                    number += value;
                } else {
                    zend_error(E_WARNING, "secure_int64 expects an array containing integer values between 0 and 255");
                }
            }
        }
    }
    
    char buffer[40];
    sprintf(buffer, "%llu", number);
    ZVAL_STRING(return_value, buffer);
}

PHP_FUNCTION(sint64_string_to_array) {
    long long number = 0;
    char *buffer = "0000000000000000000000000000000000000000";
    size_t length = 0;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(buffer, length)
    ZEND_PARSE_PARAMETERS_END();
    
    sscanf(buffer, "%lld", &number);
    
    zend_array *ret = zend_new_array(8);
    RETVAL_ARR(ret);
    
    for(int e=0;e<8;e++) {
        add_next_index_long(return_value, (number >> (56-e*8)) & 0xFF);
    }
}

PHP_FUNCTION(uint64_string_to_array) {
    unsigned long long number = 0;
    char *buffer = "0000000000000000000000000000000000000000";
    size_t length = 0;
    
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(buffer, length)
    ZEND_PARSE_PARAMETERS_END();
    
    sscanf(buffer, "%llu", &number);
    
    zend_array *ret = zend_new_array(8);
    RETVAL_ARR(ret);
    
    for(int e=0;e<8;e++) {
        add_next_index_long(return_value, (number >> (56-e*8)) & 0xFF);
    }
}
