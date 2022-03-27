#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdbool.h>

#define NO_MODE_FOUND 230
#define WRONG_POINTS 236
#define NO_COHERENT 237
#define NULL_POINTER_EXCEPTION 228

#define WEIGHT 1
#define EDGE 2
#define RANDOM 3 
#define READ 4
#define EXTENDED true
#define STANDARD false

typedef struct entryRead {
    char* fileName;
    bool printFlag;
    int* points;
    int numberPoints;
} entryR;

typedef struct entryGen {
    int rows;
    int columns;
    double rangeStart;
    double rangeEnd;
    short int mode;
    char* fileName;
} entryG;

typedef struct node {
    bool* edgeExist;
    double* edgeWeight;
} node;

typedef struct graphRead {
    node** graph;
    int rows;
    int columns;
} graphR;

entryG* allocEntryGen(void);

entryR* allocEntryRead(void);

void allocPoints(char* optarg, entryR* entryR, entryG* entryG);

void freeEntryRead(entryR* entry);

void freeAll(entryR* entryR, entryG* entryG);

#endif