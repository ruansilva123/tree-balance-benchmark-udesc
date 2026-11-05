// libs
#include <time.h>


typedef struct {
    struct timespec start;
    struct timespec end;
    double milliseconds;
} ExecutionTime;

typedef struct {
    ExecutionTime population;
    ExecutionTime deletion;
} TreeExecutionData;


void set_dataset_size(int* dataset_size);

void random_numbers_set(int** random_numbers, int dataset_size);

void start_execution_time(ExecutionTime* execution_time);

void stop_execution_time(ExecutionTime* execution_time);

void log_results(const char* tree_name, TreeExecutionData* execution_data);