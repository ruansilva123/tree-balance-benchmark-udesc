// libs
#include <stdio.h>
#include <stdbool.h>
//project
#include "./validators.h"


bool validate_negative_or_zero_nuumber(int number) {
    if (number <= 0) {
        printf("Error: The number must be greater than zero.\n");
        return false;
    }
    return true;
}