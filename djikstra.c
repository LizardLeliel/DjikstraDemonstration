#include <stdlib.h>
#include <stdio.h>
#include <limits.h> /* UINT_MAX */

#include "djikstra.h"
#include "graphing.h"
#include "rtTracking.h"

// These two are going to need to change
//shortPathNode_t* heapArray;
// pqueue_t* nodeQueue;
// Replace 90000 with int max.
// shortPathNode_t dummy = {NULL, NULL, UINT_MAX, NULL};

priorityHeap_t* newHeap()
{
    priorityHeap_t* newHeap = malloc(sizeof(priorityHeap_t));
    newHeap->currentNext = 0;
    // This should be plenty of space
    newHeap->max         = returnHighestID() * 2;
    newHeap->heapArray   = malloc(sizeof(shortPathNode_t*) * newHeap->max);

    return newHeap;
}

void deleteHeap(priorityHeap_t* heap)
{
    free(heap->heapArray);
    free(heap);
}

void insertIntoHeap(priorityHeap_t* heap, shortPathNode_t* element)
{

    if (heap->currentNext == heap->max)
    {
        heap->max *= 2;
        heap->heapArray
            = realloc(heap->heapArray, sizeof(shortPathNode_t*)*heap->max);
    }

    // Add some reallocation code here
    // Basic initalizing
    shortPathNode_t** heapArray = heap->heapArray;
    unsigned int lowerRef, higherRef;
    lowerRef            = heap->currentNext;
    heapArray[lowerRef] = element;

    ++(heap->currentNext);

    //if (heap->currentNext == 1) return;

    while (lowerRef != 0)
    {
        higherRef = (lowerRef - 2 + (lowerRef & 1)) >> 1;

        if (heapArray[higherRef]->distance > element->distance)
        {
            heapArray[lowerRef]  = heapArray[higherRef];
            heapArray[higherRef] = element;
        }
        else break;

        lowerRef = higherRef;
    }
}

shortPathNode_t* popHeap(priorityHeap_t* heap)
{
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
        if (heapArray[0] == NULL || heapArray[1] == NULL)
        {
            printf("\nWe have a problem with 2 pushed\n");
            return returnVal;
        }
        if (heapArray[0]->distance > heapArray[1]->distance)
        {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[firstLeaf];
            heapArray[firstLeaf]  = swap;
        }
        return returnVal;
    }

    while (firstLeaf < heap->currentNext)
    {
        secondLeaf = firstLeaf + 1;

        if (secondLeaf < heap->currentNext
                && heapArray[firstLeaf]->distance
                >  heapArray[secondLeaf]->distance)
        {
            ++firstLeaf; --secondLeaf;
        }

        if (firstLeaf < heap->currentNext
                && heapArray[higherRef]->distance
                >  heapArray[firstLeaf]->distance)
        {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[firstLeaf];
            heapArray[firstLeaf]  = swap;
            higherRef             = firstLeaf;
            firstLeaf             = higherRef * 2 + 1;
        }

        else if (secondLeaf < heap->currentNext
                 && heapArray[higherRef]->distance
                 > heapArray[secondLeaf]->distance)
        {
            shortPathNode_t* swap = heapArray[higherRef];
            heapArray[higherRef]  = heapArray[secondLeaf];
            heapArray[secondLeaf] = swap;
            higherRef             = secondLeaf;
            firstLeaf             = higherRef * 2 + 1;
        }

        else break;
    }

    return returnVal;
}

inline bool heapIsEmpty(priorityHeap_t* heap)
{
    return heap->currentNext == 0;
}

// Initializing helper function
static shortPathNode_t* initDjikstra(graphNode* graph, int from,
  priorityHeap_t** heap)
{
    /* build reference array */
    shortPathNode_t* shortestPaths;
    shortestPaths = malloc(sizeof(shortPathNode_t) * (returnHighestID() + 1));

    /* set heap data */
    while (graph)
    {
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
    insertIntoHeap(*heap, shortestPaths + from);

    return shortestPaths;
}



// Find ALL the shortest paths!
shortPathNode_t* djikstraAll(graphNode* graph, int from)
{
    priorityHeap_t*  heap;
    shortPathNode_t* shortestPaths = initDjikstra(graph, from, &heap);

    // While there are unchecked nodes
    while (!heapIsEmpty(heap))
    {

        // Visit the next node on the priority queue, node "a"
        shortPathNode_t* visiting = popHeap(heap);

        // While there are still paths to check
        while (visiting->shortest)
        {

            // We get node "b" which is has the shorest edge to node "a",
            //  and we also store the distance from "a" to "b".
            shortPathNode_t* comparing = shortestPaths + visiting->shortest->id;
            unsigned int distFromAbove = visiting->shortest->distance;

            // If the the path from the start node to node "a" + the distance to
            //  node "a" to node "b" is shorter then any previus calculated distance,
            //  we update node "b"'s information (the initial distance from parent
            //  is the highest int).
            if (visiting->distance + distFromAbove < comparing->distance)
            {
                comparing->parent   = visiting;
                comparing->distance = visiting->distance + distFromAbove;
            }

            // Then we push node "b" onto the heap so later we can use it as
            //  node "a"
            insertIntoHeap(heap, comparing);

            // We go onto the next closest node "b"
            visiting->shortest = visiting->shortest->next;

        }
    }

    deleteHeap(heap);
    return shortestPaths;
}

void freeDjikstra(shortPathNode_t* results)
{
    free(results);
}


// Printing functions
static bool printDjikstraPath(shortPathNode_t* restrict path)
{
    if (!path) return false;

    if (printDjikstraPath(path->parent))
    {
        printf("->%s", path->node->name);
    }

    return true;

}

void printDjikstraResultsAll(graphNode* restrict graph, 
    shortPathNode_t* restrict shortestPaths)
{
    printf("---------------\n");
    while (graph)
    {
        if (shortestPaths[graph->id].distance == UINT_MAX)
        {
            printf("There is no path from %s to %s\n",
                   shortestPaths[0].parent->node->name,
                   shortestPaths[graph->id].node->name);
            puts("---------------");
        }
        else
        {
            printf("Shortest distance from %s to %s: %u\n",
                   shortestPaths[0].parent->node->name,
                   shortestPaths[graph->id].node->name,
                   shortestPaths[graph->id].distance);
            printf("The path: %s", shortestPaths[0].parent->node->name);
            printDjikstraPath(shortestPaths + graph->id);
            puts("\n---------------");
        }
        
        graph = graph->next;
    }
}