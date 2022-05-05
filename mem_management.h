
#ifndef PROJECT_4_MEM_MANAGEMENT_H
#define PROJECT_4_MEM_MANAGEMENT_H

void init_page_table(int memory_size);

void init_main_mem(int memory_size);

void execute_command(char command, int reg_num, int virtual_address, long pid);

#endif
