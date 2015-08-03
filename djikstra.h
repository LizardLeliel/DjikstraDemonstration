#ifndef DJIKSTRA_HEADER
#include "graphing.h"
#include "rtTracking.h"

typedef struct SHORTEST_PATH_NODE {

    struct SHORTEST_PATH_NODE* parent;
    graphNode* node;
    unsigned int distance;
    adjNode* shortest; /* When null, visited */

} shortPathNode_t;


typedef struct PIRORITY_QUEUE {

    struct PIRORITY_QUEUE* next;
    shortPathNode_t* enqueued;

} pqueue_t;



//shortPathNode_t* initDjikstra(graphNode* graph, int from);
shortPathNode_t* djikstraAll(graphNode* graph, int from);

//void enqueue(pqueue_t** queueNode, shortPathNode_t* toEnqueue);
//void dequeue(pqueue_t** queueNode);




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
