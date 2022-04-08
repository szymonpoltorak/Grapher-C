#include <stdio.h>
#include <stdlib.h>
#include "readGraph.h"

static bool checkRowsCols(entryR* entry){
    int rows = entry -> rows;
    int col = entry -> columns;

    if (rows <= 0 || col <= 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

node* readFromFile(entryR* entry){
    FILE* in = fopen(entry ->fileName, "r");

    if (fscanf(in, "%d %d", &entry ->rows, &entry -> columns) != 2){
        fprintf(stderr, "ROWS AND COLUMNS NOT FOUND!\n");
        freeReadFile(in, entry, NULL);
        exit(NO_COL_ROWS_FOUND);
    }
    if (checkRowsCols(entry) == EXIT_FAILURE){
        fprintf(stderr, "WRONG NUMBER OF ROWS OR COLUMNS!!\n");
        freeReadFile(in, entry, NULL);
        exit(WRONG_ROWS_COLUMNS);
    }

    int numOfNodes = entry ->columns * entry -> rows;
    node* graph = allocGraph(numOfNodes);

    fgetc(in);
    for (int i = 0; i < numOfNodes; i++){
        char buff[1024];
        char* buf = buff;

        if (fgets(buf,1024,in) == NULL){
            fprintf(stderr, "NODES NOT FOUND!\n");
            freeReadFile(in, entry, graph);
            exit(NO_NODES_FOUND);
        }

        if (insertGraph(entry, graph, i, buf) == false ){
            fprintf(stderr, "ILLEGAL POINTS FOUND!\n");
            freeReadFile(in, entry, graph);
            exit(WRONG_POINTS);
        }
    }

    fclose(in);
    return graph;
}

bool insertGraph(entryR* entry, node* graph, int i, char* buf){
    int columns = entry->columns, rows = entry->rows;
    int node = 0, offset=0;
    float weight = 0;

    while(sscanf(buf, " %d :%f %n", &node, &weight, &offset) == 2){
        buf+=offset;
        bool hasBeenAdded = false;

        if (i - columns >= 0 && i - columns < columns * rows){
            if (node == i - columns){
                graph[i].edgeExist[UP] = true;
                graph[i].nodeToConnect[UP] = i - columns;
                graph[i].edgeWeight[UP] = weight;
                hasBeenAdded = true;
            }
        } else {
            graph[i].edgeExist[UP] = false;
        }
        if(i + 1 < columns * rows && (i+1)%columns != 0){
            if (node == i + 1){
                graph[i].edgeExist[RIGHT] = true;
                graph[i].nodeToConnect[RIGHT] = i + 1;
                graph[i].edgeWeight[RIGHT] = weight;
                hasBeenAdded = true;
            }
        } else {
            graph[i].edgeExist[RIGHT] = false;
        }
        if (i + columns > 0 && i + columns < columns * rows){
            if(node == i + columns){
                graph[i].edgeExist[DOWN] = true;
                graph[i].nodeToConnect[DOWN] = i + columns;
                graph[i].edgeWeight[DOWN] = weight;
                hasBeenAdded = true;
            }
        } else {
            graph[i].edgeExist[DOWN] = false;
        }
        if(i - 1 >= 0 && i%columns != 0){
            if(node == i - 1){
                graph[i].edgeExist[LEFT] = true;
                graph[i].nodeToConnect[LEFT] = i - 1;
                graph[i].edgeWeight[LEFT] = weight;
                hasBeenAdded = true;
            }
        } else {
            graph[i].edgeExist[LEFT] = false;
        }
        if (hasBeenAdded == false)
            return false;
    }
    return true;
}

void findPath(node* graph, entryR* entry){
    int numOfPairs = entry->numberPoints / 2;
    int numOfNodes = entry -> columns * entry -> rows;
    
    for (int i = 0; i < numOfPairs; i++){
        int startPoint = entry->points[2*i];
        int endPoint = entry->points[2*i+1];
        int currentPoint = startPoint;
        int* predecessors = allocPredecessor(numOfNodes);
        bool* visited = allocVisited(numOfNodes);
        float* weights = allocWeights(numOfNodes);
        float* distance = allocWeights(numOfNodes);

        distance[startPoint] = 0;
        visited[currentPoint] = true;
        while (true){
            for(int k = 0; k < 4; k++){
                if(graph[currentPoint].edgeExist[k]){
                    if(distance[graph[currentPoint].nodeToConnect[k]] > distance[currentPoint] + graph[currentPoint].edgeWeight[k]){
                        predecessors[graph[currentPoint].nodeToConnect[k]] = currentPoint;
                        distance[graph[currentPoint].nodeToConnect[k]] = distance[currentPoint] + graph[currentPoint].edgeWeight[k];
                        weights[graph[currentPoint].nodeToConnect[k]] = graph[currentPoint].edgeWeight[k];
                    }
                }
            }
            
            currentPoint = findNewPoint(visited, distance, numOfNodes);
            if (currentPoint == -1)
                break;
            visited[currentPoint] = true;
        }


        if(entry->printFlag == STANDARD)
            printShortPath(entry, predecessors, startPoint, endPoint);
        if (entry->printFlag == EXTENDED)
            printExtendedPath(entry, predecessors, weights, startPoint, endPoint);

        freePathMemory(predecessors, weights, distance, visited);
    }
}

void printShortPath(entryR* entry, int* predecessors, int startPoint, int endPoint){
    int numOfNodes = entry -> columns * entry -> rows;

    int* predecessorsInOrder = allocPredecessorInOrder(numOfNodes);
    int size = 0;

    printf("(%d,%d); ", startPoint, endPoint);
    while(true) {
        predecessorsInOrder[size++] = endPoint;
        endPoint = predecessors[endPoint];
        if(endPoint == -1)
            break;
    }
    for(int i = size-1; i > 0; i--)
        printf("%d ---> ", predecessorsInOrder[i]);
    printf("%d\n", predecessorsInOrder[0]);

    free(predecessorsInOrder);
}

void printExtendedPath(entryR* entry, int* predecessors, float* weights, int startPoint, int endPoint){
    int numOfNodes = entry -> columns * entry -> rows;

    int* predecessorsInOrder = allocPredecessorInOrder(numOfNodes);
    int size = 0;

    printf("(%d,%d); ", startPoint, endPoint);
    while(true) {
        predecessorsInOrder[size++] = endPoint;
        endPoint = predecessors[endPoint];
        if(endPoint == -1)
            break;
    }
    for(int i = size-1; i > 0; i--) 
        printf("%d(%f) ---> ", predecessorsInOrder[i],weights[predecessorsInOrder[i-1]]);
    printf("%d\n", predecessorsInOrder[0]);

    free(predecessorsInOrder);
}

int findNewPoint(bool* visited, float* distance, int numOfNodes){
    int point = -1;
    
    for (int i = 0; i < numOfNodes; i++)
        if(visited[i] == false)
            point = i;

    if (point == -1)
        return -1;

    for (int i = 0; i < numOfNodes; i++)
        if(visited[i] == false && distance[i] <= distance[point])
            point = i;

    return point;
}

void readMode(entryR* entry){
    node* graph = readFromFile(entry);
    int numOfNodes = entry -> columns * entry -> rows;

    if (checkIfCoherent(graph, numOfNodes) != true){
        fprintf(stderr, "GRAPH IS NOT COHERENT!!!\n");
        freeReadMode(entry, graph);
        exit(NO_COHERENT);
    }
    findPath(graph, entry);
    freeReadMode(entry, graph);
}
