#ifndef _READ_H_
#define _READ_H_

#include "tools.h"

#define WRONG_ROWS_COLUMNS 198

void readMode(entryR* entry); 

node* readFromFile(entryR* entry);

bool insertGraph(entryR* entry, node* graph, int i, char* buf);

void findPath(node* graph, entryR* entry);

void printShortPath(entryR* entry, int* predecessors, int startPoint, int endPoint);

void printExtendedPath(entryR* entry, int* predecessors, float* weights, int startPoint, int endPoint);

#endif
