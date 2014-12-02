#include "graphing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ==== Print functions ==== */
void printConnections(adjNode* listHead) {
    while (listHead != NULL) {
        printf("Node %d, distance from this node: %d\n",
                listHead->id, listHead->distance);
        listHead = listHead->next;
    }
}

void printNodeAndConnections(graphNode* graphHead) {
    printf("This is vertex %s with id %d. It's connected to these vertices:\n",
            graphHead->name, graphHead->id);
    printConnections(graphHead->adjHead);

}

/* ==== Basic pushing ==== */
void pushAdjNode(adjNode** listHead, int newID, int newDistance) {
    adjNode* newNode  = malloc(sizeof(adjNode));
    newNode->id       = newID;
    newNode->distance = newDistance;
    newNode->next     = *listHead;
    *listHead         = newNode;
}

void pushSortedAdjNode(adjNode** listHead, int newID, int newDistance) {
    adjNode* newNode  = malloc(sizeof(adjNode));
    newNode->id       = newID;
    newNode->distance = newDistance;

    if (*listHead == NULL || (*listHead)->distance >= newDistance) {
        newNode->next = *listHead;
        *listHead     = newNode;
        return;
    }

    adjNode* temp = *listHead;
    while ((*listHead)->next != NULL && (*listHead)->next->distance <= newDistance) {
        *listHead = (*listHead)->next;
    }

    newNode->next     = (*listHead)->next;
    (*listHead)->next = newNode;
    *listHead         = temp;
}

void pushVertex(graphNode** graphHead, int newID, const char* cstring) {
    graphNode* newNode  = malloc(sizeof(graphNode));
    newNode->id         = newID;
    newNode->name       = malloc(sizeof(char)*strlen(cstring)+1);
    strcpy(newNode->name, cstring);

    newNode->next  = *graphHead;
    *graphHead     = newNode;

    return;
}

/* ==== Existance checking ==== */
bool existantNamedVertex(graphNode* graphHead, const char* cstring) {
    while (graphHead != NULL && strcmp(cstring, graphHead->name)) {
        graphHead = graphHead->next;
    }
    return (bool)graphHead;
    /* Because if it reached NULL, it didn't find a match, and graphHead will
    * NULL, or false. Else, it did sucessfully match, and graphHead will be
    * a valid pointer, thus being true */

}











