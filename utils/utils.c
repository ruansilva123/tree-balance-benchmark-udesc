// libs
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// project
#include "validators/validators.h"


void set_dataset_size(int* dataset_size) {
    char default_dataset_size;
    int new_dataset_size;

    while (1) {
        printf("Do you want use default dataset size of 10000? (y/n): ");
        scanf(" %c", &default_dataset_size);

        if (default_dataset_size != 'n' && default_dataset_size != 'N'
            && default_dataset_size != 'y' && default_dataset_size != 'Y') {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        } else if (default_dataset_size != 'y' && default_dataset_size != 'Y') {
            printf("Enter the new dataset size: ");
            scanf("%d", &new_dataset_size);
            bool is_valid = validate_negative_or_zero_nuumber(new_dataset_size);
            if (is_valid) {
                *dataset_size = new_dataset_size;
                break;
            }
        } else {
            break; 
        }
    }
}


void random_numbers_set(int** random_numbers, int dataset_size) {
    if (*random_numbers == NULL) {
        *random_numbers = (int*)malloc(dataset_size * sizeof(int));
        if (*random_numbers == NULL) {
            printf("Error: Memory allocation failed.\n");
            return;
        }
    }
    for (int i = 0; i < dataset_size; i++) {
        (*random_numbers)[i] = rand() % (dataset_size * 10);
    }
}