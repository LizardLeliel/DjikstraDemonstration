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
int pushUniqueVertex(graphNode** graphHead, const char* cstring);
int linkVertices(graphNode* head, int idOne, int idTwo, int distance);
int linkByName(graphNode* head, const char* nameOne,
  const char* nameTwo, int distance);


/* Removal functions */
void severLink(graphNode* head, int idOne, int idTwo, int distance);
void deleteVertex(graphNode* head, int target);
void deleteVertextAndLinks(graphNode* head, int target);



#define GRAPHING_HEADER
#endif
