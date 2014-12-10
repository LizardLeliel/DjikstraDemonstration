#ifndef DJIKSTRA_HEADER
#include "graphing.h"
#include "rtTracking.h"

typedef struct HEAP {

    struct HEAP* parent;
    graphNode* node;
    unsigned int distance;
    adjNode* shortest; /* When null, visited */

} heap_t;


typedef struct PIRORITY_QUEUE {

    struct PIRORITY_QUEUE* next;
    heap_t* enqueued;

} pqueue_t;

void initDjikstra(graphNode* graph, int from);


/* debug printing */
void printHeapArray();
void printP_QUEUE(); /* Its spelled like this because it was freaking out
                     * with the stdio.h library and I didn't want to take
                     * any risks */

void freeDjikstra();

#define DJIKSTRA_HEADER
#endif
