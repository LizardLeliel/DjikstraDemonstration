#ifndef DJIKSTRA_HEADER
#include "graphing.h"
#include "rtTracking.h"

// Sturcture to help with the djikstra algorithm and store results
typedef struct SHORTEST_PATH_NODE {

    struct SHORTEST_PATH_NODE* parent;
    graphNode* node;
    unsigned int distance;
    adjNode* shortest; /* When null, visited */

} shortPathNode_t;

// This is going to be deleted
typedef struct PIRORITY_QUEUE {

    struct PIRORITY_QUEUE* next;
    shortPathNode_t* enqueued;

} pqueue_t;

// Heap for a priority queue in the algorithm
typedef struct PRIORITY_QUEUE_HEAP {
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

// The one function to worry about.
shortPathNode_t* djikstraAll(graphNode* graph, int from);





/* debug printing */
//void printDPath(shortPathNode_t* path);
void printDResults(graphNode* graph, shortPathNode_t* shorestPaths);
void printHeapArray();
void printP_QUEUE(); /* Its spelled like this because it was freaking out
                     * with the stdio.h library and I didn't want to take
                     * any risks */


void freeDjikstra();

//shortPathNode_t* heapArray;
//pqueue_t* nodeQueue;

#define DJIKSTRA_HEADER
#endif
