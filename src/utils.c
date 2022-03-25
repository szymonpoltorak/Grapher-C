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

static int checkFileName(char* fileName){
    if(fileName == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkPrintFlag(short int printFlag){
    if(printFlag != EXTENDED && printFlag != STANDARD)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkRangeStart(double rangeStart){
    if(rangeStart < 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkRangeEnd(double rangeEnd){
    if (rangeEnd <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkRows(int rows){
    if (rows <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkColumns(int columns){
    if (columns <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkMode(short int mode){
    if (mode == 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkPoints(int* points){
    if (points == NULL)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static int checkNumberPoints(int numberPoints){
    if (numberPoints <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void checkDataGen(entryG* entry){
    if (checkFileName(entry -> fileName) == EXIT_FAILURE){
        fprintf(stderr, "FILE NOT FOUND!\n");
        exit(EXIT_FAILURE);
    }
    if (checkRangeStart(entry -> rangeStart) == EXIT_FAILURE){
        fprintf(stderr, "RANGE START NOT FOUND!\n");
        exit(EXIT_FAILURE);        
    }
    if (checkRangeEnd(entry -> rangeEnd) == EXIT_FAILURE){
        fprintf(stderr, "RANGE END NOT FOUND!\n");
        exit(EXIT_FAILURE);        
    }
    if (checkRows(entry -> rows) == EXIT_FAILURE){
        fprintf(stderr, "ROWS NOT FOUND!\n");
        exit(EXIT_FAILURE);        
    }
    if (checkColumns(entry -> columns) == EXIT_FAILURE){
        fprintf(stderr, "COLUMNS NOT FOUND!\n");
        exit(EXIT_FAILURE);        
    } 
    if (checkMode(entry -> mode) == EXIT_FAILURE){
        fprintf(stderr, "MODE NOT FOUND!\n");
        exit(EXIT_FAILURE);        
    }                     
}

void checkDataRead(entryR* entry){
    if (checkFileName(entry -> fileName) == EXIT_FAILURE){
        fprintf(stderr, "FILE NOT FOUND!\n");
        exit(EXIT_FAILURE);
    }    
    if (checkPrintFlag(entry -> printFlag) == EXIT_FAILURE){
        fprintf(stderr, "PRINT FLAG NOT FOUND!\n");
        exit(EXIT_FAILURE);
    }
    if (checkPoints(entry -> points) == EXIT_FAILURE){
        fprintf(stderr, "POINTS NOT FOUND!\n");
        exit(EXIT_FAILURE);
    }
    if (checkNumberPoints(entry -> numberPoints) == EXIT_FAILURE){
        fprintf(stderr, "NUMBER OF POINTS NOT FOUND\n");
        exit(EXIT_FAILURE);
    }
}