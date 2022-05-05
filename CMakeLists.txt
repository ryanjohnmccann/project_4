cmake_minimum_required(VERSION 3.10)
project(project_4 C)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(project_4 main.c mem_management.c mem_management.h thread_functions.c thread_functions.h list_functions.c list_functions.h)
target_link_libraries(project_4 PRIVATE Threads::Threads)
