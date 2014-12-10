#include "graphing.h"
#include "rtTracking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

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

void printEveryVertex(graphNode* graphHead) {
    while (graphHead) {
        printf("Vertex %s with id %d:\n", graphHead->name, graphHead->id);
        graphHead = graphHead->next;
    }
}

void printEverything(graphNode* graphHead) {
    while (graphHead) {
        printNodeAndConnections(graphHead);
        printf("\n"); graphHead = graphHead->next;
    }

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
    while ((*listHead)->next != NULL &&
          (*listHead)->next->distance <= newDistance) {

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
        if (graphHead == NULL) return 2;/*graphHead reaches end: node ! found*/

        if (graphHead->id == idOne)
            head1 = &(graphHead->adjHead);
        if (graphHead->id == idTwo)
            head2 = &(graphHead->adjHead);

        graphHead = graphHead->next;
    }
    pushSortedAdjNode(head1, idTwo, distance);
    pushSortedAdjNode(head2, idOne, distance);
    return 0;
}

int linkByName(graphNode* graphHead, const char* nameOne, const char* nameTwo,
  int distance) {
    if (!strcmp(nameOne, nameTwo)) return 1; /* Same nodes */
    int idOne = 0, idTwo = 0;
    adjNode** head1 = NULL;
    adjNode** head2 = NULL;

    while (!(idOne && idTwo)) {
        if (graphHead == NULL) return 2;/*graphHead reaches end: node ! found*/

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
    pushSortedAdjNode(head1, idTwo, distance);
    pushSortedAdjNode(head2, idOne, distance);
    return 0;
}

bool deleteNode(adjNode** head, int id) {
    if (!head || !*head) return false; /* Emptey list */
    adjNode* temp;
    /* V If the first node is target ID */
    if ((*head)->id == id) {
        temp = *head;
        *(head) = (*head)->next;
        free(temp);
        return true;
    }

    adjNode* tracer = *head;
    while (tracer->next && !(tracer->next->id == id)) {
        tracer = tracer->next;
    }
    if (!tracer->next) return false;

    temp = tracer->next;
    tracer->next = tracer->next->next;
    free(temp);
    return true;

}


int severIDLink(graphNode* graphHead, int idOne, int idTwo) {
    if (idOne == idTwo) return 1; /* Same node */
    adjNode** head1 = NULL;
    adjNode** head2 = NULL;
    while (!(head1 && head2)) {
        if (!graphHead) return 2;/* Head reached Null */

        if (graphHead->id == idOne)
            head1 = &(graphHead->adjHead);
        else if (graphHead->id == idTwo)
            head2 = &(graphHead->adjHead);

        graphHead = graphHead->next;
    } /* if (!(*head1 || *head2)) return 3; / I don't even */
    deleteNode(head1, idTwo);
    deleteNode(head2, idOne);
    return 0;
}

int severNamedLink(graphNode* graphHead, const char* name1, const char* name2) {
    if (!strcmp(name1, name2)) return 1; /* Same node */
    adjNode** head1 = NULL;
    adjNode** head2 = NULL;
    int idOne, idTwo;

    while (!(head1 && head2)) {
        if (!graphHead) { printf("severNamedLink return 2\n");return 2; } /* Head reached Null */

        if (!(strcmp(name1, graphHead->name))) {
            head1 = &(graphHead->adjHead);
            idOne = graphHead->id;
        }
        else if (!(strcmp(name2, graphHead->name))) {
            head2 = &(graphHead->adjHead);
            idTwo = graphHead->id;
        }

        graphHead = graphHead->next;
    } /* if (!(*head1 || *head2)) return 3; / I don't even */
    deleteNode(head1, idTwo);
    deleteNode(head2, idOne);
    return 0;
}

int deleteVertex(graphNode** head, int target) {
    if (!head || !*head) return 1; /* Emptey list */
    graphNode* temp;
    /* V If the first node is target ID */
    if ((*head)->id == target) {
        temp = *head;
        *(head) = (*head)->next;
        free(temp);
        return true;
    }

    graphNode* tracer = *head;
    while (tracer->next && !(tracer->next->id == target)) {
        tracer = tracer->next;
    }
    if (!tracer->next) return 1;

    temp = tracer->next;
    tracer->next = tracer->next->next;
    free(temp);
    return 0;
}

int deleteVertexAndLinks(graphNode** graphHead, const char* target) {
    if (!graphHead || !*graphHead) return 1;
    graphNode* temp;

    if (!(strcmp((*graphHead)->name, target))) {

        while ((*graphHead)->adjHead) {
            severIDLink(*graphHead,
              (*graphHead)->id,
              (*graphHead)->adjHead->id);
        }
        temp = *graphHead;
        (*graphHead) = (*graphHead)->next;
        pushAvailableIDs(temp->id); /* push the old id as unused */
        free(temp);
        return 0;
    } /*first is target*/

    graphNode* tracer = *graphHead;
    while (tracer->next && strcmp(target, tracer->next->name)) {
        tracer = tracer->next;
    }

    if (!tracer->next) return 1;
    temp = tracer->next;

    while (temp->adjHead)
        severIDLink(*graphHead, temp->id, temp->adjHead->id);


    tracer->next = tracer->next->next;
    pushAvailableIDs(temp->id);
    free(temp);

    return 0;
}






