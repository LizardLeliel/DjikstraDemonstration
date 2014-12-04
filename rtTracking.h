#ifndef TRACKING_HEADER
#include <stdlib.h>
/* This file is to allow the user to reference vertices by name,
 * and allow the program to keep track of ids. Namely, if a vertex
 * is deleted, its id will be the next used when pushing a new vertex -
 * else it'll use the number nextID, and increment it
 */

typedef struct RemovedIDs {
    int unused;
    struct RemovedIDs* next;
} availableIDs;

void idStackInit();
void pushAvailableIDs(int n);
unsigned int nextAvailableIDs();
availableIDs* returnFreeIDs();


#define TRACKING_HEADER
#endif