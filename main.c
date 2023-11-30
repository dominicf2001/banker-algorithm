#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int** allocation;
int** available;
int* max;

void initialize() {
    FILE *fp = fopen("input.txt", "r");
    char c = fgetc(fp);

    // determine num of resources and processes
    int num_of_resources = 0;
    int num_of_processes = 0;
    int done_counting_resources = 0;
    while (c != '-'){
        if (!done_counting_resources && isdigit(c))
            ++num_of_resources;
        
        if (c == '|')
            done_counting_resources = 1;
        
        if (c == '\n')
            ++num_of_processes;
        
        c = fgetc(fp);
    }
    fseek(fp, 0, SEEK_SET);

    // allocate memory for the matrices
    allocation = malloc(sizeof(int*) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        allocation[i] = malloc(sizeof(int) * num_of_resources);
    }
    available = malloc(sizeof(int*) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        available[i] = malloc(sizeof(int) * num_of_resources);
    }
    max = malloc(sizeof(int) * num_of_resources);
    
    // initialize available and allocation matrices
    int is_allocation = 0;
    int p_num = 0;
    int r_num = 0;
    c = fgetc(fp);
    while (c != '-' && !feof(fp)) {
        if (is_allocation && isdigit(c)) {
            allocation[p_num][r_num] = (c - '0');
        }
        else if (isdigit(c)) {
            available[p_num][r_num] = (c - '0');
        }
        
        if (c == '|') {
            is_allocation = !is_allocation;
            r_num = 0;
        }
        else {
            ++r_num;
        }
        
        if (c == '\n')
            ++p_num;

        c = fgetc(fp);
    }

    while (!feof(fp)) {
        
        c = fgetc(fp);
    }
    
    fclose(fp);
}

int main (int argc, char** argv) {
    initialize();
}
