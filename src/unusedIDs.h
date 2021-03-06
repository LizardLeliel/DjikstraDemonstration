#ifndef TRACKING_HEADER
#include <stdlib.h>
// trTracking.c pretty much allows the program to reuse ids
 

// I'll probably merge a lot of this into graph.c
typedef struct RemovedIDs
{
    int unused;
    struct RemovedIDs* next;
} availableIDs;

void idStackInit();
void idStackDelete();

void pushAvailableIDs(int n);
unsigned int nextAvailableIDs();
unsigned int returnHighestID();

#define TRACKING_HEADER
#endif
