#include <stdio.h>
#include <stdlib.h>
#include "genGraph.h"

float generateWeights(entryG* entry){
    return (float) rand()/RAND_MAX * (entry ->rangeEnd - entry ->rangeStart) + entry->rangeStart;
}

void saveGraphToFile(entryG* entry, node* graph){
    int numOfNodes = entry->columns * entry->rows;
    char * fileName = entry->fileName;
    FILE* ofile = fopen(fileName,"w");

    fprintf(ofile,"%d %d\n",entry->rows, entry->columns);

    for (int i = 0; i < numOfNodes; i++ ){
        fprintf(ofile,"\t");
        for (short int k = 0; k < 4; k++ ){
            if (graph[i].edgeExist[k] == true){
                fprintf(ofile," %d :%f ",graph[i].nodeToConnect[k],graph[i].edgeWeight[k]);
            }
        }
        fprintf(ofile,"\n");
    }
    fclose(ofile);
}

void generateMode(entryG* entry){
    int numOfNodes = entry->columns * entry->rows;
    node *graph = allocGraph(numOfNodes);
    int numOfTries = 0;
    int maxNumOfTries = MAXNUMOFTRIES;
    bool continueGen = true;

    for (int i = 0; i < numOfNodes; i++){
        makeConnectionFromNode(i, graph, entry);
    }
    numOfTries++;

    while (entry->mode == EDGE && continueGen == true && !checkIfCoherent(graph,numOfNodes)){
        for (int i = 0; i < numOfNodes; i++){
            makeConnectionFromNode(i, graph, entry);
        }
        numOfTries++;

        if (numOfTries >= maxNumOfTries){
            printf("Dokonano %d losowań. Czy chcesz kontynuować? [Y/N]: ",numOfTries);
            char choice = 0;

            while (true) {
                if (scanf(" %c", &choice) != 1){
                    fprintf(stderr,"COULDN'T READ PROPPER ANSWER!\n");
                }
                if (choice == 'y' || choice == 'Y') {
                    continueGen = true;
                    maxNumOfTries += MAXNUMOFTRIES;
                    break;
                } else if (choice == 'n' || choice == 'N') {
                    continueGen = false;
                    break;
                } else {
                    fprintf(stderr, "UNKNOWN OPTION!!\n");
                }
            }
        }
    }

    if(continueGen == true){
        saveGraphToFile(entry,graph);
        printf("Poprawnie wygenerowano graf!\n");
    } else{
        printf("Przerwano generowanie grafu!\n");
    }

    free(graph);
    free(entry);
}

bool generateIfEdgeExist(short int mode){
    if (mode == WEIGHT){
        return true;
    }
    float i = (float) rand()/RAND_MAX * 100;
    if (i <= CHANCE){
        return true;
    }
    return false;
}

void makeConnectionFromNode (int i, node* graph, entryG* entry){
    int columns = entry->columns;
    int rows = entry->rows;
    short int mode = entry->mode;

    if (i - columns >= 0 && i - columns < columns * rows){
        if(generateIfEdgeExist(mode)){
            graph[i].edgeExist[UP] = true;
            graph[i].nodeToConnect[UP] = i - columns;
            graph[i].edgeWeight[UP] = generateWeights(entry);
        }
    } else {
        graph[i].edgeExist[UP] = false;
    }
    if(i + 1 < columns * rows && (i+1)%columns != 0){
        if(generateIfEdgeExist(mode)){
            graph[i].edgeExist[RIGHT] = true;
            graph[i].nodeToConnect[RIGHT] = i + 1;
            graph[i].edgeWeight[RIGHT] = generateWeights(entry);
        }
    } else {
        graph[i].edgeExist[RIGHT] = false;
    }
    if (i + columns > 0 && i + columns < columns * rows){
        if(generateIfEdgeExist(mode)){
            graph[i].edgeExist[DOWN] = true;
            graph[i].nodeToConnect[DOWN] = i + columns;
            graph[i].edgeWeight[DOWN] = generateWeights(entry);
        }
    } else {
        graph[i].edgeExist[DOWN] = false;
    }
    if(i - 1 >= 0 && i%columns != 0){
       if(generateIfEdgeExist(mode)){
            graph[i].edgeExist[LEFT] = true;
            graph[i].nodeToConnect[LEFT] = i - 1;
            graph[i].edgeWeight[LEFT] = generateWeights(entry);
        }
    } else {
        graph[i].edgeExist[LEFT] = false;
    }
}
