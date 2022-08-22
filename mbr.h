#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Parition_Table{
        u_int8_t booting;
        u_int8_t cls2_123[3];
        u_int8_t file_system;
        u_int8_t cls3_123[3];
        u_int32_t start_address;
        u_int32_t size;
};