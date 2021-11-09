#pragma once
#include "sort_employee.h"

Employee **read_data_from_file(const char *file_name, size_t *size);
Employee *create_element_from_file(FILE *f_ptr);
void print_position(Position *element);
void print_employee(Employee *element);