
#ifndef PROJECT_4_MEM_MANAGEMENT_H
#define PROJECT_4_MEM_MANAGEMENT_H

// A single page table entry
struct PTE {
    // Status bits
    int valid, reference, dirty;
};

#endif
