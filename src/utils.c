#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void ifReadMode(const char* usage, short int mode){
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

void validateRangeEnd(char* optarg, const char* usage){
    double end = 0;

    if (sscanf(optarg, "%lf", &end) != 1 || end <= 0){
        fprintf(stderr, "WRONG END! USAGE:\n%s\n", usage);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateColumns(char* optarg, const char* usage){
    int columns = 0;

    if(sscanf(optarg, "%d", &columns) != 1 || columns <= 0){
        fprintf(stderr, "WRONG NUMBER OF COLUMNS! USAGE:\n%s\n", usage);
        exit(WRONG_NUM_OF_COL);        
    }
}

void validateRangeStart(char* optarg, const char* usage){
    int start = 0;

    if(sscanf(optarg, "%d", &start) != 1 || start < 0){
        fprintf(stderr, "WRONG NUMBER OF START! USAGE:\n%s\n", usage);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateRows(char* optarg, const char* usage){
    int rows = 0;

    if(sscanf(optarg, "%d", &rows) != 1 || rows <= 0){
        fprintf(stderr, "WRONG NUMBER OF ROWS! ERROR CODE: 503. USAGE:\n%s\n", usage);
        exit(WRONG_NUM_OF_ROWS);
    }

}