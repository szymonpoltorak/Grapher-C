#include <stdio.h>
#include <stdlib.h>
#include "readGraph.h"

static void saveGraphToFileRead(entryR* entry, node* graph){
    int numOfNodes = entry->columns * entry->rows;

    printf("%d %d\n",entry->rows, entry->columns);

    for (int i = 0; i < numOfNodes; i++ ){
        printf("\t");
        for (int k = 0; k < 4; k++ )
            if (graph[i].edgeExist[k] == true)
                printf(" %d :%f ",graph[i].nodeToConnect[k],graph[i].edgeWeight[k]);
        printf("\n");
    }
}

node* readFromFile(entryR* entry){
    FILE* in = fopen(entry ->fileName, "r");
    int numOfNodes = entry ->columns * entry -> rows;
    node* graph = allocGraph(numOfNodes);

    if (fscanf(in, "%d %d", &entry ->rows, &entry -> columns) != 2){
        fprintf(stderr, "ROWS AND COLUMNS NOT FOUND!\n");
        freeEntryRead(entry);
        free(graph);
        exit(NO_COL_ROWS_FOUND);
    }

    fgetc(in);
    for (int i = 0; i < numOfNodes; i++){
        char buff[1024];
        char* buf = buff;

        if (fgets(buf,1024,in) == NULL){
            fprintf(stderr, "NODES NOT FOUND!\n");
            free(graph);
            freeEntryRead(entry);
            exit(NO_NODES_FOUND);
        }

        insertGraph(entry, graph, i, buf);
    }

    fclose(in);
    return graph;
}

void insertGraph(entryR* entry, node* graph, int i, char* buf){
    int columns = entry->columns, rows = entry->rows;
    int node = 0, offset=0;
    double weight = 0;

    while(sscanf(buf, " %d :%lf %n", &node, &weight, &offset) == 2){
        buf+=offset;

            if (i - columns >= 0 && i - columns < columns * rows){
                if (node == i - columns){
                    graph[i].edgeExist[UP] = true;
                    graph[i].nodeToConnect[UP] = i - columns;
                    graph[i].edgeWeight[UP] = weight;
                }
            } else {
                graph[i].edgeExist[UP] = false;
            }
            if(i + 1 < columns * rows && (i+1)%columns != 0){
                if (node == i + 1){
                    graph[i].edgeExist[RIGHT] = true;
                    graph[i].nodeToConnect[RIGHT] = i + 1;
                    graph[i].edgeWeight[RIGHT] = weight;
                }
            } else {
                graph[i].edgeExist[RIGHT] = false;
            }
            if (i + columns > 0 && i + columns < columns * rows){
                if(node == i + columns){
                    graph[i].edgeExist[DOWN] = true;
                    graph[i].nodeToConnect[DOWN] = i + columns;
                    graph[i].edgeWeight[DOWN] = weight;
                }
            } else {
                graph[i].edgeExist[DOWN] = false;
            }
            if(i - 1 >= 0 && i%columns != 0){
                if(node == i - 1){
                    graph[i].edgeExist[LEFT] = true;
                    graph[i].nodeToConnect[LEFT] = i - 1;
                    graph[i].edgeWeight[LEFT] = weight;
                }
            } else {
                graph[i].edgeExist[LEFT] = false;
            }
        }
}

void findPath(node* graph, entryR* entry){
    
}

void printShortPath(entryR* entry, int* parents){

}

void printExtendedPath(entryR* entry, int* parents, double* weights){

}

void readMode(entryR* entry){
    node* graph = readFromFile(entry);
    int numOfNodes = entry -> columns * entry -> rows;

    printf("READ GRAPH:\n");
    saveGraphToFileRead(entry, graph);

    if (checkIfCoherent(graph, numOfNodes) != true){
        fprintf(stderr, "GRAPH IS NOT COHERENT!!!\n");
        freeEntryRead(entry);
        exit(NO_COHERENT);
    }
    else
        printf("GRAPH IS COHERENT!!\n");

    free(graph);
    freeEntryRead(entry);
}
