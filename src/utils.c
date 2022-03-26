#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void ifReadMode(const char* usage, short int mode, entryR* entryR, entryG* entryG){
    if (mode != READ){
        fprintf(stderr, "IT IS NOT READ MODE!\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }
}

void validateFileName(char* optarg, const char* usage, entryR* entryR, entryG* entryG){
    FILE* in = fopen(optarg, "r");

    if (in == NULL){
        fprintf(stderr, "FILE DOES NOT EXIST! USAGE:\n %s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_FILE_FOUND);
    }
    fclose(in);
}

void validateRangeEnd(char* optarg, const char* usage, entryR* entryR, entryG* entryG){
    double end = 0;

    if (sscanf(optarg, "%lf", &end) != 1 || end <= 0){
        fprintf(stderr, "WRONG END! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateColumns(char* optarg, const char* usage, entryR* entryR, entryG* entryG){
    int columns = 0;

    if(sscanf(optarg, "%d", &columns) != 1 || columns <= 0){
        fprintf(stderr, "WRONG NUMBER OF COLUMNS! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_COL);        
    }
}

void validateRangeStart(char* optarg, const char* usage, entryR* entryR, entryG* entryG){
    int start = 0;

    if(sscanf(optarg, "%d", &start) != 1 || start < 0){
        fprintf(stderr, "WRONG NUMBER OF START! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateRows(char* optarg, const char* usage, entryR* entryR, entryG* entryG){
    int rows = 0;

    if(sscanf(optarg, "%d", &rows) != 1 || rows <= 0){
        fprintf(stderr, "WRONG NUMBER OF ROWS! ERROR CODE: 503. USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_ROWS);
    }
}

void ifModeWasDeclared(const char* usage, short int mode, entryR* entryR, entryG* entryG){
    if (mode != NO_MODE){
        fprintf(stderr, "MODE WAS ALREADY DECLARED !!!\n Usage:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
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

void checkDataGen(entryG* entryG, entryR* entryR){
    if (checkFileName(entryG -> fileName) == EXIT_FAILURE){
        fprintf(stderr, "FILE NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }
    if (checkRangeStart(entryG -> rangeStart) == EXIT_FAILURE){
        fprintf(stderr, "RANGE START NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);        
    }
    if (checkRangeEnd(entryG -> rangeEnd) == EXIT_FAILURE){
        fprintf(stderr, "RANGE END NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);        
    }
    if (checkRows(entryG -> rows) == EXIT_FAILURE){
        fprintf(stderr, "ROWS NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);        
    }
    if (checkColumns(entryG -> columns) == EXIT_FAILURE){
        fprintf(stderr, "COLUMNS NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);        
    } 
    if (checkMode(entryG -> mode) == EXIT_FAILURE){
        fprintf(stderr, "MODE NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);        
    }                     
}

void checkDataRead(entryR* entryR, entryG* entryG){
    if (checkFileName(entryR -> fileName) == EXIT_FAILURE){
        fprintf(stderr, "FILE NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }    
    if (checkPrintFlag(entryR -> printFlag) == EXIT_FAILURE){
        fprintf(stderr, "PRINT FLAG NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }
    if (checkPoints(entryR -> points) == EXIT_FAILURE){
        fprintf(stderr, "POINTS NOT FOUND!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }
    if (checkNumberPoints(entryR -> numberPoints) == EXIT_FAILURE){
        fprintf(stderr, "NUMBER OF POINTS NOT FOUND\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }
}