#ifndef _GEN_H_
#define _GEN_H_

#define CHANCE 50
#define MAXNUMOFTRIES 500
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include "alloc.h"

void generateMode(entryG* entry);

bool checkIfCoherentGen(node* graph, entryG* entry);

void saveGraphToFile(entryG* entry, node* graph);

double generateWeights(entryG* entry);

bool generateIfEdgeExist(short int mode);

void makeConnectionFromNode (int i, node* graph, entryG* entry);

typedef struct queue {
    int node;
    struct queue* next;
} queue;

void addToQueue(queue* q,int data);

queue* queInit(int data);

int popFromQueue(queue** q);

bool isEmpty(queue* q);

void displayQue(queue* q);

#endif
