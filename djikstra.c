#include <stdlib.h>
#include <stdio.h>
#include <limits.h> /* UINT_MAX */

#include "djikstra.h"
#include "graphing.h"
#include "rtTracking.h"

// These two are going to need to change
//shortPathNode_t* heapArray;
pqueue_t* nodeQueue;



static shortPathNode_t* initDjikstra(graphNode* graph, int from) {
    /* build reference array */
    shortPathNode_t* shortestPaths;
    shortestPaths = malloc(sizeof(shortPathNode_t)*(returnHighestID()+1));

    /* set heap data */
    while (graph) {
        shortPathNode_t* index = shortestPaths + graph->id;
        index->node     = graph;
        index->distance = UINT_MAX;
        index->shortest = graph->adjHead;
        graph           = graph->next;
    }

    nodeQueue = malloc(sizeof(pqueue_t));
    nodeQueue->next = nodeQueue;

    shortestPaths[from].distance = 0;
    shortestPaths[from].parent   = NULL;
    shortestPaths[0].parent      = shortestPaths + from; /* The top of the heap */

    nodeQueue->enqueued = shortestPaths + from;

    return shortestPaths;
}

static void enqueue(pqueue_t** queueNode, shortPathNode_t* toEnqueue) {
    /* If the the child list is emptey, then its either visited,
     * or it has no more child nodes, so we exit */
    if (!toEnqueue->shortest) return;
    /* We then do a standard queue pushing here */
    pqueue_t* newNode  = malloc(sizeof(pqueue_t));
    newNode->enqueued  = toEnqueue;
    newNode->next      = (*queueNode)->next;
    (*queueNode)->next = newNode;
    (*queueNode)       = newNode;
}

static void dequeue(pqueue_t** queueNode) {
    pqueue_t* toFree = (*queueNode)->next;
    **queueNode = *toFree;    /* copy */
    if (*queueNode == toFree) /* we're deleting the only node left */
        *queueNode = NULL;    /* End of algorithm */

    free(toFree);
}

/* the hurtful part of using a pirority queue ;-; */
static void findPirority(pqueue_t** queueNode /* out variable */) {
    /* if the queueNode is NULL, then we searched everything */
    if (!*queueNode) return;

    /* else, we have a searcher pointer */
    pqueue_t* finder = (*queueNode)->next;

    /* and a struct to keep track of its findings */
    struct {pqueue_t* found; unsigned int pirority;} record;

    /* we set it to the top, in case that is the highest piority */
    record.found    = *queueNode;
    record.pirority = ((*queueNode)->enqueued->distance);

    /* And as we go down the queue until it comes back to the top */
    while (finder != *queueNode) {

        /* If this node's distance from source is lower then the record's,
         * it'll be marked as temporarly "found" */
        if (finder->enqueued->distance < record.pirority) {
            record.found = finder;
            /* and of course the pirority is updated */
            record.pirority = finder->enqueued->distance;
        }
        /* We move onto the next */
        finder = finder->next;
    }
    /* And whatever we have found we'd want to set at the top */
    *queueNode = record.found;

}

shortPathNode_t* djikstraAll(graphNode* graph, int from) {
    shortPathNode_t* heapArray = initDjikstra(graph, from);

    /* While there are unchecked paths */
    while (nodeQueue) {
        /* We visit the node currently queued */
        shortPathNode_t* visiting = nodeQueue->enqueued;

        /* We check everything it is linked too */
        while (visiting->shortest) {
            /* We find which child we're looking at */
            shortPathNode_t* comparing = heapArray + visiting->shortest->id;
            /* And its distance from above */
            unsigned int distFromAbove = visiting->shortest->distance;

            /* and if the child node's distance is lower then the parent's
             * distance from source + the distance between them, then we found
             * the shorter path, and we'd want to update this */
            if (visiting->distance + distFromAbove < comparing->distance) {
                comparing->parent   = visiting;
                comparing->distance = visiting->distance + distFromAbove;
            }
            /* We enqueue this child, saying look at this eventually */
            enqueue(&nodeQueue, comparing);

            /* And we move onto the next child */
            visiting->shortest = visiting->shortest->next;

        }
        /* Then we remove the visiting node from our queue */
        dequeue(&nodeQueue);
        /* And search for the queue, and set nodeQueue to the next
         * lowest pirority. Its a circular list, so it doesn't matter
         * what's first */
        findPirority(&nodeQueue);
    }

    return heapArray;
}

shortPathNode_t* heapArray;

static void printDPath(shortPathNode_t* path) {
    if (!path) return;

    printDPath(path->parent);

    printf("%s->", path->node->name);
    return;
}

void printDResults(graphNode* graph, shortPathNode_t* shortestPaths) {
    printf("-----------\n");
    while(graph) {

        printf("Shortest Distance from %s to %s: %u\n",
                shortestPaths[0].parent->node->name,
                shortestPaths[graph->id].node->name,
                shortestPaths[graph->id].distance);
        printf("The path: \n");
        printDPath(shortestPaths + graph->id);
        printf("done\n----------\n");
        graph = graph->next;
    }
}


void printHeapArray(graphNode* graph, shortPathNode_t* shortestPaths) {

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

void printP_QUEUE() {
    pqueue_t* q = nodeQueue;

    do {
        printf("%p, %s\n", q->enqueued, q->enqueued->node->name);
        q = q->next;
    } while (q != nodeQueue);

}


