#ifndef DJIKSTRA_HEADER
#include "graphing.h"
#include "unusedIDs.h"

// Sturcture to help with the djikstra algorithm and store results
typedef struct SHORTEST_PATH_NODE
{

    struct SHORTEST_PATH_NODE* parent;
    graphNode* node;
    unsigned int distance;
    adjNode* shortest; /* When null, visited */

} shortPathNode_t;


// Heap for a priority queue in the algorithm
typedef struct PRIORITY_QUEUE_HEAP
{
    shortPathNode_t** heapArray; // Array of pointers
    unsigned int currentNext;
    unsigned int max;

} priorityHeap_t;

// Heap funcions
priorityHeap_t* newHeap();
void deleteHeap(priorityHeap_t* heap);
void insertIntoHeap(priorityHeap_t* heap, shortPathNode_t* element);
shortPathNode_t* popHeap(priorityHeap_t* heap);
bool heapIsEmpty(priorityHeap_t* heap);

// The djikstra functions. (graphNode is going to need to change to graph_t*)
shortPathNode_t* djikstraAll(graph_t* graph, unsigned int from);
void freeDjikstra(shortPathNode_t* results);





/* debug printing */
//void printDPath(shortPathNode_t* path);
//void printDResults(graphNode* graph, shortPathNode_t* shorestPaths);
void printDjikstraResultsAll(graphNode* restrict graph,
    shortPathNode_t* restrict results);




//shortPathNode_t* heapArray;
//pqueue_t* nodeQueue;

#define DJIKSTRA_HEADER
#endif
