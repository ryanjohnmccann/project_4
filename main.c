// TODO: Update comments, doc strings, and clean

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "thread_functions.h"

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

    handle_infile(input_file_name);

    // TODO: Check this
    // Init semaphores and threads
    sem_init(&output_sem, 0, 0);
    sem_init(&mem_sem, 0, 0);
    pthread_t process_threads[num_processes];

    // TODO: Check print statements
    // Create threads
    for (int i = 0; i < 1; i++) {
        printf("Main: started producer %i\n", i);
        long tmp_id = i;
        rc = pthread_create(&process_threads[i], NULL, Process, (void *) tmp_id);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join threads
    for (int i = 0; i < 1; i++) {
        rc = pthread_join(process_threads[i], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        // TODO: Check print statement
        printf("Main: producer %i joined\n", i);
    }

    pthread_exit(NULL);
}
