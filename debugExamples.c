#include "debugExamples.h"
#include "graphing.h"
#include "rtTracking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void basicGraphAndSampleLists() {
    adjNode* test = NULL;
    pushAdjNode(&test, 4, 15);
    pushAdjNode(&test, 7, 21);
    pushAdjNode(&test, 2, 19);
    printConnections(test); printf("\n\n");

    adjNode* anotherTest = NULL;

    pushSortedAdjNode(&anotherTest, 5, 12);
    pushSortedAdjNode(&anotherTest, 6, 16);
    pushSortedAdjNode(&anotherTest, 7, 24);
    pushSortedAdjNode(&anotherTest, 8, 20);
    pushSortedAdjNode(&anotherTest, 9, 14);
    pushSortedAdjNode(&anotherTest, 10, 5);
    pushSortedAdjNode(&anotherTest, 11, 33);
    pushSortedAdjNode(&anotherTest, 12, 23);
    pushSortedAdjNode(&anotherTest, 13, 20);
    printConnections(anotherTest); printf("\n\n");

    graphNode* graphTest = NULL;
    pushVertex(&graphTest, 3, "Hello, world!");
    pushVertex(&graphTest, 2, "Rexcalibur");

    graphTest->adjHead = anotherTest;

    printNodeAndConnections(graphTest); printf("\n\n");

    pushVertex(&graphTest, 4, "Megidolaon");
    graphTest->adjHead = test;

    printNodeAndConnections(graphTest); printf("\n");
    printNodeAndConnections(graphTest->next); printf("\n\n");

    printf("%s %s %s\n\n",
           existantNamedVertex(graphTest, "Rexcalibur")    ? "true" : "false",
           existantNamedVertex(graphTest, "Robin")         ? "true" : "false",
           existantNamedVertex(graphTest, "Hello, world!") ? "true" : "false");
}

void basicFreeIDSample() {
    pushAvailableIDs(22);
    pushAvailableIDs(5);
    pushAvailableIDs(17);
    printf("%d %d %d",
      nextAvailableIDs(),
      nextAvailableIDs(),
      nextAvailableIDs());
}

void basicGraph2() {
    graphNode* testGraph = NULL;

    pushUniqueVertex(&testGraph, "Graph1");
    pushUniqueVertex(&testGraph, "Graph2");
    if (pushUniqueVertex(&testGraph, "Graph3")) printf("Sucess\n");
    else printf("Fail\n");
    if (pushUniqueVertex(&testGraph, "Graph1")) printf("Sucess\n");
    else printf("Fail\n");

    pushUniqueVertex(&testGraph, "Graph4");

    printf("\n\n");

    printNodeAndConnections(testGraph);
    printf("\nNodes which exist: %s, %s, %s, %s\n", testGraph->name,
      testGraph->next->name, testGraph->next->next->name,
      testGraph->next->next->next->name);

    printf("Their ids: %d %d %d %d\n", testGraph->id,
      testGraph->next->id, testGraph->next->next->id,
      testGraph->next->next->next->id);

    printf("%d\n", linkVertices(testGraph, 3, 4, 25));
    linkVertices(testGraph, 4, 2, 12);
    linkVertices(testGraph, 4, 1, 13);

    printNodeAndConnections(testGraph); printf("\n");
    printNodeAndConnections(testGraph->next); printf("\n");

    linkByName(testGraph, "Graph3", "Graph1", 95);

    printNodeAndConnections(testGraph->next);



}
