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
            if( graph[i].edgeExist[k] == true){
                fprintf(ofile," %d :%f ",graph[i].nodeToConnect[k],graph[i].edgeWeight[k]);
            }
        }
        fprintf(ofile,"\n"); //  \n
    }
    fclose(ofile);
}

void generateMode(entryG* entry){
    int numOfNodes = entry->columns * entry->rows;
    node *graph = malloc(sizeof (node) * numOfNodes );

    for (int i = 0; i < numOfNodes; i++){
        //zrob w gore
        if ( i - entry->columns > 0 && i - entry->columns < numOfNodes){
            if(generateIfEdgeExist(entry->mode)){
                graph[i].edgeExist[0] = true;
                graph[i].nodeToConnect[0] = i - entry->columns;
                graph[i].edgeWeight[0] = generateWeights(entry);

            }
        } else {
             graph[i].edgeExist[0] = false;
        }
        //zrob w prawo
        if( i + 1 < numOfNodes && (i+1)%entry->columns != 0){
            if(generateIfEdgeExist(entry->mode)){
                graph[i].edgeExist[1] = true;
                graph[i].nodeToConnect[1] = i + 1;
                graph[i].edgeWeight[1] = generateWeights(entry);
            }
        } else {
            graph[i].edgeExist[1] = false;
        }
        //zrob w dol
        if ( i + entry->columns > 0 && i + entry->columns < numOfNodes){
            if(generateIfEdgeExist(entry->mode)){
                graph[i].edgeExist[2] = true;
                graph[i].nodeToConnect[2] = i + entry->columns;
                graph[i].edgeWeight[2] = generateWeights(entry);

            }
        } else {
             graph[i].edgeExist[2] = false;
        }
        //zrob w lewo
        if( i - 1 >= 0 && i%entry->columns != 0){
            if(generateIfEdgeExist(entry->mode)){
                graph[i].edgeExist[3] = true;
                graph[i].nodeToConnect[3] = i - 1;
                graph[i].edgeWeight[3] = generateWeights(entry);
            }
        } else {
            graph[i].edgeExist[3] = false;
        }
    }
    saveGraphToFile(entry,graph);

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

bool generateIfEdgeExist(short int mode){
    if (mode == 1)
        return true;
    double i = (double) rand()/RAND_MAX;
    if (i >= 0.5)
        return true;
    return false;
}
