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

void displayQue(queue* q);

#endif
