
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_management.h"

struct PTE *page_table;
struct Frame *frames;

extern int page_size;
extern int random_seed;

void append_pte(struct PTE **head_ref, struct PTE *new_node) {
    struct PTE *last = *head_ref;

    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void change_pte_data(struct PTE *node, int index, int data, char data_select) {
    while (node != NULL) {
        if (node->index == index) {
            // Valid bit
            if (data_select == 'v') {
                node->valid = data;
            }
                // Reference bit
            else if (data_select == 'r') {
                node->reference = data;
            }
                // Dirty bit
            else if (data_select == 'd') {
                node->dirty = data;
            }
                // Frame number
            else if (data_select == 'f') {
                node->frame = data;
            }
        }
        node = node->next;
    }
}

void print_page_table(struct PTE *node) {
    while (node != NULL) {
        printf("Index: %d\tValid bit: %d\tReference bit: %d\tDirty bit: %d\tFrame: %d\n\n", node->index,
               node->valid, node->reference, node->dirty, node->frame);
        node = node->next;
    }
}

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

void append_frame(struct Frame **head_ref, struct Frame *new_node) {
    struct Frame *last = *head_ref;

    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void change_frame_data(struct Frame *node, int index, unsigned int address) {
    while (node != NULL) {
        if (node->index == index) {

            unsigned int tmp = 0xF0000000;
            unsigned int shift = 28;

            for (int j = 0; j < 8; j++) {
                node->data[j] = (tmp & address) >> shift;
                tmp = tmp >> 4;
                shift -= 4;
            }

        }
        node = node->next;
    }
}

void print_frames(struct Frame *node) {
    while (node != NULL) {
        for (int i = 0; i < 8; i++) {
            if (i == 0) {
                printf("0x");
            }
            printf("%x", node->data[i]);
        }
        printf("\n");
        node = node->next;
    }
}

void init_main_mem(int memory_size) {
    int num_frames = memory_size / page_size;
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
