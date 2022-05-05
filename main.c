// TODO: Update comments, doc strings, and clean

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "thread_functions.h"
#include "mem_management.h"

FILE *output_fp;
char *input_file_name, *output_file_name;
int mm_size, page_size, num_processes, random_seed;
sem_t output_sem, mem_sem;

void handle_infile(const char *file_name) {
    FILE *fp;
    int line_count = 0;
    char line[50];

    fp = fopen(file_name, "r");
    while (fgets(line, sizeof(line), fp)) {
        if (line_count == 0) {
            mm_size = atoi(line);
        } else if (line_count == 1) {
            page_size = atoi(line);
        } else if (line_count == 2) {
            num_processes = atoi(line);
        }
        line_count += 1;
    }
    fclose(fp);
}


// Controls the program
int main(int argc, char *argv[]) {

    void *status;
    int rc;

    input_file_name = argv[1];
    output_file_name = argv[2];
    random_seed = atoi(argv[3]);

    // TODO: Check if random seed exists: srand(time(0))
    srand(random_seed);

    handle_infile(input_file_name);

    init_main_mem(mm_size);

    // TODO: Check this
    // Init semaphores and threads
    sem_init(&output_sem, 0, 0);
    sem_init(&mem_sem, 0, 0);
    pthread_t process_threads[num_processes];

    // Output file
    output_fp = fopen(output_file_name, "w");
    fclose(output_fp);
    output_fp = fopen(output_file_name, "a");

    // Create threads
    for (int i = 0; i < num_processes; i++) {
        fprintf(output_fp, "Process %i started\n", i);
        long tmp_id = i;
        rc = pthread_create(&process_threads[i], NULL, Process, (void *) tmp_id);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join threads
    for (int i = 0; i < num_processes; i++) {
        rc = pthread_join(process_threads[i], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        fprintf(output_fp, "Process %i complete\n", i);
    }

    fprintf(output_fp, "Main: program completed\n");
    fclose(output_fp);
    pthread_exit(NULL);
}
