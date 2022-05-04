
#include "stdio.h"
#include <stdlib.h>

#include "linked_list.h"
#include "mem_management.h"

//struct PTE *page_table = NULL;

extern int page_size;

void init_page_table(int memory_size) {
    int num_pages = memory_size / page_size;
    for (int i = 0; i < num_pages; i++) {
        struct PTE *page_table = (struct PTE *) malloc(sizeof(struct PTE));
        page_table->dirty = 0;
        // Start with an invalid frame
        page_table->frame = -1;
        page_table->page_number = i;
        page_table->valid = 0;
        page_table->reference = 0;
    }
}

void init_main_mem(int memory_size) {
    int num_frames = memory_size / page_size;
    for (int i = 0; i < num_frames; i++) {

    }
}
