#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "alloc.h"

entryG* allocEntryGen(void){
    entryG* entry = (entryG*) malloc (sizeof(*entry));

    return entry;
}

entryR* allocEntryRead(void){
    entryR* entry = (entryR*) malloc (sizeof(*entry));
    
    return entry;
}

int* allocPoints(char* optarg, entryR* entry){
    int size = strlen(optarg);

    for (int i = 0; i < size; i++){
        if (!isdigit(optarg[i]) && optarg[i] != ','){
            fprintf(stderr, "WRONG POINTS FOUND ! ERROR CODE: 612\n");
            exit(WRONG_POINTS);
        }
    }

    int* points = (int*) malloc (size * sizeof(*points));

    entry -> numberPoints = 0;

    int howManyRead = 0;
    while(true){
        if (sscanf(optarg, "%d,%n", &points[entry -> numberPoints], &howManyRead) != 1){
            break;
        }
        entry -> numberPoints++;
        optarg+= howManyRead;
    }

    if (entry -> numberPoints == 0 || (entry -> numberPoints % 2 != 0)){
        fprintf(stderr, "WRONG POINTS FOUND! ERROR CODE: 612\n");
        exit(WRONG_POINTS);
    }

    return points;
}