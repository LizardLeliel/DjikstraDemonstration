#ifndef GRAPHING_HEADER
#include <stdlib.h>
#include <stdbool.h>

typedef struct ConnectionNode {
    int id;
    int distance;
    struct ConnectionNode* next;
} adjNode;

typedef struct VertexNode {
    int id;
    char* name;

    adjNode* adjHead;
    struct VertexNode* next;
} graphNode;

/* Print functions */
void printConnections(adjNode* listHead);
void printNodeAndConnections(graphNode* graphHead);

/* Basic pushing */
void pushAdjNode(adjNode** listHead, int newID, int newDistance);
void pushSortedAdjNode(adjNode** listHead, int newID, int newDistance);
void pushVertex(graphNode** graphHead, int newID, const char* cstring);

/* Existance checking */
bool existantIDVertex(graphNode* graphHead, int newID);
bool existantNamedVertex(graphNode* graphHead, const char* cstring);

/* Implementation functions */
void pushUniqueVertex(graphNode** graphHead, int newID, const char* cstring);
void connectVertices(graphNode* head, int idOne, int idTwo, int distance);





#define GRAPHING_HEADER
#endif
