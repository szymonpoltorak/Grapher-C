#ifndef _GEN_H_
#define _GEN_H_

#include "alloc.h"

void generateMode(entryG* entry);

bool checkIfCoherentGen(node* graph, entryG* entry);

void saveGraphToFile(entryG* entry, node* graph);

double generateWeights(entryG* entry);

int defineNodeNumber(int i, int k, int rows, int columns);

bool generateIfEdgeExist(short int mode);

#endif