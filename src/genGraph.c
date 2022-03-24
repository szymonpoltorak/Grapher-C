#include <stdio.h>
#include <stdlib.h>
#include "genGraph.h"

double generateWeights(entryG* entry){
    return (double) rand()/RAND_MAX * (entry ->rangeEnd - entry ->rangeStart) + entry->rangeStart;
}

bool checkIfCoherentGen(node* graph, entryG* entry){
    return true;
}

void saveGraphToFile(entryG* entry, node* graph){
    int numOfNodes = entry->columns * entry->rows;
    char * fileName = entry->fileName;
    FILE* ofile = fopen(fileName,"w");

    fprintf(ofile,"%d %d\n",entry->rows, entry->columns);

    for (int i = 0; i < numOfNodes; i++ ){
        fprintf(ofile,"\t"); //tab
        for( int k = 0; k < 4; k++ ){
            int nodeNum = defineNodeNumber(i, k, entry->rows, entry->columns);
            double nodeWeight = graph[i].edgeWeight[k];
            if( graph[i].edgeExist[k] == true){
                fprintf(ofile," %d :%f ",nodeNum,nodeWeight);
            }
        }
        fprintf(ofile,"\n"); //  \n
    }
    fclose(ofile);
}

void generateMode(entryG* entry){

}


int defineNodeNumber (int i, int k, int rows, int columns){
    switch (k)
    {
    case 1: //up
        return i - columns;
        break;
    case 2: //right
       return i + 1;
        break;
    case 3: // down
        return i + columns;
        break;
    case 4: //left
        return i - 1;
        break;
    default:
        return 0;
        break;
    }
}
