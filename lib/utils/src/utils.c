#include "utils.h"


Employee **read_data_from_file(const char *file_name, size_t *size){

    if (file_name == NULL || size == NULL){
        printf("Empty");
        return NULL;
    }

    FILE *file = fopen(file_name, "r");

    if (file == NULL){
        fprintf(stderr, "Failed to open file\n");
        return NULL;
    }
  
    fscanf(file, "%zu", size);

    Employee **data = calloc(*size, sizeof(Employee*));

    if (data == NULL){
        printf("Error create data\n");
        fclose(file);
        return NULL;
    }
    // в цикле проходимся по массиву, инициализиурем его и заполняем
    for(size_t i = 0; i < *size; i++){
        data[i] = create_element_from_file(file);
        if(data[i] == NULL){
            fprintf(stderr, "Failed create new elemnts");
            fclose(file);
            free_array_employee(data, &i);
            return NULL;
        }
    }

    if (fclose(file)) {
        fprintf(stderr, "Failed to close file\n");
        free_array_employee(data, size);
        return NULL;
    }

    return data;
}

Employee *create_element_from_file(FILE *f_ptr){

    Employee *new_element = create_element();
    if(new_element == NULL){
        return NULL;
    }
    fscanf(f_ptr, "%s", new_element->name);
    fscanf(f_ptr, "%s", new_element->last_name);
    fscanf(f_ptr, "%s", &new_element->sex);
    fscanf(f_ptr, "%zu", &new_element->age);
    fscanf(f_ptr, "%zu", &new_element->salary);
    fscanf(f_ptr, "%s", new_element->position);
    fscanf(f_ptr, "%zu", &new_element->experience);

    return new_element;

}


void print_employee(Employee *element){

    printf("Name: %s\n", element->name);
    printf("Last: %s\n", element->last_name);
    printf("Sex: %s\n", &element->sex);
    printf("Age: %zu\n", element->age);
    printf("Salary: %zu\n", element->salary);
    printf("Position: %s\n", element->position);
    printf("Exper: %zu\n\n", element->experience);
}


void print_position(Position *element){

    printf("-------------------------------------\n");
    printf("Position: %s\n", element->position);
    printf("Size: %zu\n", element->size);

    if (element->result_size < element->size){
        printf("----------\nYONGEST:\n----------\n");
        for (size_t i = 0; i < element->result_size; ++i){
            print_employee(element->youngest[i]);
        }
        printf("----------\nOLDEST:\n----------\n");
        for (size_t i = 0; i < element->result_size; ++i){
            print_employee(element->oldest[i]);
        }
    }
    else{
        printf("----------\nALL (size = %zu):\n----------\n", element->size);
        for (size_t i = 0; i < element->size; ++i){
            print_employee(element->youngest[i]);
        }
    }
}
