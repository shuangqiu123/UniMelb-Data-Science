/* dijkstra.h */
/* #include "digraph.h" */
#include <limits.h>
#define NOPATH INT_MAX
struct dijkstraRes {
    /* The node that all paths originate from, index is into
        indices list. */
    int sourceNode;
    /* The shortest paths from the source node to
        the destination.  */
    int *shortestPaths;
    /* The list of destination indices that the shortest
        paths correspond to. */
    int *indices;
    /* If you like, you can also add an item for 
        predecessors, but the actual path isn't
        being printed, so this isn't too important
        for the moment. Remember to update this in
        the free dijkstra struct function if you
        make memory-related changes to this struct. */
    
    /* The number of items in the index list. */
    int nodeCount;
};

/* Finds the shortest paths from the given source node to all
    other nodes in the graph (which have at least one edge in either
    direction) and returns a structure of these nodes. 
    Assumes that the given source node is actually in the graph. */
struct dijkstraRes *dijkstra(struct digraph *graph, int source);

/* 
    Prints all the shortest paths.
*/
void printDijkstra(struct dijkstraRes *res);

/*
    Frees a dijkstraRes struct and all the memory it
    is responsible for. (In the provided code, this is 
    assumed to be: .shortestPaths and .indices, as well
    as the struct sent).
*/
void freeDijkstraRes(struct dijkstraRes *res);