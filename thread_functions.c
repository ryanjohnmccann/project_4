
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "thread_functions.h"
#include "linked_list.h"

int virtual_mem_size;

void init_registers() {
    struct Node *regs = NULL;
    for (int i = 0; i < 32; i++) {
        push(&regs, -1);
    }
}

void *Process(void *id) {

    FILE *fp;
    long pid = (long) id;

    // Handle thread file
    char file_name[50] = "thread";
    // Add one to the process ID (since file names start at 1 and not 0)
    char tmp = pid + '1';
    strncat(file_name, &tmp, 1);
    strncat(file_name, ".txt", 4);

    int line_count = 0;
    int data_count = 0;
    int virtual_address;
    // Random relates to unwanted whitespace or newlines
    char command, reg, random;
    fp = fopen(file_name, "r");
    init_registers();
    while (!feof(fp)) {
        if (line_count == 0) {
            fscanf(fp, "%d%c", &virtual_mem_size, &random);
            line_count += 1;
        } else {
            if (data_count == 0) {
                fscanf(fp, "%c%c", &command, &random);
            } else if (data_count == 1) {
                fscanf(fp, "%c%c%c", &random, &reg, &random);
            } else {
                fscanf(fp, "%d%c", &virtual_address, &random);
                data_count = -1;
            }
            data_count += 1;
        }
    }

    fclose(fp);
    pthread_exit((void *) id);
}
