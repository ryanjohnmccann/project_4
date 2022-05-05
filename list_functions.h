
#ifndef PROJECT_4_LIST_FUNCTIONS_H
#define PROJECT_4_LIST_FUNCTIONS_H

struct PTE {
    int index, valid, reference, dirty, frame;
    struct PTE *next;
};

struct Frame {
    int index;
    // Expect 8 bytes, for 32 bit values
    char data[8];
    struct Frame *next;
};

struct Register {
    int index;
    char data[8];
    struct Register *next;
};

void append_pte(struct PTE **head_ref, struct PTE *new_node);

void change_pte_data(struct PTE *node, int index, int data, char data_select);

void print_page_table(struct PTE *node);

void append_frame(struct Frame **head_ref, struct Frame *new_node);

void change_frame_data(struct Frame *node, int index, unsigned int address);

void print_frames(struct Frame *node);

void append_register(struct Register **head_ref, struct Register *new_node);

void change_register_data(struct Register *node, int index, unsigned int address);

void print_registers(struct Register *node);


#endif
