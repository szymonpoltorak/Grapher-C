#include <stdio.h>
#include <stdlib.h>
#include "enters.h"
#include "utils.h"

extern const char* usage;

void enterStandardPrintFlag(entryR* entryR, entryG* entryG, int mode){
    ifModeWasDeclared(mode, entryR, entryG);
    ifReadMode(mode, entryR, entryG);
    entryR -> printFlag = STANDARD;
}

void enterExtendedPrintFlag(entryR* entryR, entryG* entryG, int mode){
    ifModeWasDeclared(mode, entryR, entryG);
    ifReadMode(mode, entryR, entryG);
    entryR -> printFlag = EXTENDED;    
}

void enterFile(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);
    validateFileName(optarg, entryR, entryG);

    if (mode == READ){
        entryR -> fileName = optarg;
    } 
    else if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        entryG -> fileName = optarg;
    } 
    else {
        fprintf(stderr, "UNKNOWN MODE FOUND!\n");
        exit(NO_MODE_FOUND);
    }
}

void enterRows(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);

    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        validateRows(optarg, entryR, entryG);
        entryG -> rows = atoi(optarg);
    } 
    else if (mode == READ){
        fprintf(stderr, "ROWS ARE NOT USED IN READ MODE! USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(WRONG_MODE);
    } 
    else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }
}

void enterColumns(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);

    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        validateColumns(optarg, entryR, entryG);
        entryG -> columns = atoi(optarg);
    } 
    else if (mode == READ) {
        fprintf(stderr, "COLUMNS ARE NOT BEING DECLARED IN READ MODE. USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(WRONG_MODE);
    } 
    else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }    
}

void enterRangeStart(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);

    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        validateRangeStart(optarg, entryR, entryG);
        entryG -> rangeStart = atof(optarg);
    }
    else if (mode == READ) {
        fprintf(stderr, "RANGE START IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);//
        freeEntries(entryR, entryG);
        exit(WRONG_MODE);
    }
    else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }
}

void enterRangeEnd(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);

    if (mode == WEIGHT || mode == EDGE || mode == RANDOM){
        validateRangeEnd(optarg, entryR, entryG);
        entryG -> rangeEnd = atof(optarg);
    }
    else if (mode == READ) {
        fprintf(stderr, "RANGE END IS NOT USED IN READ MODE! USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(WRONG_MODE);
    }
    else {
        fprintf(stderr, "UNKNOWN MODE !!\n");
        exit(NO_MODE_FOUND);
    }
}

void enterPoints(entryR* entryR, entryG* entryG, int mode, char* optarg){
    ifModeWasDeclared(mode, entryR, entryG);
    ifReadMode(mode, entryR, entryG);
    allocPoints(optarg, entryR, entryG);    
}

short int enterWageMode(entryR* entryR, entryG* entryG, int mode){
    ifModeWasMultiplied(mode, entryR, entryG);
    entryG -> mode = WEIGHT;

    return WEIGHT;
}

short int enterReadMode(entryR* entryR, entryG* entryG, int mode){
    ifModeWasMultiplied(mode, entryR, entryG);
    return READ;
}

short int enterEdgeMode(entryR* entryR, entryG* entryG, int mode){
    ifModeWasMultiplied(mode, entryR, entryG);
    entryG -> mode = EDGE;

    return EDGE;
}

short int enterRandomMode(entryR* entryR, entryG* entryG, int mode){
    ifModeWasMultiplied(mode, entryR, entryG);
    entryG -> mode = RANDOM;

    return RANDOM;
}