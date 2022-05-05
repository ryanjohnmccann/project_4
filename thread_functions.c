
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "list_functions.h"
#include "thread_functions.h"
#include "mem_management.h"

struct Register *regs;
int virtual_mem_size;

void init_registers() {
    regs = NULL;
    for (int i = 0; i < 32; i++) {
        struct Register *tmp_reg = (struct Register *) malloc(sizeof(struct Register));
        tmp_reg->index = i;
        for (int j = 0; j < 8; j++) {
            tmp_reg->data[j] = 0;
        }
        append_register(&regs, tmp_reg);
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

    init_registers();

    // TODO: Register number could be have two characters (10 and up)
    int line_count = 0;
    int data_count = 0;
    int virtual_address;
    // Random relates to unwanted whitespace or newlines
    char command, reg_num, random;
    fp = fopen(file_name, "r");
    while (!feof(fp)) {
        if (line_count == 0) {
            fscanf(fp, "%d%c", &virtual_mem_size, &random);
            init_page_table(virtual_mem_size);
            line_count += 1;
        } else {
            if (data_count == 0) {
                fscanf(fp, "%c%c", &command, &random);
            } else if (data_count == 1) {
                fscanf(fp, "%c%c%c", &random, &reg_num, &random);
            } else {
                fscanf(fp, "%d%c", &virtual_address, &random);
                execute_command(command, reg_num, virtual_address, pid);
                data_count = -1;
            }
            data_count += 1;
        }
    }

    fclose(fp);
    pthread_exit((void *) id);
}
