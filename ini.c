/*----------------------------------------------------------------*/
/*  Program Name: ini.c                                           */
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

int maxnodenum=0,maxlinknum=0;
int node1id,node2id,pathid;
double dis;

void initial()
{
    int i=0,j=0;
    //initial the array and various
    for (i=0;i<NODENUM;i++)
    {
        node[i].oldID=0;
        node[i].x=0.0;
        node[i].y=0.0;
        for (j=0;j<NODENUM;j++)
        {
            if (i==j)
                path[i][j].distance=0.0;    //  A to A is 0
            else
                path[i][j].distance=MAXLENGTH;   //assign max value
        }
        for (j=0;j<NODENUM;j++)
            path[i][j].route=j;  // from i to j through j

    //printf("ini node %d",i);   test run in large array
    }
    for (i=0;i<PATHNUM;i++)
    {
        link[i].oldID=0;
        link[i].from=0;
        link[i].to=0;
    }
}

void readmapfile()
{
    FILE *fp;
    int i;
    char tempstr[DATALEN];
    if ((fp=fopen(MAPDATAFILE,"r"))==NULL)
    {
        printf("Map Data file a cannot be opened,please check the file!\n");
        exit(0);
    }
//    printf("\n  Map is been parsing ,wait...\n");

    //search the <node>,create the table of old and new nodes, and fprintf them for gnuplot
    i=0;
    while(fgets(tempstr,DATALEN-1,fp))
    {
        if (strstr(tempstr,"<node")!=NULL)
        {
             node[i].oldID=trunc2int(tempstr,"<node id=","lat=");
             node[i].y=trunc2float(tempstr,"lat=","lon=");
             node[i].x=trunc2float(tempstr,"lon=","/node>");
//printf("newnodeid=%d,oldnodeid=%d, coordinates X=%lf Y=%lf \n",i,nodetable[i],nodeX[i],nodeY[i]);
             i++;
        }
    }
    maxnodenum=i;//calculate the amount of node
    rewind(fp);   //reset file point
    i=0;
    while(fgets(tempstr,DATALEN-1,fp))
    {
        if (strstr(tempstr,"<link")!=NULL)
        {
             pathid=trunc2int(tempstr,"<link id=","node=");
             node1id=trunc2int2(tempstr,"node=","node=");
             node2id=trunc2int3(tempstr,"node=","way=");
             dis=trunc2float(tempstr,"length=","veg=");
             link[i].oldID=pathid;
             link[i].from=getnewnodeid(node1id);
             link[i].to=getnewnodeid(node2id);
             path[getnewnodeid(node1id)][getnewnodeid(node2id)].distance=dis;     //distance of a to b =  distance of b to a
             path[getnewnodeid(node2id)][getnewnodeid(node1id)].distance=dis;     //distance of a to b =  distance of b to a
             i++;
           //  path[getnewnodeid(node1id)][getnewnodeid(node2id)]=pathid;

//printf("pathid=%d,from node id=%d(%d)  to node id=%d(%d) %lf \n",pathid,node1id,getnewnodeid(node1id),node2id,getnewnodeid(node2id),dis);

        }
    }
    maxlinknum=i;
    fclose(fp); //close map file point

}

void writemapfile()
{
    int i;
    FILE *fpw;
    char tempstr1[80],tempstr2[80];
    if ((fpw=fopen(OUTFILE1,"w+"))==NULL)
    {
        printf(" OutData file1 cannot be opened,please check the file!\n");
        exit(0);
    }
    for (i=0;i<maxnodenum;i++)
    {
        gcvt(node[i].x,7,tempstr1);
        gcvt(node[i].y,8,tempstr2);
        strcat(tempstr1,"   ");
        strcat(tempstr1,tempstr2);
        fprintf(fpw,"%s\n",tempstr1);
    }
    fclose(fpw);//finish the print of map

    if ((fpw=fopen(OUTFILE2,"w+"))==NULL)
    {
        printf(" OutData file2 cannot be opened,please check the file!\n");
        exit(0);
    }
    for (i=0;i<maxlinknum;i++)
    {
        gcvt(node[link[i].from].x,7,tempstr1);
        gcvt(node[link[i].from].y,8,tempstr2);
        strcat(tempstr1,"   ");
        strcat(tempstr1,tempstr2);
        fprintf(fpw,"%s\n",tempstr1);

        gcvt(node[link[i].to].x,7,tempstr1);
        gcvt(node[link[i].to].y,8,tempstr2);
        strcat(tempstr1,"   ");
        strcat(tempstr1,tempstr2);
        fprintf(fpw,"%s\n\n\n",tempstr1);
    }
    fclose(fpw);

}


