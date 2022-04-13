#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

static int calculateNode(int index, int numOfNodes){
    return (index + 1) % numOfNodes;
}

bool checkIfCoherent(node* graph, int numOfNodes){
    int* queue = allocQueue(numOfNodes);

    for(int l = 0; l < numOfNodes; l++){
        int startingNode = l;
        bool *visited = allocVisited(numOfNodes);
        int reader = 0;
        int writer = 0;

        queue[writer] = startingNode;
        visited[startingNode] = true;
        writer = calculateNode(writer, numOfNodes);
        
        while(reader != writer){
            int currentNode = queue[reader];
            reader = calculateNode(reader, numOfNodes);

            for (short int k = 0; k < 4; k++){
                int aim = graph[currentNode].nodeToConnect[k];
                if (graph[currentNode].edgeExist[k] == true){
                    if (visited[aim] != true && aim != -1){
                        visited[aim] = true;
                        queue[writer] = aim;
                        writer = calculateNode(writer, numOfNodes);
                    }
                }
            }
        }

        for (int i = 0; i < numOfNodes; i++ ){
            if(visited[i] == false){
                free(visited);
                free(queue);
                return false;
            }
        }
        free(visited);
    }
    free(queue);

    return true;
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
