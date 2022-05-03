
#include <stdio.h>
#include <stdlib.h>

char *input_file_name, *output_file_name;
int random_seed;
int mm_size, page_size, num_processes;

void handle_infile(const char *file_name) {
    FILE *fp;
    int line_count = 0;
    char line[50];

    fp = fopen(file_name, "r");
    while (fgets(line, sizeof(line), fp)) {
        if (line_count == 0) {
            mm_size = atoi(line);
        }
        else if (line_count == 1) {
            page_size = atoi(line);
        }
        else if (line_count == 2) {
            num_processes = atoi(line);
        }
        // TODO: Do I really need to read the other file names?
        line_count += 1;
    }
    fclose(fp);
}


// Controls the program
int main(int argc, char* argv[]) {

    input_file_name = argv[1];
    output_file_name = argv[2];
    random_seed = atoi(argv[3]);

    handle_infile(input_file_name);

    return 0;
}
