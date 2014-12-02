#include "graphing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printConnections(adjNode* listHead) {
    while (listHead != NULL) {
        printf("Node %d, distance from this node: %d\n",
                listHead->id, listHead->distance);
        listHead = listHead->next;
    }
}

void pushAdjNode(adjNode** listHead, int newID, int newDistance) {
    adjNode* newNode  = malloc(sizeof(adjNode));
    newNode->id       = newID;
    newNode->distance = newDistance;
    newNode->next     = *listHead;
    *listHead         = newNode;
}
