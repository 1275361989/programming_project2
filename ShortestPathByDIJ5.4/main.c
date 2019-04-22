/*----------------------------------------------------------------*/
/*  Program Name: main.c                                          */
/*  Author: Jason Zhang                                           */
/*  Last changes: 2019.4.1                                        */
/*  Version: 2.1                                                  */
/*----------------------------------------------------------------*/
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
//    initial();
//    printf("The map data has been initial.\n");
//    readmapfile();
//    writemapfile();

    while(1)
    {
        printf("\nPlease input two Node IDs (comma-delimited,input 0 then exit. ex:12345,67890):");
        scanf("%d,%d",&inputnode1,&inputnode2);
        if ((inputnode1==0)||(inputnode2==0))
        {
            printf("\nGoodbye!\n"); exit(0);
        }

        printf("The map data has been initial.\n");
        initial();
        readmapfile();
        if ((getnewnodeid(inputnode1)<0) || (getnewnodeid(inputnode2)<0))
        {
            printf("Sorry.There is a error in input node id,try again!\n");
            continue;
        }

        dijkstra(inputnode1);   //calculate node shortest path

        if (writePath(inputnode1,inputnode2)==1)
        {
            writemapfile();
            printMap();
        }

    }
}

//test modular
/*
printf("node 21545939(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(21545939),getnewnodeid(1601125136),distancenode[getnewnodeid(21545939)][getnewnodeid(1601125136)]);
printf("node 354734667(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(354734667),getnewnodeid(1601125136),distancenode[getnewnodeid(354734667)][getnewnodeid(1601125136)]);

printf("node 1601125136(%d) to node 21545939(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(21545939),distancenode[getnewnodeid(1601125136)][getnewnodeid(21545939)]);
printf("node 1601125136(%d) to node 354734667(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(354734667),distancenode[getnewnodeid(1601125136)][getnewnodeid(354734667)]);
*/

/*------------------------------------------------------------------------------------*/
/* reference documentation  https://blog.csdn.net/jeffleo/article/details/53349825 */

