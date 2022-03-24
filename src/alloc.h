#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdbool.h>

#define NO_MODE_FOUND 230
#define WRONG_NUM_OF_ROWS 232
#define WRONG_NUM_OF_COL 233
#define WRONG_RANGE_OF_WAGES 234
#define NO_FLAG_FOUND 235
#define WRONG_POINTS 236
#define NO_COHERENT 237

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
    bool mode;
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

int* allocPoints(char* optarg, entryR* entry);

#endif