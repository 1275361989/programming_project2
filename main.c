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
    int inputnode1,inputnode2;//the two input node's id

    printf("\nWelcome to use system!\n");

    while(1)
    {
        printf("\nPlease input two Node IDs (comma-delimited,input 0 to exit:");
        scanf("%d,%d",&inputnode1,&inputnode2);
        if ((inputnode1==0)||(inputnode2==0))//if the input node is 0 ,exit the system
        {
            printf("\nnice to see you again !\n");
            exit(0);
        }

        initial();//initial the whole program
        readmapfile();//read information from map file
        printf("The map data has been initial.\n");
        if ((getnewnodeid(inputnode1)<0) || (getnewnodeid(inputnode2)<0))//if the input id is error, give the warning
        {
            printf("Sorry.There is a error in input node id,please try again!\n");
            continue;
        }
        if ((isalonenode(getnewnodeid(inputnode1))==1)||(isalonenode(getnewnodeid(inputnode2))==1))
        {
            printf(" Sorry! There is no path between these two nodes!please try again \n");
            continue;
        }

        dijkstra(inputnode1);   //calculate node shortest path

        if (writePath(inputnode1,inputnode2)==1)//if the two nodes have the link,write the path
        {
            writemapfile();//write the link and node
            printMap();//start the gnuplot
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

