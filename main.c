#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int num_of_processes = 0;
int num_of_resources = 0;
int** allocation;
int** max;
int** need;
int* available;

void print_matrix(int** matrix) {
    for (int i = 0; i < num_of_processes; ++i) {
        for (int j = 0; j < num_of_resources; ++j) {
            printf("%d |", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_array(int* array) {
    printf("[");
    for (int i = 0; i < num_of_resources; ++i) {
        printf("%d", array[i]);
        if (i < (num_of_resources - 1)) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
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
    max = malloc(sizeof(int*) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        max[i] = malloc(sizeof(int) * num_of_resources);
    }
    need = malloc(sizeof(int*) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        need[i] = malloc(sizeof(int) * num_of_resources);
    }
    available = malloc(sizeof(int) * num_of_resources);
    
    // initialize max and allocation matrices
    int is_allocation = 1;
    int p_num = 0;
    int r_num = 0;
    c = fgetc(fp);
    while (c != '-' && !feof(fp)) {
        if (is_allocation && isdigit(c)) {
            allocation[p_num][r_num] = (c - '0');
            ++r_num;
        }
        else if (isdigit(c)) {
            max[p_num][r_num] = (c - '0');
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
    
    r_num = 0;
    while (!feof(fp)) {
        if (isdigit(c)) {
            available[r_num] = (c - '0');
            ++r_num;
        }
        
        c = fgetc(fp);
    }

    // initialize need matrix
    for (int i = 0; i < num_of_processes; ++i){
        for (int j = 0; j < num_of_resources; ++j){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    fclose(fp);
}

int main (int argc, char** argv) {
    initialize();
    printf("Max matrix\n");
    print_matrix(max);

    printf("Allocation matrix\n");
    print_matrix(allocation);

    printf("Need matrix\n");
    print_matrix(need);

    printf("Available array\n");
    print_array(available);

    /* int k = 0; */
    /* int* safe_sequence = malloc(sizeof(int) * num_of_processes); */
    /* memset(safe_sequence, 0, num_of_processes); */

    /* int i = 0; */
    /* while (k != num_of_processes) { */
    /*     if (!safe_sequence[i] && ) */
        
    /*     i = (i + 1) % num_of_processes; */
    /* } */
}
