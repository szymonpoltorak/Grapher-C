#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "alloc.h"

entryG* allocEntryGen(void){
    entryG* entry = (entryG*) malloc (sizeof(*entry));

    if (entry == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
        exit(EXIT_FAILURE);
    }

    entry -> fileName = NULL;
    entry -> columns = 0;
    entry -> mode = 0;
    entry -> rangeStart = 0;
    entry -> rangeEnd = 0;
    entry -> rows = 0;

    return entry;
}

entryR* allocEntryRead(void){
    entryR* entry = (entryR*) malloc (sizeof(*entry));

    if (entry == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
        exit(EXIT_FAILURE);
    }

    entry -> points = NULL;
    entry -> fileName = NULL;
    entry -> numberPoints = 0;
    entry -> printFlag = 0;

    return entry;
}

void allocPoints(char* optarg, entryR* entryR, entryG* entryG){
    int size = strlen(optarg);

    for (int i = 0; i < size; i++){
        if (!isdigit(optarg[i]) && optarg[i] != ','){
            fprintf(stderr, "WRONG POINTS FOUND ! ERROR CODE: 612\n");
            freeAll(entryR, entryG);
            exit(WRONG_POINTS);
        }
    }
    int* points = (int*) malloc (size * sizeof(*points));
    
    if (points == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
        freeAll(entryR, entryG);
        exit(EXIT_FAILURE);
    }    

    int howManyRead = 0;
    while(true){
        if (sscanf(optarg, "%d,%n", &points[entryR -> numberPoints], &howManyRead) != 1){
            break;
        }
        entryR -> numberPoints++;
        optarg+= howManyRead;
    }

    if (entryR -> numberPoints == 0 || (entryR -> numberPoints % 2 != 0)){
        fprintf(stderr, "WRONG POINTS FOUND! ERROR CODE: 612\n");
        freeAll(entryR, entryG);
        exit(WRONG_POINTS);
    }

    entryR -> points = points;
}

void freeEntryRead(entryR* entry){
    free(entry -> points);
    free(entry);
}

void freeAll(entryR* entryR, entryG* entryG){
    free(entryG);
    freeEntryRead(entryR);
}
