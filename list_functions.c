
#include <stdio.h>
#include <string.h>

#include "list_functions.h"

struct PTE *page_table;
struct Frame *frames;
struct Register *regs;

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

int get_pte_data(struct PTE *node, int index, char data_select) {
    while (node != NULL) {
        if (node->index == index) {
            // Valid bit
            if (data_select == 'v') {
                return node->valid;
            }
                // Reference bit
            else if (data_select == 'r') {
                return node->reference;
            }
                // Dirty bit
            else if (data_select == 'd') {
                return node->dirty;
            }
                // Frame number
            else if (data_select == 'f') {
                return node->frame;
            }
        }
        node = node->next;
    }
    printf("INVALID RETURN FROM GET PTE DATA FUNCTION\n\n");
    return -1;
}

void print_page_table(struct PTE *node) {
    while (node != NULL) {
        printf("Index: %d\tValid bit: %d\tReference bit: %d\tDirty bit: %d\tFrame: %d\n\n", node->index,
               node->valid, node->reference, node->dirty, node->frame);
        node = node->next;
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

unsigned int get_frame_data(struct Frame *node, int index) {
    while (node != NULL) {

        unsigned int tmp = 0xF0000000;
        unsigned int res_value = 0x00000000;

        if (node->index == index) {
            for (int i = 0; i < 8; i++) {
                res_value = tmp & node->data[i];
                tmp = tmp >> 4;
            }
            return res_value;
        }
        node = node->next;
    }
    printf("INVALID RETURN FROM GET FRAME DATA FUNCTION\n\n");
    return -1;
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

void print_registers(struct Register *node) {
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

void change_register_data(struct Register *node, int index, unsigned int address) {
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

void append_register(struct Register **head_ref, struct Register *new_node) {
    struct Register *last = *head_ref;

    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}
