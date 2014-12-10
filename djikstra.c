#include <stdlib.h>
#include <stdio.h>
#include <limits.h> /* UINT_MAX */

#include "djikstra.h"
#include "graphing.h"
#include "rtTracking.h"


heap_t* heapArray;
pqueue_t* nodeQueue;

void initDjikstra(graphNode* graph, int from) {
    /* build reference array */
    heapArray = malloc(sizeof(heap_t)*returnHighestID());

    /* set heap data */
    while (graph) {
        heap_t* index   = heapArray + graph->id;
        index->node     = graph;
        index->distance = UINT_MAX;
        index->shortest = graph->adjHead;
        graph           = graph->next;
    }

    nodeQueue = malloc(sizeof(pqueue_t));
    nodeQueue->next = NULL;

    heapArray[from].distance = 0;
    heapArray[from].parent   = NULL;

    nodeQueue->enqueued = heapArray + from;
}


void printHeapArray(graphNode* graph) {

    printf("========== Heap printing ==========\n");
    int i = 0;

    while (graph) {
        printf("Graph depth: %d\n", ++i);
        printf("Heap index: %d\n", graph->id);
        printf("Expected name: %s\n", graph->name);
        printf("Heap values:\n");
        printf("  heapArray[graph->id].node->name: %s\n", heapArray[graph->id].node->name);
        printf("  heapArray[graph->id].node->id: %d\n", heapArray[graph->id].node->id);
        printf("  heapArray[graph->id].distance: %u\n\n", heapArray[graph->id].distance);
        graph = graph->next;
    }

    printf("========= End =========\n");
}

void printQ_QUEUE() {
    pqueue_t* q = nodeQueue;

    while (q) {
        printf("%p, %s\n", q->enqueued, q->enqueued->node->name);
        q = q->next;
    }

}


