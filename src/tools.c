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
                        if(q == NULL){
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

    while(iterator->next != NULL){
        iterator = iterator->next;
    }

    iterator->next = (queue*) malloc(sizeof(queue));

    if (iterator->next == NULL) {
        fprintf(stderr, "NULL POINTER FOUND!!!\n");
        exit(NULL_POINTER_EXCEPTION);
    }

    iterator->next->node = data;
    iterator->next->next = NULL;
}

int popFromQueue(queue** q){
    if(isEmpty(*q) == true){
        return -1;
    }
    
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

bool ifParentBigger(Heap* heap, int index){
    int parent = (index - 1) / 2;

    if (index == 0){
        return false;
    }
    if (heap -> priorities[index] < heap -> priorities[parent]){
        return true;
    }
    return false;
}

void updatePriority(Heap* heap, int id, float priority){
    int index = heap -> nodesIndex[id];
    float prevPrio = heap -> priorities[index];

    heap -> priorities[index] = priority;

    if (prevPrio < priority){
        int temp = 0;
        while ((temp = returnSmallerIndex(heap, index)) >= 0){
            swapChildren(heap, index, temp);
            index = temp;
        }
    } else {
        while (ifParentBigger(heap, index) == true){
            swapPriorities(heap, index);
            index = (index - 1) / 2;
        }
    }
}

int returnSmallerIndex(Heap* heap, int parent){
    int smallerIndex = 0;
    int leftChild = 2 * parent + 1;
    int rightChild = 2 * parent + 2;

    if (leftChild >= heap -> length){
        return -1;
    }
    if (rightChild >= heap -> length){
        smallerIndex = leftChild;
    } else if (heap -> priorities[leftChild] < heap -> priorities[rightChild]){
        smallerIndex = leftChild;
    } else {
        smallerIndex = rightChild;
    }
    if(heap -> priorities[smallerIndex] < heap -> priorities[parent]){
        return smallerIndex;
    }
    
    return -1;
}

void swapPriorities(Heap* heap, int index){
    int parent = (index - 1) / 2;
    float temp = 0;

    temp = heap -> priorities[index];
    heap -> priorities[index] = heap ->priorities[parent];
    heap -> priorities[parent] = temp;

    temp = heap -> nodes[index];
    heap -> nodes[index] = heap ->nodes[parent];
    heap -> nodes[parent] = temp;

    heap -> nodesIndex[heap -> nodes[index]] = index;
    heap -> nodesIndex[heap -> nodes[parent]] = parent;
}

void swapChildren(Heap* heap, int index, int parent){
    float temp = 0;
    int tmp = 0;

    temp = heap -> priorities[index];
    heap -> priorities[index] = heap ->priorities[parent];
    heap -> priorities[parent] = temp;

    tmp = heap -> nodes[index];
    heap -> nodes[index] = heap ->nodes[parent];
    heap -> nodes[parent] = tmp;

    heap -> nodesIndex[heap -> nodes[index]] = index;
    heap -> nodesIndex[heap -> nodes[parent]] = parent;
}

void addToHeap(Heap* heap, float priority){
    int index = heap -> length;

    heap -> priorities[index] = priority;
    heap -> nodes[index] = index;
    heap -> length++;
    heap -> nodesIndex[index] = index;

    while (ifParentBigger(heap, index) == true){
        swapPriorities(heap, index);
        index = (index - 1) / 2;
    }
}

int popFromHeap(Heap* heap){
    int parent = 0;
    int index = 0;
    int toReturn = heap -> nodes[0];

    heap -> priorities[0] = heap -> priorities[--heap -> length];
    heap -> nodes[0] = heap -> nodes[heap -> length];
    heap -> nodesIndex[heap -> nodes[0]] = 0;

    while ((index = returnSmallerIndex(heap, parent)) >= 0){
        swapChildren(heap, parent, index);
        parent = index;
    }

    return toReturn;
}
