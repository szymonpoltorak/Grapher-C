#include <stdio.h>
#include <stdlib.h>
#include "genGraph.h"

double generateWeights(entryG* entry){
    return (double) rand()/RAND_MAX * (entry ->rangeEnd - entry ->rangeStart) + entry->rangeStart;
}

bool checkIfCoherentGen(node** graph, entryG* entry){
    return true;
}

void saveGraphToFile(entryG* entry, node** graph){

}

void generateMode(entryG* entry){

}