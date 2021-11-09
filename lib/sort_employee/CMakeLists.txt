add_library(sort STATIC sort_employee.c)
target_include_directories(sort PUBLIC include)
target_link_libraries(sort PUBLIC utils)