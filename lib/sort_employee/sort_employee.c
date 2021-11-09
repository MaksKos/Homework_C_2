#include "sort_employee.h"


Employee *create_element(){

    // функция инициализирует структуру Employee

    Employee *new_element = calloc(1, sizeof(Employee));
    if (new_element == NULL){
        return NULL;
    }

    new_element->name = calloc(STR_SIZE, sizeof(char*));
    if (new_element->name == NULL){
        free_employee(new_element);
        return NULL;
    }
    new_element->last_name = calloc(STR_SIZE, sizeof(char*));
    if(new_element->last_name == NULL){
        free_employee(new_element);
        return NULL;
    }
    new_element->position = calloc(STR_SIZE, sizeof(char*));
    if(new_element->position == NULL){
        free_employee(new_element);
        return NULL;
    }
    return new_element;
}

int position_initial(Position *element, const size_t *size){
    // инициализирует структуру position
    if (element == NULL || size == NULL || *size < 1){
        return 2;
    }
    element->youngest = (Employee**)calloc(*size, sizeof(Employee**));
    if(element->youngest == NULL){
        free_position(element);
        return 3;
    }
    element->oldest = (Employee**)calloc(*size, sizeof(Employee**));
    if(element->oldest == NULL){
        free_position(element);
        return 4;
    }
    return 0;
}

int free_array_employee(Employee **arr, const size_t *n){

    if( arr == NULL || n == NULL || *n < 1){
        return 1;
    }
    for(size_t i = 0; i < *n; ++i){
        if (free_employee(arr[i]) != 0){
            return 1;
        }
    }
    free(arr);
    return 0;
}

int free_employee(Employee *struc){
    if(struc == NULL){
        return 2;
    }
    if(struc->name != NULL ) free(struc->name);
    if(struc->last_name != NULL ) free(struc->last_name);
    if(struc->position != NULL ) free(struc->position);
    free(struc);
    return 0;  
}

int free_array_position(Position *arr, size_t *n){
    if( arr == NULL || n == NULL || *n < 1){
        return 1;
    }
    for(size_t i = 0; i < *n; ++i){
        free_position(&arr[i]);
    }
    free(arr);
    return 0;
}

int free_position(Position *struc){
    if(struc == NULL){
        return 2;
    }
    if(struc->youngest != NULL ) free(struc->youngest);
    if(struc->oldest != NULL ) free(struc->oldest);
    return 0;  
}

Position *get_worker_information (Employee **data, const size_t *N, const size_t *result_size, size_t *len ){

    //функция выполянет обработку массива сотрудников и возвращает результат
    if (data == NULL){
        return NULL;
    }
    size_t count_posit = 1;

    //сортируем по должности и возрасту
    qsort(data, *N, sizeof(Employee*), compare_position);

    //подсчет количевтва должностей
    char *curr_posit = data[0]->position;
    for (size_t i = 1; i < *N; ++i){
        if (strcmp(curr_posit, data[i]->position) != 0)
        {
            curr_posit = data[i]->position;
            count_posit++;
        }
    }

    *len = count_posit;

    // инициализируем и заполняем структуру "должность" по каждой должности
    Position *posit_array = (Position*)calloc(count_posit, sizeof(Position));
    if (posit_array == NULL) return NULL;

    if(fill_posit_array(data, posit_array, N) !=0){
        free_array_position(posit_array, &count_posit);
        return NULL;
    }

    // дальнейшая обработка: выделение возрастных и молодых и сортировка по фамилии
    for (size_t i = 0; i < count_posit; ++i){
        if (employee_selection(&posit_array[i], result_size) != 0){
            free_array_position(posit_array, &i);
            return NULL;
        }
    }
    return posit_array;
}

int fill_posit_array(Employee **data, Position *posit_array, const size_t *n){

    if(posit_array == NULL || data == NULL ){
        return -1;
    }

    size_t count = 0;
    size_t last_ptr = 0;
    for (size_t i = 1; i < *n; ++i)
    {
        if (strcmp(data[i]->position, data[i-1]->position) != 0){
            posit_array[count].position = data[i-1]->position;
            posit_array[count].start_ptr = &data[last_ptr];
            posit_array[count].size = i - last_ptr;
            last_ptr = i;
            count++;
        }
        if(i == *n-1){
            posit_array[count].position = data[i]->position;
            posit_array[count].start_ptr = &data[last_ptr];
            posit_array[count].size = i - last_ptr + 1;
        }
    }
    return 0;
}

int compare_position(const void *elem_1, const void *elem_2){

    const Employee *left  = *(const Employee **)elem_1;
    const Employee *right = *(const Employee **)elem_2;
    
    int cmp = strcmp(left->position, right->position);
    if (cmp) return cmp;

    return (left->age - right->age);
}

int  employee_selection(Position *element, const size_t *result_size){

    // выбирает нужное количество сотрудников по каждой должности
    if (element == NULL || result_size == NULL){
        return 2;
    }
    if ((*result_size < 1) || (element->size < 1)){
        return 3;
    }
    if (*result_size <= element->size){
        position_initial(element, result_size);
        if (select_sort(element, result_size) != 0){
            return 5;
        }
    }
    else{
        position_initial(element, &element->size);
        if (select_sort(element, &element->size) != 0){
            return 5;
        }
    }
    return 0;
}


int select_sort(Position *element, const size_t *size){
    // выбирает сотрудников и сортирует по фамилии
    if (element == NULL || size == NULL || *size < 1){
        return 2;
    }
    for (size_t i = 0; i < *size; ++i){
        if(element->start_ptr == NULL ){
            return 6;
        }
        element->youngest[i] = element->start_ptr[i];
        element->oldest[i] = element->start_ptr[element->size-1-i];
    }
    if (*size > 1){
        qsort(element->youngest, *size, sizeof(Employee*), compare_name);
        qsort(element->oldest, *size, sizeof(Employee*), compare_name);
    }
    element->result_size = *size;
    return 0;
}


int compare_name(const void *elem_1, const void *elem_2){

    const Employee *left  = *(const Employee **)elem_1;
    const Employee *right = *(const Employee **)elem_2;

    return strcmp(left->last_name, right->last_name);
}
