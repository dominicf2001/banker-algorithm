#include <stddef.h>
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

void matrix_print(int** matrix, size_t width, size_t height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%d |", matrix[i][j]);
        }
        printf("\n");
    }
}

void array_print(int* array, size_t size) {
    printf("[");
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i < (size - 1)) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}

int array_compare(int* a, int* b, size_t size) {
    for (int i = 0; i < size; ++i){
        if (a[i] > b[i]) {
            return 0;
        }
    }
    return 1;
}

int array_contains(int *a, size_t size, int x) {
    for (int i = 0; i < size; ++i){
        if (a[i] == x) {
            return 1;
        }
    }
    return 0;
}

void initialize(const char* file_name) {
    FILE *fp = fopen(file_name, "r");
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
    initialize(argv[1]);
    
    /* printf("Max matrix\n"); */
    /* matrix_print(max, num_of_resources, num_of_processes); */

    /* printf("Allocation matrix\n"); */
    /* matrix_print(allocation, num_of_resources, num_of_processes); */

    /* printf("Need matrix\n"); */
    /* matrix_print(max, num_of_resources, num_of_processes); */

    /* printf("Available array\n"); */
    /* array_print(available, num_of_resources); */

    int k = 0;
    int* safe_sequence = malloc(sizeof(int) * num_of_processes);
    memset(safe_sequence, -1, sizeof(int) * num_of_processes);
    
    int p_num = 0;
    while (k != num_of_processes) {
        int acceptableNeed = array_compare(need[p_num], available, num_of_resources);
        if (!array_contains(safe_sequence, num_of_processes, p_num) && acceptableNeed) {
            for (int i = 0; i < num_of_resources; ++i) {
                available[i] = available[i] + allocation[p_num][i];
            }
            safe_sequence[k++] = p_num;
        }
        p_num = (p_num + 1) % num_of_processes;
    }

    printf("SAFE SEQUENCE: ");
    array_print(safe_sequence, num_of_processes);
}
