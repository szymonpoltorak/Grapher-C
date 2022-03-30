#ifndef _GEN_H_
#define _GEN_H_

#define CHANCE 50
#define MAXNUMOFTRIES 500

#include "tools.h"

void generateMode(entryG* entry);

void saveGraphToFile(entryG* entry, node* graph);

double generateWeights(entryG* entry);

bool generateIfEdgeExist(short int mode);

void makeConnectionFromNode (int i, node* graph, entryG* entry);

#endif
