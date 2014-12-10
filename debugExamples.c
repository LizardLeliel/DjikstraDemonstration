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

#define NEWL printf("\n")

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

    printNodeAndConnections(testGraph->next); printf("\n");

    /*deleteNode(&(testGraph->next->adjHead), 1);*/
    /*printNodeAndConnections(testGraph->next); NEWL ;*/
    /* ^ This works! But the function evidently works in the next
     * function, and its useful to have that graphNode set right */

    severIDLink(testGraph, 3, 4); printf("Reached here \n");
    printNodeAndConnections(testGraph->next); NEWL ;
    printNodeAndConnections(testGraph); NEWL ;
    printNodeAndConnections(testGraph->next->next->next); NEWL ;

    severNamedLink(testGraph, "graph1", "graph4");
    printNodeAndConnections(testGraph); NEWL ;
    printNodeAndConnections(testGraph->next->next->next); NEWL ;

    severNamedLink(testGraph, "Graph1", "Graph4");
    printNodeAndConnections(testGraph); NEWL ;
    printNodeAndConnections(testGraph->next->next->next); NEWL ;
}

void basicGraph3() {
    graphNode* test = NULL;
    /* Test data based off my Civilization V game */
    /* http://cloud-4.steampowered.com/ugc/49867998648437970/AE9960A7C9AC6B6325C7F6C8B5880E38020E0FD2/ */
    pushUniqueVertex(&test, "Kyoto");
    pushUniqueVertex(&test, "Osaka");
    pushUniqueVertex(&test, "Satsuma");
    pushUniqueVertex(&test, "Tokyo");
    pushUniqueVertex(&test, "Ragusa");
    pushUniqueVertex(&test, "Kuala Lumpur");
    pushUniqueVertex(&test, "Ankara");
    pushUniqueVertex(&test, "Istanbul");
    pushUniqueVertex(&test, "Kuala Lumpur");
    pushUniqueVertex(&test, "Bursa");
    pushUniqueVertex(&test, "Edirne");
    pushUniqueVertex(&test, "Kagoshima");
    pushUniqueVertex(&test, "Nagoya");

    printEveryVertex(test); NEWL ;

    /* I counted these by hand by tiles :S */
    /* Most are probably approximations. Also, counting the roads */
    linkByName(test, "Kagoshima", "Nagoya", 5);
    linkByName(test, "Kagoshima", "Istanbul", 7);
    linkByName(test, "Kagoshima", "Bursa", 5);

    linkByName(test, "Nagoya", "Edirne", 6);

    linkByName(test, "Bursa", "Istanbul", 4);
    linkByName(test, "Bursa", "Ragusa", 8);
    linkByName(test, "Bursa", "Satsuma", 11);
    linkByName(test, "Bursa", "Kuala Lumpur", 8);

    linkByName(test, "Istanbul", "Edirne", 4);
    linkByName(test, "Istanbul", "Kuala Lumpur", 6);
    linkByName(test, "Istanbul", "Satsuma", 9);
    linkByName(test, "Istanbul", "Ragusa", 9);

    linkByName(test, "Ragusa", "Kuala Lumpur", 8);
    linkByName(test, "Ragusa", "Satsuma", 5);
    linkByName(test, "Ragusa", "Kyoto", 6);

    linkByName(test, "Kuala Lumpur", "Ankara", 3);
    linkByName(test, "Kuala Lumpur", "Satsuma", 6);

    linkByName(test, "Ankara", "Tokyo", 4);

    linkByName(test, "Satsuma", "Tokyo", 3);
    linkByName(test, "Satsuma", "Kyoto", 3);

    linkByName(test, "Tokyo", "Osaka", 4);

    linkByName(test, "Kyoto", "Osaka", 4);

    printEverything(test);
    printf("^This is everything before deletions^\n");

    printf("%d\n", deleteVertexAndLinks(&test, "Kuala Lumpur"));
    printEverything(test);
    printf("^After Kuala Lumpur was deleted^\n");
    printf("==================================\n");

    pushUniqueVertex(&test, "Imaginary land");
    linkByName(test, "Imaginary land", "Kyoto", 29);

    /*Imaginary land should have ID 6*/
    printf("Test: %s %d\n", test->name, test->id);
    printEverything(test);
    printf("^New push^\n");

    pushUniqueVertex(&test, "OMG");
    printf("We just pushed \"OMG\", and the new vertex's number is: %d\n",
           test->id);
}



#undef NEWL


