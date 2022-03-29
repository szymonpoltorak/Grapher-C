#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

extern const char* usage;

void ifReadMode(short int mode, entryR* entryR, entryG* entryG){
    if (mode != READ){
        fprintf(stderr, "IT IS NOT READ MODE!\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(NOT_READ_MODE);
    }
}

void validateFileName(char* optarg, entryR* entryR, entryG* entryG){
    FILE* in = fopen(optarg, "r");

    if (in == NULL){
        fprintf(stderr, "FILE DOES NOT EXIST! USAGE:\n %s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_FILE_FOUND);
    }
    fclose(in);
}

void validateRangeEnd(char* optarg, entryR* entryR, entryG* entryG){
    double end = 0;

    if (sscanf(optarg, "%lf", &end) != 1 || end <= 0){
        fprintf(stderr, "WRONG END! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateColumns(char* optarg, entryR* entryR, entryG* entryG){
    int columns = 0;

    if(sscanf(optarg, "%d", &columns) != 1 || columns <= 0){
        fprintf(stderr, "WRONG NUMBER OF COLUMNS! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_COL);        
    }
}

void validateRangeStart(char* optarg, entryR* entryR, entryG* entryG){
    int start = 0;

    if(sscanf(optarg, "%d", &start) != 1 || start < 0){
        fprintf(stderr, "WRONG NUMBER OF START! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }
}

void validateRows(char* optarg, entryR* entryR, entryG* entryG){
    int rows = 0;

    if(sscanf(optarg, "%d", &rows) != 1 || rows <= 0){
        fprintf(stderr, "WRONG NUMBER OF ROWS! ERROR CODE: 503. USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_ROWS);
    }
}

void ifModeWasDeclared(short int mode, entryR* entryR, entryG* entryG){
    if (mode != NO_MODE){
        fprintf(stderr, "MODE WAS ALREADY DECLARED !!!\n Usage:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(MULTIPILE_MODE_DECLARATION);
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
        fprintf(stderr, "FILE NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_FILE_FOUND);
    }
    if (checkRangeStart(entryG -> rangeStart) == EXIT_FAILURE){
        fprintf(stderr, "RANGE START NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES);
    }
    if (checkRangeEnd(entryG -> rangeEnd) == EXIT_FAILURE){
        fprintf(stderr, "RANGE END NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_RANGE_OF_WAGES );
    }
    if (checkRows(entryG -> rows) == EXIT_FAILURE){
        fprintf(stderr, "ROWS NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_ROWS);
    }
    if (checkColumns(entryG -> columns) == EXIT_FAILURE){
        fprintf(stderr, "COLUMNS NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_NUM_OF_COL);
    } 
    if (checkMode(entryG -> mode) == EXIT_FAILURE){
        fprintf(stderr, "MODE NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_MODE_FOUND);  
    }                     
}

void checkDataRead(entryR* entryR, entryG* entryG){
    if (checkFileName(entryR -> fileName) == EXIT_FAILURE){
        fprintf(stderr, "FILE NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_FILE_FOUND);
    }    
    if (checkPrintFlag(entryR -> printFlag) == EXIT_FAILURE){
        fprintf(stderr, "PRINT FLAG NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(NO_FLAG_FOUND);
    }
    if (checkPoints(entryR -> points) == EXIT_FAILURE){
        fprintf(stderr, "POINTS NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_POINTS);
    }
    if (checkNumberPoints(entryR -> numberPoints) == EXIT_FAILURE){
        fprintf(stderr, "NUMBER OF POINTS NOT FOUND! USAGE:\n%s\n", usage);
        freeAll(entryR, entryG);
        exit(WRONG_POINTS);
    }
}
