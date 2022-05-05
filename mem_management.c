
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>

#include "list_functions.h"
#include "mem_management.h"

struct PTE *page_table;
struct Frame *frames;

extern char *free_frames;
extern int page_size;
extern FILE *output_fp;
extern sem_t output_sem, mem_sem;

void init_page_table(int memory_size) {
    int num_pages = memory_size / page_size;
    page_table = NULL;

    for (int i = 0; i < num_pages; i++) {
        struct PTE *tmp_pte = (struct PTE *) malloc(sizeof(struct PTE));
        tmp_pte->index = i;
        tmp_pte->valid = 0;
        tmp_pte->reference = 0;
        tmp_pte->dirty = 0;
        // This means no frame present
        tmp_pte->frame = -1;
        append_pte(&page_table, tmp_pte);
    }
}

void init_main_mem(int memory_size) {
    int num_frames = memory_size / page_size;
    free_frames = malloc(sizeof(char) * (char) num_frames);
    frames = NULL;

    for (int i = 0; i < num_frames; i++) {
        // Generate 32-bit number
        int curr_address = rand();
        struct Frame *tmp_frame = (struct Frame *) malloc(sizeof(struct Frame));
        tmp_frame->index = i;

        // Store in big-endian format
        unsigned int tmp = 0xF0000000;
        unsigned int shift = 28;
        for (int j = 0; j < 8; j++) {
            tmp_frame->data[j] = (tmp & curr_address) >> shift;
            tmp = tmp >> 4;
            shift -= 4;
        }

        append_frame(&frames, tmp_frame);
    }
}

int find_page_num(int address) {
    int page_num, shift_bits = 0;
    unsigned int reference = 0xFFFFFFFF;
    while (pow(2, shift_bits) < page_size) {
        shift_bits += 1;
    }

    page_num = (reference << shift_bits) & address;
    return page_num >> shift_bits;
}

void execute_command(char command, int reg_num, int virtual_address, long pid) {
    sem_wait(&output_sem);
    fprintf(output_fp, "P%ld: OPERATION: %c r%i %i\n", pid, command, reg_num, virtual_address);
    sem_post(&output_sem);

    int des_page = find_page_num(virtual_address);

}
