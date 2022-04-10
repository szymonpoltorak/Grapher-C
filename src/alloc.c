#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include "alloc.h"

extern const char* usage;

entryG* allocEntryGen(void){
    entryG* entry = (entryG*) malloc (sizeof(*entry));

    if (entry == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    entry -> fileName = NULL;
    entry -> columns = 0;
    entry -> mode = 0;
    entry -> rangeStart = 0;
    entry -> rangeEnd = 0;
    entry -> rows = 0;

    return entry;
}

entryR* allocEntryRead(entryG* entryG){
    entryR* entry = (entryR*) malloc (sizeof(*entry));

    if (entry == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        free(entryG);
        exit(NULL_POINTER_EXCEPTION);
    }

    entry -> points = NULL;
    entry -> fileName = NULL;
    entry -> numberPoints = 0;
    entry -> printFlag = 0;
    entry -> rows = 0;
    entry -> columns = 0;

    return entry;
}

node* allocGraph(int numOfNodes){
    node* graph = (node*) calloc (numOfNodes, sizeof(*graph));

    if (graph == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    for (int i = 0; i < numOfNodes; i++){
        for (short int j = 0; j < 4; j++){
            graph[i].edgeExist[j] = false;
            graph[i].edgeWeight[j] = -1;
            graph[i].nodeToConnect[j] = -1;
        }
    }
    return graph;
}

bool* allocVisited(int numOfNodes){
    bool* visited = (bool*)calloc(numOfNodes, sizeof(*visited));

    if (visited == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    for (int i = 0; i < numOfNodes; i++)
        visited[i] = false;

    return visited;
}

void allocPoints(char* optarg, entryR* entryR, entryG* entryG){
    int size = strlen(optarg);

    for (int i = 0; i < size; i++){
        if (!isdigit(optarg[i]) && optarg[i] != ','){
            fprintf(stderr, "WRONG POINTS FOUND ! USAGE:\n%s\n", usage);
            freeEntries(entryR, entryG);
            exit(WRONG_POINTS);
        }
    }
    int* points = (int*) malloc (size * sizeof(*points));
    
    if (points == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(NULL_POINTER_EXCEPTION);
    }

    int howManyRead = 0;
    while(true){
        if (sscanf(optarg, "%d%n", &points[entryR -> numberPoints], &howManyRead) != 1){
            break;
        }
        entryR -> numberPoints++;
        optarg+= howManyRead + 1;
        if (*optarg == 0)
            break;
    }

    if (entryR -> numberPoints == 0 || (entryR -> numberPoints % 2 != 0)){
        fprintf(stderr, "WRONG POINTS FOUND! USAGE:\n%s\n", usage);
        freeEntries(entryR, entryG);
        exit(WRONG_POINTS);
    }

    entryR -> points = points;
}

int* allocPredecessor (int numOfNodes){
    int* predecessor = (int*)calloc(numOfNodes, sizeof(*predecessor));

    if (predecessor == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    for (int i = 0; i < numOfNodes; i++)
        predecessor[i] = -1;    

    return predecessor;
}

float* allocFloatArray (int numOfNodes){
    float* array = (float*)calloc(numOfNodes, sizeof(*array));

    if (array == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    for (int i = 0; i < numOfNodes; i++)
        array[i] = FLT_MAX;

    return array;
}

int* allocPredecessorInOrder (int numOfNodes){
    int* predecessor = (int*)calloc(numOfNodes, sizeof(*predecessor));

    if (predecessor == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER! USAGE:\n%s\n", usage);
        exit(NULL_POINTER_EXCEPTION);
    }

    for (int i = 0; i < numOfNodes; i++)
        predecessor[i] = -1;    

    return predecessor;
}

int* allocIntArrays(int numOfNodes){
    int* array = (int*) calloc (numOfNodes, sizeof(*array));
    
    if (array == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
        exit(NULL_POINTER_EXCEPTION);
    }

    return array;
}

Heap* heapInit(int numOfNodes){
    Heap* heap = (Heap*) malloc (sizeof(*heap));

    if (heap == NULL){
        fprintf(stderr, "DEREFERNCING NULL POINTER!\n");
        exit(NULL_POINTER_EXCEPTION);        
    }

    heap -> numOfNodes = numOfNodes;
    heap -> length = 0;
    heap -> priorities = allocFloatArray(numOfNodes);
    heap -> nodes = allocIntArrays(numOfNodes);
    heap -> nodesIndex = allocIntArrays(numOfNodes);

    return heap;
}

void freeHeap(Heap* heap){
    free(heap -> priorities);
    free(heap -> nodes);
    free(heap -> nodesIndex);
    free(heap);
}

void freeEntryRead(entryR* entry){
    free(entry -> points);
    free(entry);
}

void freeEntries(entryR* entryR, entryG* entryG){
    free(entryG);
    freeEntryRead(entryR);
}

void freePathMemory(int* predecessors, float* weights, float* distance){
    free(distance);
    free(predecessors);
    free(weights);    
}

void freeReadFile(FILE* in, entryR* entry, node* graph){
    fclose(in);
    freeEntryRead(entry);
    if (graph != NULL)
        free(graph);
}

void freeReadMode(entryR* entry, node* graph){
    freeEntryRead(entry);
    free(graph);    
}