
#ifndef PROJECT_4_MEM_MANAGEMENT_H
#define PROJECT_4_MEM_MANAGEMENT_H

struct PTE {
    int index, valid, reference, dirty, frame;
    struct PTE *next;
};

struct Frame {
    int index;
    // Expect 4 bytes, for 32 bit values
    char data[4];
    struct Frame *next;
};

void append_pte(struct PTE **head_ref, struct PTE *new_node);

void change_pte_data(struct PTE *node, int index, int data, char data_select);

void print_page_table(struct PTE *node);

void append_frame(struct Frame **head_ref, struct Frame *new_node);

void change_frame_data(struct Frame *node, int index, int data);

void print_frames(struct Frame *node);

void init_page_table(int memory_size);

void init_main_mem(int memory_size);

#endif
