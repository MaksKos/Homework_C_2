#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 16
#define NUM 10

typedef struct Employee
{
   char *name;
   char *last_name;
   char sex;
   size_t age;
   size_t salary;
   char *position;
   size_t experience;
} Employee ;

typedef struct Position
{
    char *position;
    Employee **start_ptr;
    Employee **youngest;
    Employee **oldest;
    size_t size;
    size_t result_size;
} Position;

Employee *create_element();
int position_initial(Position *element, const size_t *size);
int free_array_employee(Employee **arr, const size_t *n);
int free_employee(Employee *struc);
int free_array_position(Position *arr, size_t *n);
int free_position(Position *struc);
Position *get_worker_information (Employee **data, const size_t *N, const size_t *result_size , size_t *len);

int compare_position(const void *elem_1, const void *elem_2);
int employee_selection(Position *element, const size_t *result_size);
int select_sort(Position *element, const size_t *size);
int compare_name(const void *elem_1, const void *elem_2);
int fill_posit_array(Employee **data, Position *posit_array, const size_t *n);