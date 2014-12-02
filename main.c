#include <stdio.h>
#include <stdlib.h>

#include "graphing.h"

int main()
{
    printf("Hello world!\n");
    adjNode* test = NULL;
    pushAdjNode(&test, 4, 15);
    pushAdjNode(&test, 7, 21);
    pushAdjNode(&test, 2, 19);
    printConnections(test);
    return 0;
}
