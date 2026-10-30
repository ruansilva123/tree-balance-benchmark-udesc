// libs
#include <stdio.h>
// project
#include "utils/utils.h"


int dataset_size = 10000;
int *random_numbers = NULL;


int main() {
    set_dataset_size(&dataset_size);
    random_numbers_set(&random_numbers, dataset_size);

    // Exibir as informações do resultado das árvores balanceadas
    return 0;
}