
#ifndef PROJECT_4_MEM_MANAGEMENT_H
#define PROJECT_4_MEM_MANAGEMENT_H

struct PTE {
    int page_number, valid, reference, dirty, frame;
    struct PTE *next;
};

struct Frame {
    // Expect 4 bytes, for 32 bit values
    char data[4];
    struct Frame *next;
};

void init_page_table(int memory_size);

void init_main_mem(int memory_size);

#endif
