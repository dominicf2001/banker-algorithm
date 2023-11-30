#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int num_of_processes = 0;
int num_of_resources = 0;
int** allocation;
int** available;
int* max;

void print_matrix(int** matrix) {
    for (int i = 0; i < num_of_processes; ++i) {
        for (int j = 0; j < num_of_resources; ++j) {
            printf("%d |", matrix[i][j]);
        }
        printf("\n");
    }
}

void initialize() {
    FILE *fp = fopen("input.txt", "r");
    char c = fgetc(fp);

    // determine num of resources and processes
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
            ++r_num;
        }
        else if (isdigit(c)) {
            available[p_num][r_num] = (c - '0');
            ++r_num;
        }
        
        if (c == '|') {
            is_allocation = !is_allocation;
            r_num = 0;
        }
        
        if (c == '\n')
            ++p_num;

        c = fgetc(fp);
    }

    /* while (!feof(fp)) { */
        
    /*     c = fgetc(fp); */
    /* } */
    
    fclose(fp);
}

int main (int argc, char** argv) {
    initialize();
    printf("Available matrix\n");
    print_matrix(available);

    /* printf("Allocation matrix\n"); */
    /* print_matrix(allocation); */
}
