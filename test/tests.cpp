#include <gtest/gtest.h>

extern "C" {
    #include "sort_employee.h"
}

TEST (test_free, test_empl_free){
    Employee *element = nullptr;
    EXPECT_EQ (free_employee(element), 2);

    element = create_element();
    if (element == nullptr) FAIL();

    EXPECT_EQ (free_employee(element), 0);

}

TEST (test_init_del, test_init_empl){
    Employee *elemnt = create_element();
    EXPECT_FALSE(elemnt == NULL);
    free_employee(elemnt);
}

TEST (test_free, test_arr_empl_free){

    Employee **elements = nullptr;
    const size_t size = 1;
    size_t size_incorect = 0;

    EXPECT_EQ (free_array_employee(elements, &size), 1);

    elements = (Employee**)calloc(size, sizeof(Employee*));
    if (elements == nullptr) FAIL();

    elements[0] = nullptr;
    EXPECT_EQ (free_array_employee(elements, &size), 1);

    elements[0] = create_element();
    if (elements[0] == nullptr){ 
        free_array_employee(elements, &size);
        FAIL();
    }


    EXPECT_EQ (free_array_employee(elements, &size_incorect), 1);
    EXPECT_EQ (free_array_employee(elements, NULL), 1);
    EXPECT_EQ (free_array_employee(elements, &size), 0);
}

TEST (test_init, test_init_position){
    Position *element = nullptr;
    size_t size = 5;
    size_t size_incorect = 0;
    
    EXPECT_EQ(position_initial(element, &size), 2);

    element = (Position *)calloc(1, sizeof(Position));
    if (element == nullptr) FAIL();

    EXPECT_EQ(position_initial(element, NULL), 2);
    EXPECT_EQ(position_initial(element, &size_incorect), 2);
    EXPECT_EQ(position_initial(element, &size), 0);

    free_position(element);
    free(element);
}

TEST (test_free, test_position_free){

    Position *element = nullptr;
    size_t size = 1;

    EXPECT_EQ (free_position(element), 2);

    element = (Position *)calloc(1, sizeof(Position));
    if (element == nullptr) FAIL();

    position_initial(element, &size);
    if (element == nullptr) FAIL();

    EXPECT_EQ (free_position(element), 0);
    free(element);
}


TEST (test_free, test_arr_position_free){

    size_t size = 1;
    size_t size_incorect = 0;
    Position *elements = (Position*)calloc(size, sizeof(Position));
    if (elements == nullptr) FAIL();

    if(position_initial(&elements[0], &size) !=0){
        free_array_position(elements, &size);
        FAIL();
        }

    EXPECT_EQ (free_array_position(elements, NULL), 1);
    EXPECT_EQ (free_array_position(NULL, &size), 1);
    EXPECT_EQ (free_array_position(elements, &size_incorect), 1);
    EXPECT_EQ (free_array_position(elements, &size), 0);
}

TEST (test_cmp, test_cmp){

    char position_1[] = "Direct";
    char position_2[] = "Driver";
    char last_name_1[] = "Ivanov";
    char last_name_2[] = "Smirnov";

    Employee *left = create_element();
    if (left == nullptr) FAIL();

    Employee *right = create_element();
    if (right == nullptr){
        free_employee(left);
        FAIL();
    }

    if (left->position != nullptr) strcpy(left->position, position_1);
    left->age = 25;
    if (right->position != nullptr) strcpy(right->position, position_1);
    right->age = 35;


    EXPECT_EQ (compare_position(&left, &right), -10);
    strcpy(left->position, position_2);

    EXPECT_TRUE (compare_position(&left, &right) == 1 || compare_position(&left, &right) == 9);

    if (left->last_name != nullptr) strcpy(left->last_name, last_name_1);
    if (right->last_name != nullptr) strcpy(right->last_name, last_name_2);
    
    EXPECT_TRUE (compare_name(&left, &right) == -1 || compare_name(&left, &right) == -10);
    
    free_employee(left);
    free_employee(right);
}

TEST (tect_incorrect_val, test_select){

    Position *elements = (Position*)calloc(1, sizeof(Position));
    if (elements == nullptr) FAIL();

    size_t size  = 1;
    size_t incorrect_size  = 0;
    size_t incorrect_size_2  = 2;

    Employee **ptr = nullptr;
    elements->size = 1;
    elements->start_ptr = ptr;

    EXPECT_EQ (select_sort(NULL, &size), 2);
    EXPECT_EQ (select_sort(elements, NULL), 2);
    EXPECT_EQ (select_sort(elements, &incorrect_size), 2);
    EXPECT_EQ (select_sort(elements, &size), 6);

    EXPECT_EQ (employee_selection(NULL, &size), 2);
    EXPECT_EQ (employee_selection(elements, NULL), 2);
    EXPECT_EQ (employee_selection(elements, &incorrect_size), 3);
    EXPECT_EQ (employee_selection(elements, &size), 5);

    free_position(elements);

    EXPECT_EQ (employee_selection(elements, &incorrect_size_2), 5);
    elements->size = 0;
    EXPECT_EQ (employee_selection(elements, &size), 3);

    free_position(elements);
    free(elements);
}


TEST (tect_incorrect_val, test_fill_posit_array){

    Position *position = (Position*)calloc(1, sizeof(Position));
    if (position == nullptr) FAIL();

    Employee **employee = (Employee**)calloc(1, sizeof(Employee*));
    if (employee == nullptr) FAIL();

    size_t size  = 1;

    EXPECT_EQ (fill_posit_array(NULL, position, &size), -1);
    EXPECT_EQ (fill_posit_array(employee, NULL, &size), -1);
    EXPECT_EQ (get_worker_information(NULL, &size, &size, &size), nullptr);

    free_position(position);
    free(position);
    free(employee);
}

TEST (test_correct, test_correct_main){

    size_t size = 2;
    size_t result_size = 1;
    size_t lenght = 0;

    Employee **employees = (Employee**)calloc(size, sizeof(Employee*));
    if (employees == nullptr) FAIL();
    Position *elements = (Position*)calloc(1, sizeof(Position));
    if (elements == nullptr) FAIL();

    char position[]= {"Direct"};
    char last_name[][10] = {"Willi", "Born"};
    for( size_t i = 0; i < size; ++i){
        employees[i] = create_element();
        if (employees[i] == NULL) FAIL();
        strcpy(employees[i]->position, position);
        strcpy(employees[i]->last_name, last_name[i]);
        employees[i]->age = i;
    }
    elements->position = employees[0]->position;
    elements->size = size;
    elements->start_ptr = employees;
    if (position_initial(elements, &result_size) != 0) FAIL();
    if (elements->oldest == NULL || elements->youngest == NULL) FAIL();
    elements->youngest[0] = employees[0];
    elements->oldest[0] = employees[1];


    Position *result = nullptr;
    result = get_worker_information(employees, &size, &result_size, &lenght);

    EXPECT_EQ (strcmp(result->position, elements->position), 0);
    EXPECT_TRUE (result->size == elements->size);
    EXPECT_TRUE (*(result->start_ptr) == *(elements->start_ptr));
    EXPECT_TRUE (*(result->youngest) == *(elements->start_ptr));
    EXPECT_TRUE (*(result->oldest) == *(elements->oldest));

 
    free_array_position (result, &lenght);
    free_array_position (elements, &result_size);
    free_array_employee (employees, &size);
}

TEST (test_correct, test_correct_select){

    size_t size = 2;
    Position *elements = (Position*)calloc(size, sizeof(Position));
    if (elements == nullptr) FAIL();

    Employee **employees = (Employee**)calloc(size, sizeof(Employee*));
    if (employees == nullptr) FAIL();
    employees[0] = create_element();
    employees[1] = create_element();
    if (employees[0] == NULL || employees[1] == NULL) FAIL();

    char position[][10] = {"Direct", "Manager"};
    char last_name[][10] = {"Willi", "Born"};
    for( size_t i = 0; i < size; ++i){
        strcpy(employees[i]->position, position[i]);
        strcpy(employees[i]->last_name, last_name[i]);
        employees[i]->age = 5;
    }

    EXPECT_EQ (fill_posit_array(employees, elements, &size), 0);
    EXPECT_EQ (employee_selection(elements, &size), 0);

    free_array_employee(employees, &size);
    free_position(elements);
    free(elements);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
