#include "debugExamples.h"
#include "graphing.h"
#include "unusedIDs.h"
#include "djikstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NEWL printf("\n")


void basicGraph3()
{
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

    /* This code is designed to test deletion and pushing after deleting.
     * it gets in the way of seeing djikstra's algorithm work */

    //printEverything(test);
    //printf("^This is everything before deletions^\n");

    printf("%d\n", deleteVertexAndLinks(&test, "Kuala Lumpur"));
    printEverything(test);
    printf("^After Kuala Lumpur was deleted^\n");
    printf("==================================\n");

    pushUniqueVertex(&test, "Imaginary land");
    //linkByName(test, "Imaginary land", "Kyoto", 29);

    /*Imaginary land should have ID 6*/
    printf("Test: %s %d\n", test->name, test->id);
    printEverything(test);
    printf("^New push^\n");

    pushUniqueVertex(&test, "OMG");
    printf("We just pushed \"OMG\", and the new vertex's number is: %d\n",
           test->id);

    printEverything(test);

    //printf("%p, id: %d\n", test, test->id);

    deleteVertexAndLinks(&test, "OMG");

    //initDjikstra(test, 3);

    //printHeapArray(test);
    //printP_QUEUE();


    /* HERE IT IS */
    //printf("\n\n!!!!!!!!!!\n\n\n");
    shortPathNode_t* result = djikstraAll(test, 3);
    //printDResults(test, result);
    printDjikstraResultsAll(test, result);

    bool heap = false;
    //heap = true;
    if (heap)
    {
        priorityHeap_t* heap = newHeap();

        printf("\nNo pushed: max: %d currentNext: %d\n\n",
               heap->max, heap->currentNext);

        shortPathNode_t spn1 = { NULL, NULL, 10, NULL };
        shortPathNode_t spn2 = { NULL, NULL, 20, NULL };
        shortPathNode_t spn3 = { NULL, NULL, 30, NULL };
        shortPathNode_t spn4 = { NULL, NULL, 40, NULL };

        insertIntoHeap(heap, &spn2);
        insertIntoHeap(heap, &spn1);

        printf("\nTwo pushed: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);

        printf("Top of heap (should be 10): %d", popHeap(heap)->distance);
        printf("\nOne popped: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);
        printf("Top of heap (should be 20): %d", popHeap(heap)->distance);
        printf("\nOne popped: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);

        insertIntoHeap(heap, &spn1);
        insertIntoHeap(heap, &spn2);

        printf("\nNow pushing 10 then 20 then popping each: %d %d\n",
               popHeap(heap)->distance, popHeap(heap)->distance);

        insertIntoHeap(heap, &spn3);
        insertIntoHeap(heap, &spn2);
        insertIntoHeap(heap, &spn1);

        while (!(heap->currentNext == heap->max - 1))
        {
            insertIntoHeap(heap, &spn4);
        }

        printf("Many pushed: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);

        printf("Popping once (should be 10): %d\n", popHeap(heap)->distance);
        insertIntoHeap(heap, &spn2);
        printf("pushing after popping: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);
        insertIntoHeap(heap, &spn3);
        printf("Pushing one more: max: %d currentNext: %d\n",
               heap->max, heap->currentNext);

        insertIntoHeap(heap, &spn1);
        printf("Pushing past the max: max: %d currentNext %d\n",
               heap->max, heap->currentNext);

        printf("\n Troting through the array: ");
        for (int i = 0; i < 10; ++i)
        {
            printf("%d, ", heap->heapArray[i]->distance);
        } NEWL ; NEWL ;


        printf("\nPopping many: ");

        while (heap->currentNext != 3)
        {
            printf("%d, ", popHeap(heap)->distance);
        } NEWL ; NEWL ;

        printf("Next: %d\n", heap->heapArray[0]->distance);
        printf("Next next: %d\n", heap->heapArray[1]->distance);
        printf("Next next next: %d\n", heap->heapArray[2]->distance);
        //printf("Next next next next: %d\n", heap->heapArray[3]->distance);

        while (heap->currentNext != 0)
        {
            printf("The rest: %d, ", popHeap(heap)->distance);
        } NEWL ; NEWL ;
    }
}




#undef NEWL


