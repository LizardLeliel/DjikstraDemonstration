#ifndef GRAPHING_HEADER
#include <stdlib.h>
#include <stdbool.h>

typedef struct hashBucket hashBucket_t;

typedef struct hash hash_t;

typedef struct ConnectionNode
{
    int id;
    int distance;
    struct ConnectionNode* next;
} adjNode;

typedef struct VertexNode
{
    int id;
    char* name;
    adjNode* adjHead;
    struct VertexNode* next;
} graphNode;

// Eventually we'll use this
typedef struct graphNode
{
    hash_t* dictionary;
    graphNode* head;
} graph_t;

// Get the string's corresponding ID (looks it up in the hash)
unsigned int getIDFromName(graph_t* graph, char* name);


// Printing graph information
void printConnections(adjNode* listHead);
void printNodeAndConnections(graphNode* graphHead);
void printEveryVertex(graphNode* graphHead);
void printEverything(graphNode* graphHead);

/* Basic pushing */
void pushAdjNode(adjNode** listHead, int newID, int newDistance); // Delete?
void pushSortedAdjNode(adjNode** listHead, int newID, int newDistance); // Static?
void pushVertex(graphNode** graphHead, int newID, const char* cstring); // static?

/* Existance checking */
bool existantNamedVertex(graphNode* graphHead, const char* cstring);

/* Implementation functions */
int pushUniqueVertex(graphNode** graphHead, const char* cstring); 
int linkVertices(graphNode* head, int idOne, int idTwo, int distance); // static
int linkByName(graphNode* head, const char* nameOne,
               const char* nameTwo, int distance); // "rename"


// removal functions
bool deleteNode(adjNode** head, int id);
int severIDLink(graphNode* graphHead, int idOne, int idTwo); // static?
int severNamedLink(graphNode* head, const char* name1, const char* name2);
int deleteVertex(graphNode** head, int target);
/*^ This will probably be delete in the end */
int deleteVertexAndLinks(graphNode** graphHead, const char* target); 
void deleteGraph(graph_t* graph);


#define GRAPHING_HEADER
#endif
