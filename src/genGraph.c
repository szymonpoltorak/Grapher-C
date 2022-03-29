#include <stdio.h>
#include <stdlib.h>
#include "genGraph.h"

double generateWeights(entryG* entry){
    return (double) rand()/RAND_MAX * (entry ->rangeEnd - entry ->rangeStart) + entry->rangeStart;
}

bool checkIfCoherentGen(node* graph, entryG* entry){
    int numOfNodes = entry->columns * entry->rows;

    for(int l = 0; l < numOfNodes; l++){
        int startingNode = l;
        bool *visited = allocVisited(numOfNodes);
        queue* q = queInit(startingNode);

        visited[startingNode] = true;
        while(!isEmpty(q)){
            int currentNode = popFromQueue(&q);

            for (int k = 0; k < 4; k++){
                if(graph[currentNode].edgeExist[k]){
                    if( visited[graph[currentNode].nodeToConnect[k]] == false ) {
                        if(q == NULL) {
                            q = queInit(graph[currentNode].nodeToConnect[k]);
                        } else {
                            addToQueue(q, graph[currentNode].nodeToConnect[k]);
                        }
                        visited[graph[currentNode].nodeToConnect[k]] = true;
                    }
                }
            }
        }

        for (int i = 0; i < numOfNodes; i++ ){
            if(visited[i] == false){
                free(visited);
                return false;
            }
        }
        free(visited);   
    }
    return true;
}

void saveGraphToFile(entryG* entry, node* graph){
    int numOfNodes = entry->columns * entry->rows;
    char * fileName = entry->fileName;
    FILE* ofile = fopen(fileName,"w");

    fprintf(ofile,"%d %d\n",entry->rows, entry->columns);

    for (int i = 0; i < numOfNodes; i++ ){
        fprintf(ofile,"\t");
        for (int k = 0; k < 4; k++ )
            if (graph[i].edgeExist[k] == true)
                fprintf(ofile," %d :%f ",graph[i].nodeToConnect[k],graph[i].edgeWeight[k]);
        fprintf(ofile,"\n");
    }
    fclose(ofile);
}

void generateMode(entryG* entry){
    int numOfNodes = entry->columns * entry->rows;
    node *graph = allocGraphGen(numOfNodes);
    int numOfTries = 0;
    int maxNumOfTries = MAXNUMOFTRIES;
    bool continueGen = true;

    for (int i = 0; i < numOfNodes; i++)
        makeConnectionFromNode(i, graph, entry);
    numOfTries++;

    while (entry->mode == EDGE && continueGen == true && !checkIfCoherentGen(graph,entry)){
        for (int i = 0; i < numOfNodes; i++)
            makeConnectionFromNode(i, graph, entry);
        numOfTries++;

        if (numOfTries >= maxNumOfTries){
            printf("Dokonano %d losowań. Czy chcesz kontynuować? [Y/N]: ",numOfTries);
            char choice = 0;
            scanf(" %c", &choice);

            if(choice == 'y' || choice == 'Y'){
                continueGen = true;
                maxNumOfTries += MAXNUMOFTRIES;
            } else {
                continueGen = false;
            }
        }
    }

    if(continueGen == true){
        saveGraphToFile(entry,graph);
        printf("Poprawnie wygenerowano graf!\n");
    }
    if(continueGen == false)
        printf("Przerwano generowanie grafu!\n");
    free(graph);
}

bool generateIfEdgeExist(short int mode){
    if (mode == WEIGHT)
        return true;
    double i = (double) rand()/RAND_MAX * 100;
    if (i <= CHANCE)
        return true;
    return false;
}

void makeConnectionFromNode (int i, node* graph, entryG* entry){
    int columns = entry->columns;
    int rows = entry->rows;
    int mode = entry->mode;

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

queue* queInit(int data){
    queue* q = (queue*) malloc(sizeof(queue));

    if (q == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!");
        exit(NULL_POINTER_EXCEPTION);        
    }

    q->node = data;
    q->next = NULL;
    return q;
}

void addToQueue(queue* q, int data){
    queue* iterator = q;

    while(iterator->next != NULL)
        iterator = iterator->next;

    iterator->next = (queue*) malloc(sizeof(queue));
    iterator->next->node = data;
    iterator->next->next = NULL;
}

int popFromQueue(queue** q){
    if(isEmpty(*q) == true)
        return -1;
    
    queue* tmp = *q;
    int data = tmp->node;
    *q = tmp->next;

    free(tmp);
    return data;
}

bool isEmpty(queue* q){
    if (q == NULL)
        return true;
    else
        return false;
}

void displayQue(queue* q){
    queue* iterator = q;
    printf("K: ");
    while(iterator->next != NULL){
        printf("%d ---> ",iterator->node);
        iterator = iterator->next;
    }
    printf("%d\n",iterator->node);
}
