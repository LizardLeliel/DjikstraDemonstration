#include <stdlib.h>
#include <stdio.h>
#include <limits.h> /* UINT_MAX */

#include "djikstra.h"
#include "graphing.h"
#include "rtTracking.h"

// These two are going to need to change
//shortPathNode_t* heapArray;
pqueue_t* nodeQueue;
// Replace 90000 with int max. 
shortPathNode_t dummy = {NULL, NULL, UINT_MAX, NULL};

priorityHeap_t* newHeap() {
    priorityHeap_t* newHeap = malloc(sizeof(priorityHeap_t));
    newHeap->currentNext = 0;
    // This should be plenty of space
    newHeap->max         = returnHighestID() * 2;
                           // Should use calloc here.
    newHeap->heapArray   = malloc(sizeof(shortPathNode_t*) * newHeap->max);

    return newHeap;
}

void deleteHeap(priorityHeap_t* heap) {
    free(heap->heapArray);
    free(heap);
}

void insertIntoHeap(priorityHeap_t* heap, shortPathNode_t* element) {

    if (heap->currentNext == heap->max)
    {
        heap->heapArray 
            = realloc(heap->heapArray, sizeof(shortPathNode_t*)*heap->max*2);
        heap->max *= 2;
    }

    // Add some reallocation code here
    // Basic initalizing
    shortPathNode_t** heapArray = heap->heapArray;
    unsigned int lowerRef, higherRef;
    lowerRef            = heap->currentNext;
    heapArray[lowerRef] = element;

    ++(heap->currentNext);

    while (lowerRef != 0) {
        higherRef = (lowerRef - 2 + (lowerRef & 1)) >> 1;

        if (heapArray[higherRef]->distance > element->distance) {
            heapArray[lowerRef]  = heapArray[higherRef];
            heapArray[higherRef] = element;
        }
        else break;

        lowerRef = higherRef;
    }
}

shortPathNode_t* popHeap(priorityHeap_t* heap) {
    if (heap->currentNext == 0) return NULL;

    shortPathNode_t** heapArray = heap->heapArray;
    shortPathNode_t* returnVal  = heapArray[0];
    unsigned int higherRef      = 0;
    unsigned int firstLeaf      = 1;
    unsigned int secondLeaf     = 2;

    --(heap->currentNext);
    heapArray[0]                 = heapArray[heap->currentNext];
    heapArray[heap->currentNext] = NULL;

    if (heap->currentNext <= 1) return returnVal;
    else if (heap->currentNext == 2)
    {
        if (heapArray[0]->distance > heapArray[1]->distance) {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[firstLeaf];
            heapArray[firstLeaf]  = swap;
        }
        return returnVal;
    }

    while (firstLeaf < heap->currentNext) {
        secondLeaf = firstLeaf + 1;

        if (heapArray[firstLeaf]->distance 
          > heapArray[secondLeaf]->distance) {
            ++firstLeaf; --secondLeaf;
        }

        if (firstLeaf < heap->currentNext 
          && heapArray[higherRef]->distance 
          >  heapArray[firstLeaf]->distance) {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[firstLeaf];
            heapArray[firstLeaf]  = swap;
            higherRef             = firstLeaf;
            firstLeaf             = higherRef*2 + 1;
        }

        else if (secondLeaf < heap->currentNext
          && heapArray[higherRef]->distance 
          > heapArray[secondLeaf]->distance) {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[secondLeaf];
            heapArray[secondLeaf] = swap;
            higherRef             = secondLeaf;
            firstLeaf             = higherRef*2 + 1;
        }

        else break;
    }

    return returnVal;
}

// Initializing helper function
static shortPathNode_t* initDjikstra(graphNode* graph, int from, 
  priorityHeap_t** heap) {
    /* build reference array */
    shortPathNode_t* shortestPaths;
    shortestPaths = malloc(sizeof(shortPathNode_t) * (returnHighestID()+1));

    /* set heap data */
    while (graph) {
        shortPathNode_t* index = shortestPaths + graph->id;
        index->node     = graph;
        index->distance = UINT_MAX;
        index->shortest = graph->adjHead;
        graph           = graph->next;
    }

    // Initializing some points in the array.
    shortestPaths[from].distance = 0;
    shortestPaths[from].parent   = NULL;
    shortestPaths[0].parent      = shortestPaths + from; /* The top of the heap */

    // Making our heap.
    *heap = newHeap();

    // Our hold Priority Queue. Delete this part.
    nodeQueue = malloc(sizeof(pqueue_t));
    nodeQueue->next = nodeQueue;
    nodeQueue->enqueued = shortestPaths + from;

    return shortestPaths;
}

// Old queue functions
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
    priorityHeap_t* heap;
    shortPathNode_t* heapArray = initDjikstra(graph, from, &heap);

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

// This is so the unused printing functions still compile. I need to find
//  those and delete those. 
shortPathNode_t* heapArray;

//printing function
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


