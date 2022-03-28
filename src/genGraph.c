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
    int numOfTries = 0;
    int maxNumOfTries = 500;
    bool continueGen = true;

    for (int i = 0; i < numOfNodes; i++) {
            makeConnectionFromNode(i, graph, entry);
    }
    numOfTries++;

    while (entry->mode == 2 && continueGen == true && !checkIfCoherentGen(graph,entry)){

        for (int i = 0; i < numOfNodes; i++)
            makeConnectionFromNode(i, graph, entry);
        numOfTries++;
    
        if (numOfTries >= maxNumOfTries){
            printf("Dokonano %d losowań. Czy chcesz kontynuować? [Y/N]: ",numOfTries);
            char choice;
            scanf(" %c", &choice);

            if(choice == 'y' || choice == 'Y'){
                continueGen = true;
                maxNumOfTries += 500;
            } else {
                continueGen = false;
            }
        }
    }

    if(continueGen == true){
        saveGraphToFile(entry,graph);
        printf("Poprawnie wygenerowano graf!\n");
    }
    if(continueGen == false){
        printf("Przerwano generowanie grafu!\n");
    }
}

bool generateIfEdgeExist(short int mode){
    if (mode == 1)
        return true;
    double i = (double) rand()/RAND_MAX;
    if (i <= 0.9)
        return true;
    return false;
}

void makeConnectionFromNode ( int i, node* graph, entryG* entry){
    int columns = entry->columns;
    int rows = entry->rows;
    int mode = entry->mode;
    if ( i - columns >= 0 && i - columns < columns * rows){
            if(generateIfEdgeExist(mode)){
                graph[i].edgeExist[UP] = true;
                graph[i].nodeToConnect[UP] = i - columns;
                graph[i].edgeWeight[UP] = generateWeights(entry);

            }
        } else {
             graph[i].edgeExist[UP] = false;
        }
    if( i + 1 < columns * rows && (i+1)%columns != 0){
            if(generateIfEdgeExist(mode)){
                graph[i].edgeExist[RIGHT] = true;
                graph[i].nodeToConnect[RIGHT] = i + 1;
                graph[i].edgeWeight[RIGHT] = generateWeights(entry);
            }
        } else {
            graph[i].edgeExist[RIGHT] = false;
        }
    if ( i + columns > 0 && i + columns < columns * rows){
            if(generateIfEdgeExist(mode)){
                graph[i].edgeExist[DOWN] = true;
                graph[i].nodeToConnect[DOWN] = i + columns;
                graph[i].edgeWeight[DOWN] = generateWeights(entry);

            }
        } else {
             graph[i].edgeExist[DOWN] = false;
        }
     if( i - 1 >= 0 && i%columns != 0){
            if(generateIfEdgeExist(mode)){
                graph[i].edgeExist[LEFT] = true;
                graph[i].nodeToConnect[LEFT] = i - 1;
                graph[i].edgeWeight[LEFT] = generateWeights(entry);
            }
        } else {
            graph[i].edgeExist[LEFT] = false;
        }
}
