#include "rtTracking.h"
#include <stdlib.h>
#include <stdio.h>

availbleIDs* freeIDs;
unsigned int nextAvailable;

void idInit() {
    freeIDs = NULL;
    nextAvailable = 1;
}

void pushAvailbleIDs(int n) {
    availbleIDs* newID = malloc(sizeof(availbleIDs));
    newID->unused = n;
    newID->next   = freeIDs;
    freeIDs       = newID;
}

unsigned int popAvailbleIDs() {
    if (!freeIDs) return 0; /*Stack is null*/

    unsigned int returnVal;
    returnVal = freeIDs->unused;
    freeIDs   = freeIDs->next;
    return returnVal;
}

availbleIDs* returnFreeIDs() {
    return freeIDs;
}
