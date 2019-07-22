/* digraph.h */
struct digraph;

/* Return type for edges. 
    Linked list concrete data type. */
struct weightedEdge {
    int destIndex;
    int weight;
    struct weightedEdge *next;
};

/* Create a new weighted directed graph containing no edges. */
struct digraph *newDigraph();

/* 
    Add an edge from the source to the destination with the given weight
    to the given graph.
*/
void addEdge(struct digraph *graph, int source, int destination, int weight);

/*
    Returns a list of edges which occur in the given graph, will be in order.
    Nodes without an edge to or from them will not be returned. This list should
    be freed by the caller. Value sent into size will be set to the size of the
    returned list. The final value in the returned list will also be given a value
    of graph->lowIndex - 1, so can be used as a sentinel (the size will exclude 
    this value).
*/
int *getNodes(struct digraph *graph, int *size);

/*
    Returns the list of edges from a particular node in the graph as indices
    into the provided list. (ie a graph with nodes -1, 3, 4 and a list [-1,3,4],
    the edge list [[-1,50],[3,30],[4,20]] will be transformed to 
    [[0,50],[4,30],[5,20]], this is for the purposes of abstracting out some of
    the internal behaviour of the digraph).
    The source index should be the value at the index in the nodeList given (so 0
    would be the index -1).
    The returned array is allocated as a list of weighted edges. This should be
    freed by the calling function.
    The original list is expected to obey the same constraints as that in the getNodes
    function.
*/
struct weightedEdge *getAdjacent(struct digraph *graph, int *nodeList, int sourceIndex);

/*
    Converts a given index to an index in the given node list (linear search). Could be
    binary search, but keeping it simple it should still be fast enough in this case.
*/
int convertIndex(int *list, int originalIndex);

/*
    Frees all the memory used by a particular graph.
*/
void freeDigraph(struct digraph *graph);