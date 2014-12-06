#include "graphing.h"
#include "rtTracking.h"
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
    printf("Pushing %s\n", cstring);
    graphNode* newNode  = malloc(sizeof(graphNode));
    newNode->id         = newID;
    newNode->name       = malloc(sizeof(char)*strlen(cstring)+1);
    newNode->adjHead    = NULL;
    strcpy(newNode->name, cstring);

    newNode->next  = *graphHead;
    *graphHead     = newNode;

    return;
}

/* ==== Existance checking ==== */
bool existantNamedVertex(graphNode* graphHead, const char* cstring) {
    if (graphHead == NULL) return false; /* Graph has no names */
    while (graphHead != NULL && strcmp(cstring, graphHead->name)) {
        graphHead = graphHead->next;
    }
    return (bool)graphHead;
    /* Because if it reached NULL, it didn't find a match, and graphHead will
    * NULL, or false. Else, it did sucessfully match, and graphHead will be
    * a valid pointer, thus being true */

}

int pushUniqueVertex(graphNode** graphHead, const char* cstring) {
    if (existantNamedVertex(*graphHead, cstring)) return 1; /*Already exists*/
    pushVertex(graphHead, nextAvailableIDs(), cstring);
    return 0;
}

int linkVertices(graphNode* graphHead, int idOne, int idTwo, int distance) {
    if (idOne == idTwo) return 1; /* Same nodes */
    adjNode** head1 = NULL;
    adjNode** head2 = NULL;

    while (!(head1 && head2)) {
        if (graphHead == NULL) return 2; /* graphHead reaches end - node not found */

        if (graphHead->id == idOne)
            head1 = &(graphHead->adjHead);
        if (graphHead->id == idTwo)
            head2 = &(graphHead->adjHead);

        graphHead = graphHead->next;
    }
    pushSortedAdjNode(head1, idOne, distance);
    pushSortedAdjNode(head2, idTwo, distance);
    return 0;
}

int linkByName(graphNode* graphHead, const char* nameOne, const char* nameTwo,
  int distance) {
    if (!strcmp(nameOne, nameTwo)) return 1; /* Same nodes */
    int idOne, idTwo;
    adjNode** head1 = NULL;
    adjNode** head2 = NULL;

    while (!(head1 && head2)) {
        if (graphHead == NULL) return 2; /* graphHead reaches end - node not found */

        if (!(strcmp(nameOne, graphHead->name))) {
            head1 = &(graphHead->adjHead);
            idOne = graphHead->id;
        }
        if (!(strcmp(nameTwo, graphHead->name))) {
            head2 = &(graphHead->adjHead);
            idTwo = graphHead->id;
        }
        graphHead = graphHead->next;
    }
    pushSortedAdjNode(head1, idOne, distance);
    pushSortedAdjNode(head2, idTwo, distance);
    return 0;
}









