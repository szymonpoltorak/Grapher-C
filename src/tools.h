#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "alloc.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

typedef struct queue {
    int node;
    struct queue* next;
} queue;

bool checkIfCoherent(node* graph, int numOfNodes);

void addToQueue(queue* q,int data);

queue* queInit(int data);

int popFromQueue(queue** q);

bool isEmpty(queue* q);

bool ifParentBigger(Heap* heap, int index);

void updatePriority(Heap* heap, int id, float priority);

int returnSmallerIndex(Heap* heap, int parent);

void swapPriorities(Heap* heap, int index);

void swapChildren(Heap* heap, int index, int parent);

void addToHeap(Heap* heap, float priority);

int popFromHeap(Heap* heap);

#endif
