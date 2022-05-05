
#ifndef PROJECT_4_THREAD_FUNCTIONS_H
#define PROJECT_4_THREAD_FUNCTIONS_H

struct Register {
    char data[8];
    struct Register *next;
};

void append_register();

void change_register_data();

void print_registers();

void *Process(void *id);

#endif
