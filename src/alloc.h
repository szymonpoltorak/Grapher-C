#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdbool.h>
#include <stdio.h>

#define NO_MODE_FOUND 226
#define WRONG_POINTS 236
#define NO_COHERENT 237
#define NULL_POINTER_EXCEPTION 228
#define NO_COL_ROWS_FOUND 223
#define NO_NODES_FOUND 220

#define WEIGHT 1
#define EDGE 2
#define RANDOM 3 
#define READ 4
#define EXTENDED 5
#define STANDARD 6

typedef struct Heap {
    int numOfNodes;
    int length;
    float* priorities;
    int* nodes;
    int* nodesIndex;
} Heap;

typedef struct entryRead {
    int rows;
    int columns;
    char* fileName;
    short int printFlag;
    int* points;
    int numberPoints;
} entryR;

typedef struct entryGen {
    int rows;
    int columns;
    float rangeStart;
    float rangeEnd;
    short int mode;
    char* fileName;
} entryG;

typedef struct node {
    bool edgeExist[4]; 
    float edgeWeight[4]; 
    int nodeToConnect[4];
} node;

entryG* allocEntryGen(void);

entryR* allocEntryRead(entryG* entryG);

void allocPoints(char* optarg, entryR* entryR, entryG* entryG);

int* allocPredecessor (int numOfNodes);

float* allocFloatArray (int numOfNodes);

int* allocPredecessorInOrder (int numOfNodes);

void freeEntryRead(entryR* entry);

void freeEntries(entryR* entryR, entryG* entryG);

node* allocGraph(int numOfNodes);

bool* allocVisited(int numOfNodes);

void freePathMemory(int* predecessors, float* weights, float* distance);

void freeReadFile(FILE* in, entryR* entry, node* graph);

void freeReadMode(entryR* entry, node* graph);

void freeHeap(Heap* heap);

int* allocIntArrays(int numOfNodes);

Heap* heapInit(int numOfNodes);

#endif
