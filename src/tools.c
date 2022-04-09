#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

bool checkIfCoherent(node* graph, int numOfNodes){
    for(int l = 0; l < numOfNodes; l++){
        int startingNode = l;
        bool *visited = allocVisited(numOfNodes);
        queue* q = queInit(startingNode);

        visited[startingNode] = true;
        while(!isEmpty(q)){
            int currentNode = popFromQueue(&q);

            for (short int k = 0; k < 4; k++){
                if(graph[currentNode].edgeExist[k]){
                    if( visited[graph[currentNode].nodeToConnect[k]] == false ) {
                        if(q == NULL)
                            q = queInit(graph[currentNode].nodeToConnect[k]);
                        else
                            addToQueue(q, graph[currentNode].nodeToConnect[k]);
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

queue* queInit(int data){
    queue* q = (queue*) malloc(sizeof(queue));

    if (q == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
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

    if (iterator->next == NULL) {
        fprintf(stderr, "NULL POINTER FOUND!!!\n");
        exit(NULL_POINTER_EXCEPTION);
    }

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
