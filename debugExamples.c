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
    pushAvailbleIDs(22);
    pushAvailbleIDs(5);
    pushAvailbleIDs(17);
    printf("%d %d %d",
    popAvailbleIDs(),
    popAvailbleIDs(),
    popAvailbleIDs());
}
