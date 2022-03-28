#ifndef _GEN_H_
#define _GEN_H_

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

void makeConnectionFromNode ( int i, node* graph, entryG* entry);

#endif