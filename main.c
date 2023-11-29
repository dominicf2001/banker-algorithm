#include <stdio.h>

int** allocation;
int** available;
int** max;

void initialize() {
    FILE *fp = fopen("input.txt", "r");

    // TODO: need to allocate memory for the matrices
    // ...
    
    // initialize available and allocation matrices
    char *c = fgetc(fp);
    int is_allocation = 0;
    int p_num = 0;
    int i = 0;
    while (c != "-" || feof(fp)) {
        if (is_allocation) {
            allocation[p_num][i] = (c - '0');
        }
        else {
            available[p_num][i] = (c - '0');            
        }
        
        if (c == "|") {
            is_allocation = !is_allocation;
            i = 0;
        }
        else {
            ++i;
        }
        
        if (c == "\n")
            ++p_num;
    }
    
    fclose(fp);
}

int main (int argc, char** argv) {
    
}
