#ifndef _READ_H_
#define _READ_H_

#include "alloc.h"

void readMode(entryR* entry); 

graphR** readFromFile(entryR* entry);

bool checkIfCoherentRead(graphR** graph, entryR* entry);

void findPath(graphR** graph, entryR* entry);

void printShortPath(entryR* entry, int* parents);

void printExtendedPath(entryR* entry, int* parents, double* weights);

#endif