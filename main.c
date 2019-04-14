
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "shortestpath.h"
#include "function.h"
#include "ini.h"
#include "output.h"
 int main()
{
    int inputnode1,inputnode2;

    printf("\nWelcome to use my program!\n");
    initial();
    printf("The map has been initial.\n");
//  check two node is alone
    read();
    write();
    printf("\n We will calculate shortestpath, wait for 70 seconds...\n\n");
    //shortestpathbyfloyd(1);   //calculate node shortest path

//test modular
/*
printf("node 21545939(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(21545939),getnewnodeid(1601125136),distancenode[getnewnodeid(21545939)][getnewnodeid(1601125136)]);
printf("node 354734667(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(354734667),getnewnodeid(1601125136),distancenode[getnewnodeid(354734667)][getnewnodeid(1601125136)]);

printf("node 1601125136(%d) to node 21545939(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(21545939),distancenode[getnewnodeid(1601125136)][getnewnodeid(21545939)]);
printf("node 1601125136(%d) to node 354734667(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(354734667),distancenode[getnewnodeid(1601125136)][getnewnodeid(354734667)]);
*/
while(1)
{
    printf("\nPlease input two node IDs (comma-delimited):");
    scanf("%d,%d",&inputnode1,&inputnode2);
    dijkstra(inputnode1);   //calculate node shortest path
    writePath(inputnode1,inputnode2);
    printMap();
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* reference documentation  https://blog.csdn.net/jeffleo/article/details/53349825
/*_____________________________________________________________________________________________________________________*/
