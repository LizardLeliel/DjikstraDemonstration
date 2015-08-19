#ifndef GRAPHING_HEADER
#define GRAPHING_HEADER

#include <stdlib.h>
#include <stdbool.h>

typedef struct hashBucket
{
    unsigned int id;
    const char* symbol; // For collisions
    struct hashBucket* next; //  if collision happens
} hashBucket_t;

typedef struct hash
{
    hashBucket_t** hashArray;
} hash_t;

typedef struct ConnectionNode
{
    unsigned int id;
    unsigned int distance;
    struct ConnectionNode* next;
} adjNode;

typedef struct VertexNode
{
    unsigned int id;
    char* name;
    adjNode* adjHead;
    struct VertexNode* next;
} graphNode;

//
typedef struct idTracker 
{
    unsigned int currentHighest; // if == 0 then no ids.
    struct reuseStackNode
    {
        unsigned int unusedID;
        struct reuseStackNode* next;
    } *reuseStack;
} idTracker_t;

// Eventually we'll use this
typedef struct graph
{
    hash_t dictionary;
    idTracker_t idTracker;
    graphNode* head;
} graph_t;

// Note for me (ignore this):
// pushUnusedIDs();
// getNewID(idTracker* idTracker);
// searchID(hash_t* hash, const char* symbol);
// addPair(hash_t* hash, string, unsigned int);

// Get the string's corresponding ID (looks it up in the hash)
unsigned int getIDFromName(graph_t* graph, char* name);
unsigned int highestID(graph_t* graph);
void initGraph(graph_t* graph);

// Printing graph information - change to use graph_t
void printConnections(adjNode* listHead);
void printNodeAndConnections(graphNode* graphHead);
void printEveryVertex(graphNode* graphHead);
void printEverything(graphNode* graphHead);

// Basic pushing 
// Delete?
void pushAdjNode(adjNode** listHead, int newID, int newDistance); 
// Static?
void pushSortedAdjNode(adjNode** listHead, int newID, int newDistance); 
// Static?
void pushVertex(graphNode** graphHead, int newID, const char* cstring); 

// Existance checking - May get deleted, since most functions
//  need to get an id anyways so it'll be a lot of (if (x = getID() != 0)
//bool existantNamedVertex(graphNode* graphHead, const char* cstring);

// Implementation functions - start with these
int pushUniqueVertex(graph_t* graph, const char* name); 
// static
//int linkVertices(graphNode* head, int idOne, int idTwo, int distance); // static
int linkByName(graph_t* graphHead, const char* nameOne,
  const char* nameTwo, unsigned int distance); // "rename"



// removal functions
bool deleteNode(adjNode** head, int id);
int severIDLink(graphNode* graphHead, int idOne, int idTwo); // static?
int severNamedLink(graphNode* head, const char* name1, const char* name2);
int deleteVertex(graphNode** head, int target);
//^ This will may be delete in the end? (old comment, look into it later)
int deleteVertexAndLinks(graphNode** graphHead, const char* target); 
void deleteGraph(graph_t* graph);


// GRAPHING_HEADER
#endif
