
#include "thread_functions.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>

int virtual_mem_size;

void *Process(void *id) {

    FILE *fp;
    long pid = (long) id;

    char file_name[50] = "thread";
    // Add one to the process ID (since file names start at 1 and not 0)
    char tmp = pid + '1';
    strncat(file_name, &tmp, 1);
    strncat(file_name, ".txt", 4);

    int line_count = 0;
    int data_count = 0;
    int virtual_address;
    char command;
    char reg;
    fp = fopen(file_name, "r");
    while (!feof(fp)) {
        if (line_count == 0) {
            fscanf(fp, "%d", &virtual_mem_size);
            line_count += 1;
        } else {
            if (data_count == 0) {
                fscanf(fp, "%c", &command);
                printf("This is what command is -->%c\n\n", command);
            } else if (data_count == 1) {
                fscanf(fp, "%c", &reg);
                printf("This is what reg is -->%c\n\n", reg);
            } else {
                fscanf(fp, "%d", &virtual_address);
                data_count = -1;
            }
            data_count += 1;
        }
    }

    fclose(fp);
    pthread_exit((void *) id);
}
