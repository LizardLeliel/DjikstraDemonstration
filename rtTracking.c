#include "rtTracking.h"
#include <stdlib.h>
#include <stdio.h>

availableIDs* freeIDs;
unsigned int nextAvailable;

void idStackInit() {
    freeIDs = NULL;
    nextAvailable = 0;
}

void pushAvailableIDs(int n) {
    availableIDs* newID = malloc(sizeof(availableIDs));
    newID->unused = n;
    newID->next   = freeIDs;
    freeIDs       = newID;
}

unsigned int nextAvailableIDs() {
    if (!freeIDs) return ++nextAvailable;

    unsigned int returnVal;
    returnVal = freeIDs->unused;
    freeIDs   = freeIDs->next;
    return returnVal;
}

unsigned int returnHighestID() {
    return nextAvailable;
}
