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
    adjNode* adjHead;
    struct VertexNode* next;
} graphNode;

/* == Base functions == */
void printConnections(adjNode* listHead);
/* pushAdhNode is legacy */
void pushAdjNode(adjNode** listHead, int newID, int newDistance);
void pushSortedAdjNode(adjNode** listHead, int newID, int newDistance);
void pushVertex(graphNode** graphHead, int newID);
bool existantVertext(graphNode** graphHead, int newID);
void pushUniqueVertex(graphNode** graphHead, int newID);
void connectVertices(graphNode* head, int idOne, int idTwo, int distance);





#define GRAPHING_HEADER
#endif
