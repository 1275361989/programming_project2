
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "shortestpath.h"
#include "function.h"

 int main()
{
    FILE *fp,*fpw;
    char tempstr[DATALEN],tempstr1[80],tempstr2[80],currdir[256];

    int i,j;
    int inputnode1,inputnode2;
    int maxnodenum=0,maxlinknum=0;
    int node1id,node2id,pathid;
    double dis;

    printf("\nWelcome to use my program!\n");


    if ((fp=fopen(MAPDATAFILE,"r"))==NULL)
    {
        printf("Map Data file a cannot be opened,please check the file!\n");
        exit(0);
    }
    printf("\n  Map is been parsing ,wait...\n");
    //initial the array and various
    for (i=0;i<NODENUM;i++)
    {
        nodetable[i]=0;
        nodeX[i]=0.0;
        nodeY[i]=0.0;
        for (j=0;j<NODENUM;j++)
        {
            if (i==j)
                distancenode[i][j]=0.0;    //  A to A is 0
            else
                distancenode[i][j]=MAXLENGTH;   //assign max value
        }
        for (j=0;j<NODENUM;j++)
            path[i][j]=j;  // from i to j through j
            path[i][j]=j;  // from i to j through j
    //printf("ini node %d",i);   test run in large array
    }
    for (i=0;i<PATHNUM;i++)
    {
        pathtable[i]=0;
        pathfrom[i]=0;
        pathto[i]=0;
    }
    //search the <node>,create the table of old and new nodes, and fprintf them for gnuplot
    i=0;
    while(fgets(tempstr,DATALEN-1,fp))
    {
        if (strstr(tempstr,"<node")!=NULL)
        {
             nodetable[i]=trunc2int(tempstr,"<node id=","lat=");
             nodeY[i]=trunc2float(tempstr,"lat=","lon=");
             nodeX[i]=trunc2float(tempstr,"lon=","/node>");
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
             pathtable[i]=pathid;
             pathfrom[i]=getnewnodeid(node1id);
             pathto[i]=getnewnodeid(node2id);
             distancenode[getnewnodeid(node1id)][getnewnodeid(node2id)]=dis;     //distance of a to b =  distance of b to a
             distancenode[getnewnodeid(node2id)][getnewnodeid(node1id)]=dis;     //distance of a to b =  distance of b to a
             i++;
           //  path[getnewnodeid(node1id)][getnewnodeid(node2id)]=pathid;

//printf("pathid=%d,from node id=%d(%d)  to node id=%d(%d) %lf \n",pathid,node1id,getnewnodeid(node1id),node2id,getnewnodeid(node2id),dis);

        }
    }
    maxlinknum=i;
    fclose(fp); //close map file point

//  check two node is alone


    if ((fpw=fopen(OUTFILE1,"w+"))==NULL)
    {
        printf(" OutData file1 cannot be opened,please check the file!\n");
        exit(0);
    }
    for (i=0;i<maxnodenum;i++)
    {
        gcvt(nodeX[i],7,tempstr1);
        gcvt(nodeY[i],8,tempstr2);
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
        gcvt(nodeX[pathfrom[i]],7,tempstr1);
        gcvt(nodeY[pathfrom[i]],8,tempstr2);
        strcat(tempstr1,"   ");
        strcat(tempstr1,tempstr2);
        fprintf(fpw,"%s\n",tempstr1);

        gcvt(nodeX[pathto[i]],7,tempstr1);
        gcvt(nodeY[pathto[i]],8,tempstr2);
        strcat(tempstr1,"   ");
        strcat(tempstr1,tempstr2);
        fprintf(fpw,"%s\n\n\n",tempstr1);
    }
    fclose(fpw);

    printf("\n We will calculate shortestpath, wait for 3-5minute...\n\n");
    shortestpathbyfloyd(1);   //calculate node shortest path

//test modular
/*
printf("node 21545939(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(21545939),getnewnodeid(1601125136),distancenode[getnewnodeid(21545939)][getnewnodeid(1601125136)]);
printf("node 354734667(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(354734667),getnewnodeid(1601125136),distancenode[getnewnodeid(354734667)][getnewnodeid(1601125136)]);

printf("node 1601125136(%d) to node 21545939(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(21545939),distancenode[getnewnodeid(1601125136)][getnewnodeid(21545939)]);
printf("node 1601125136(%d) to node 354734667(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(354734667),distancenode[getnewnodeid(1601125136)][getnewnodeid(354734667)]);
*/
while(1)
{
    printf("Please input two node IDs (comma-delimited):");
    scanf("%d,%d",&inputnode1,&inputnode2);

if ((getnewnodeid(inputnode1)<0) || (getnewnodeid(inputnode2)<0))
    {
        printf(" Sorry£¡There is a error in input node id!\n");
        exit(0);
    }
//    int cat1=isalonenode(getnewnodeid(inputnode1));
//    int cat2=nodetable[getnewnodeid(inputnode2)];
    if ((isalonenode(getnewnodeid(inputnode1))==1)||(isalonenode(getnewnodeid(inputnode2))==1))
    {
        printf(" Sorry! There is no path between these two nodes!\n");
        exit(0);
    }


    int v,w,k;
    v=getnewnodeid(inputnode1);
    w=getnewnodeid(inputnode2);
//27081332-> 354734667 1601125136
    if ((fpw=fopen(OUTFILE3,"w+"))==NULL)
    {
        printf(" OutData file3 cannot be opened,please check the file!\n");
        exit(0);
    }
    //has shortest path
    if (distancenode[v][w]<(MAXLENGTH-1))
    {
        k=path[v][w];
        printf("\n the shortest path of %d(%d)->%d(%d) is £º%10.6lf \n", inputnode1,v,inputnode2,w,distancenode[v][w]);//v,w may need delete
        printf("path: %d",inputnode1);//print the start
        while(k!=w)   //prevent the circle
        {
            printf("-> %d",nodetable[k]);//print the node though in the screen

            fprintf(fpw,"%10.6lf   %10.6lf\n",nodeX[v],nodeY[v]);//print the node though to the file
            fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",nodeX[k],nodeY[k]);

            v=k;
            k = path[k][w];
        }
        printf("-> %d\n",inputnode2);//print the final node
        fprintf(fpw,"%10.6lf   %10.6lf\n",nodeX[v],nodeY[v]);
        fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",nodeX[k],nodeY[k]);
    }
    else
    {
        printf("\n %d -> %d shortest path is£ºNULL\n", inputnode1,inputnode2);
        printf("sorry! There is no path between these two nodes!\n");
    }
    fclose(fpw);

    if ((fpw=fopen(PLOTSCRIPTFILE,"w+"))==NULL)
    {
        printf(" Plot script file3 cannot be created,please check the file!\n");
        exit(0);
    }
    //look for Final_Map.map
    //<bounding  minLat=53.801600 minLon=-1.564000 maxLat=53.811000 maxLon=-1.543100 /bounding>
    fprintf(fpw,"set xrange [-1.564000:-1.543100]\n");
    fprintf(fpw,"set yrange [53.8016:53.811]\n");
    fprintf(fpw,"unset key\n");
    fprintf(fpw,"plot \'");
    fprintf(fpw,OUTFILE1);
    fprintf(fpw,"\' with points lc rgb \"red\" pointtype 7 pointsize 0.8, \\\n");
    fprintf(fpw,"\'");
    fprintf(fpw,OUTFILE2);
    fprintf(fpw,"\' with line lc rgb \"red\", \\\n");
    fprintf(fpw,"\'");
    fprintf(fpw,OUTFILE3);
    fprintf(fpw,"\' with line lc rgb \"blue\" linewidth 3 \n");
    fclose(fpw);
    //run gnuplot file
    if ( !access(PLOTSCRIPTFILE,0) )
    {
        system(PLOTSCRIPTFILE);
    }
//don't link 550173412->304898150
//has link 27081332->304898150,342660317,274246828,250133218
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
/* reference documentation  https://blog.csdn.net/jeffleo/article/details/53349825
/*_____________________________________________________________________________________________________________________*/
