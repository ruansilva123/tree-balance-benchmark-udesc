// libs
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
// project
#include "./utils.h"
#include "../validators/validators.h"


void set_dataset_size(int* dataset_size) {
    char default_dataset_size;
    int new_dataset_size;

    while (true) {
        printf("Do you want use default dataset size of 10000? (y/n): ");
        scanf(" %c", &default_dataset_size);

        if (default_dataset_size != 'n' && default_dataset_size != 'N'
            && default_dataset_size != 'y' && default_dataset_size != 'Y') {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        } else if (default_dataset_size != 'y' && default_dataset_size != 'Y') {
            printf("Enter the new dataset size: ");
            scanf("%d", &new_dataset_size);
            if (validate_negative_or_zero_nuumber(new_dataset_size)) {
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


void start_execution_time(ExecutionTime* execution_time) {
    clock_gettime(CLOCK_MONOTONIC, &execution_time->start);
}


void stop_execution_time(ExecutionTime* execution_time) {
    clock_gettime(CLOCK_MONOTONIC, &execution_time->end);
    execution_time->milliseconds = (
        (execution_time->end.tv_sec - execution_time->start.tv_sec) * 1000.0
        + (execution_time->end.tv_nsec - execution_time->start.tv_nsec) / 1e6
    );
}