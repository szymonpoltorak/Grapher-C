#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void ifReadMode(const char* usage, short unsigned int mode){
    if (mode != READ){
        fprintf(stderr, "IT IS NOT READ MODE!\n%s\n", usage);
        exit(EXIT_FAILURE);
    }
}

void validateFileName(char* optarg, const char* usage){
    FILE* in = fopen(optarg, "r");

    if (in == NULL){
        fprintf(stderr, "FILE DOES NOT EXIST! USAGE:\n %s\n", usage);
        exit(NO_FILE_FOUND);
    }
    fclose(in);
}