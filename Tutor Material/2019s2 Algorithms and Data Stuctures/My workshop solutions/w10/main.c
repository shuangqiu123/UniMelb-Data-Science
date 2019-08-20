/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "digraph.h"
#include "dijkstra.h"
#define EDGES 6

int main(int argc, char **argv){
    struct digraph *graph = NULL;
    struct dijkstraRes *res = NULL;
    int src[EDGES];
    int dest[EDGES];
    int weight[EDGES];
    int i = 0;
    src[i] = 1; dest[i] = 2; weight[i] = 200; i++;
    src[i] = 1; dest[i] = 3; weight[i] = 100; i++;
    src[i] = 1; dest[i] = 4; weight[i] = 500; i++;
    src[i] = 2; dest[i] = 3; weight[i] = 150; i++;
    src[i] = 2; dest[i] = 4; weight[i] = 300; i++;
    src[i] = 4; dest[i] = 5; weight[i] = 100;
    
    graph = newDigraph();
    
    for(i = 0; i < EDGES; i++){
        addEdge(graph, src[i], dest[i], weight[i]);
    }
    
    printf("Running Dijkstra's Algorithm on graph\n");
    res = dijkstra(graph, 1);
    
    printf("Results:\n");
    printDijkstra(res);
    
    freeDigraph(graph);
    freeDijkstraRes(res);
    
    return 0;
}