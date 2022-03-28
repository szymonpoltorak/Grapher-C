#include <stdio.h>
#include <stdlib.h>
#include "genGraph.h"

#define CHANCE 5

double generateWeights(entryG* entry){
    return (double) rand()/RAND_MAX * (entry ->rangeEnd - entry ->rangeStart) + entry->rangeStart;
}

bool checkIfCoherentGen(node* graph, entryG* entry){
    int numOfNodes = entry->columns * entry->rows;
    bool *coherentFrom = (bool *) malloc(sizeof coherentFrom * numOfNodes);
    for ( int i = 0; i < numOfNodes; i++)
        coherentFrom[i] = false;

    for(int l = 0; l < numOfNodes; l++){
        int startingNode = l;
        bool *visited = (bool *) malloc(sizeof visited * numOfNodes);
        for ( int i = 0; i < numOfNodes; i++)
            visited[i] = false;

        que* q = NULL;
        q = queInit(startingNode);

        while(!isEmpty(q)){
            int currentNode = popFromQueue(&q);
            visited[currentNode] = true;
            for (int k = 0; k < 4; k++){
                if(graph[currentNode].edgeExist[k]){
                    if( visited[graph[currentNode].nodeToConnect[k]] == false ) {
                        if(q == NULL) {
                            q = queInit(graph[currentNode].nodeToConnect[k]);
                        } else {
                            addToQueue(q, graph[currentNode].nodeToConnect[k]);
                        }
                    }
                }
            }
        }
        int numOfNotVisited = 0;
        for ( int i = 0; i < numOfNodes; i++ ){
            if(visited[i] == false){
                numOfNotVisited++;
            }
        }

        free(visited);

        if(numOfNotVisited > 0){
            coherentFrom[l] = false;
        } else {
            coherentFrom[l] = true;
        }
    }
    int numOfNotChoherentFrom = 0;;
    for ( int i = 0; i < numOfNodes; i++ ){
        if(coherentFrom[i] == false)
           numOfNotChoherentFrom++;
    }
    if(numOfNotChoherentFrom > 0) {
        return false;
    } else {
        return true;
    }
}

void saveGraphToFile(entryG* entry, node* graph){
    int numOfNodes = entry->columns * entry->rows;
    char * fileName = entry->fileName;
    FILE* ofile = fopen(fileName,"w");

    fprintf(ofile,"%d %d\n",entry->rows, entry->columns);

    for (int i = 0; i < numOfNodes; i++ ){
        fprintf(ofile,"\t");
        for( int k = 0; k < 4; k++ ){
            if( graph[i].edgeExist[k] == true){
                fprintf(ofile," %d :%f ",graph[i].nodeToConnect[k],graph[i].edgeWeight[k]);
            }
        }
        fprintf(ofile,"\n");
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
        if (checkIfCoherentGen(graph,entry) == true){
            printf("Wygenerowano spojny\n");
        } else {
            printf("Wygenerowano niespojny\n");
        }
        saveGraphToFile(entry,graph);
        printf("Poprawnie wygenerowano graf!\n");
    }
    if(continueGen == false){
        printf("Przerwano generowanie grafu!\n");
    }
}

bool generateIfEdgeExist(short int mode){
    if (mode == 1) //ZAMIENIC PRZY MARGE
        return true;
    double i = (double) 100*rand()/RAND_MAX;
    if (i <= CHANCE)
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

que* queInit(int data){
    que* q = malloc(sizeof(que));
    q->node = data;
    q->next = NULL;
    return q;
}

void addToQueue(que* q, int data){
    que* iterator = q;
    while(iterator->next != NULL){
        iterator = iterator->next;
    }
    iterator->next = malloc(sizeof(que));
    iterator->next->node = data;
    iterator->next->next = NULL;
}

int popFromQueue( que** q){
    if( isEmpty(*q) == true){
        return -1;
    }
    
    que* tmp = *q;
    int data = tmp->node;
    *q = tmp->next;
    free(tmp);
    return data;
}

bool isEmpty( que* q ){
    if (q == NULL){
        return true;
    } else {
        return false;
    }
}

void displayQue(que* q){
    que* iterator = q;
    printf("K: ");
    while(iterator->next != NULL){
        printf("%d ---> ",iterator->node);
        iterator = iterator->next;
    }
    printf("%d\n",iterator->node);
}