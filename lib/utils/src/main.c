#include "utils.h"

int main() {

    size_t result_size = 0; //сколько сотрудников вывести на каждую категорию
    printf("Enter num of result:\n");
    scanf("%zu", &result_size);

    size_t lenght = 0; //количество должностей
    size_t size = 0;  // количество сотрудников
    static const char *file_name = "database.txt";

    Employee **data = NULL; 
    data = read_data_from_file(file_name, &size);
    if(data == NULL){
        printf("Error read from file\n");
        return EXIT_FAILURE;
    }

    Position *result = NULL;
    result = get_worker_information(data, &size, &result_size, &lenght);
    if(result == NULL){
        printf("Error get\n");
        free_array_employee(data, &size);
        return EXIT_FAILURE;
    }

    printf("\nResult:\n\n");
    printf("Differen positions: %zu\n", lenght);
    for(size_t i = 0; i < lenght; ++i){
        print_position(&result[i]);
    }

    free_array_employee(data, &size);
    free_array_position(result, &lenght);
    return EXIT_SUCCESS;
}