
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>

#include "list_functions.h"
#include "mem_management.h"

struct PTE *page_table;
struct Frame *frames;
int num_frames;

extern int page_size, *free_frames;
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
    num_frames = memory_size / page_size;
    // Indexes will be used to determine if the frame is free, e.g. if index 0 = 1, then that frame is free!
    free_frames = malloc(sizeof(int) * num_frames);
    frames = NULL;

    for (int i = 0; i < num_frames; i++) {
        // Init all frames to be free
        free_frames[i] = 1;
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

int find_free_frame() {
    for (int i = 0; i < num_frames; i++) {
        if (free_frames[i] == 1) {
            free_frames[i] = 0;
            return i;
        }
    }
    // All the frames are taken, we need to evict
    // TODO: Randomly evicting for now, update this
    return 0;
}

void execute_command(char command, int reg_num, int virtual_address, long pid) {
    sem_wait(&output_sem);
    fprintf(output_fp, "P%ld: OPERATION: %c r%i %i\n", pid, command, reg_num, virtual_address);
    sem_post(&output_sem);

    int des_page = find_page_num(virtual_address);
    int in_memory = get_pte_data(page_table, des_page, 'v');

    sem_wait(&output_sem);
    if (!in_memory) {
        fprintf(output_fp, "P%ld: page %d not resident in memory\n", pid, des_page);
        // Page is now resident in memory
        int curr_frame = find_free_frame();
        // Update valid bit
        change_pte_data(page_table, des_page, 1, 'v');
        // Update the frame
        change_pte_data(page_table, des_page, curr_frame, 'f');
        fprintf(output_fp, "P%ld: new translation from page %d to frame %d\n", pid, des_page, curr_frame);
    } else {
        int curr_frame = get_pte_data(page_table, des_page, 'f');
        fprintf(output_fp, "P%ld: valid translation from page %d to frame %d\n", pid, des_page,
                curr_frame);
    }
    // TODO: Translate physical address
    // TODO: Read data into the register and print it
    fprintf(output_fp, "translated VA 0x%08x to PA 0x%08x\n", virtual_address);
    sem_post(&output_sem);

}
