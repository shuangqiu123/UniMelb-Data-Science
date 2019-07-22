/* dijkstra.c */
#include "digraph.h"
#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include "../w09/pqueue.h"
/* NOTE: If you didn't write pqueue.h & pqueue.c last week, consider doing
    so before this exercise. */

struct dijkstraRes *dijkstra(struct digraph *graph, int source){
    /* FILL IN HERE */
    
    
    
    
    
}

void printDijkstra(struct dijkstraRes *res){
    int i;
    printf("Shortest paths from %d\n", res->indices[res->sourceNode]);
    for(i = 0; i < res->nodeCount; i++){
        if ((res->shortestPaths[i]) == NOPATH){
            printf("to %d: NO PATH;\n", res->indices[i]);
        } else {
            printf("to %d: %d;\n", res->indices[i], res->shortestPaths[i]);
        }
    }
}

void freeDijkstraRes(struct dijkstraRes *res){
    if(! res){
        return;
    }
    if(res->shortestPaths){
        free(res->shortestPaths);
    }
    if(res->indices){
        free(res->indices);
    }
    free(res);
}