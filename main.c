#include <stdio.h>
#include <stdlib.h>

#include "graphing.h"
#include "debugExamples.h"
#include "rtTracking.h"

int main()
{
    printf("Hello world!\n");
    idStackInit();

    //basicGraphAndSampleLists();
    //basicFreeIDSample();
    //basicGraph2();
    basicGraph3();
    printf("%u %u", sizeof(void*), sizeof(unsigned long));
    return 0;
}
