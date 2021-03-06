#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "shortestpath.h"
#include "function.h"

int writePath(int inputnode1,int inputnode2)
{
    FILE *fpw;
    int v,w,k;

    int trace[NODENUM];//the array is ready for the anti-oder output
    int j,count;

    for(j=0;j<NODENUM;j++)
        trace[j]=0;

    v=getnewnodeid(inputnode1);//v is the start
    w=getnewnodeid(inputnode2);//w is the end
//27081332-> 354734667 1601125136
    if ((fpw=fopen(OUTFILE3,"w+"))==NULL)//if the file is error, it will give the warnings
    {
        printf(" OutData file3 cannot be opened,please check the file!\n");
        exit(-4);
    }
    //has shortest path
    if (path[v][w].distance<(MAXLENGTH-1))
    {
        count=0;
        trace[count++]=w;//reverse, put the end w as the start
        k=path[v][w].route;//k is node which is in path and closet to w
        while(k!=v)   //prevent the circle
        {
            trace[count++]=k;//the next node is k which closet to w(k)
            k = path[v][k].route;//update the k, and k is node which is in path and closet to k
        }
        trace[count]=v;//the end is the start node v

        printf("The shortest path of %d(%d)->%d(%d) is %10.6lf \n", inputnode1,v,inputnode2,w,path[v][w].distance);//v,w may need delete
        printf("path: %d",inputnode1);//print the start

        for(j=(count-1);j>0;j--)
        {
            k=trace[j];//k is the start of the path
            printf("-> %ld",node[k].oldID);//print the node though in the screen

            fprintf(fpw,"%10.6lf   %10.6lf\n",node[v].x,node[v].y);//print the node though to the file
            fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",node[k].x,node[k].y);
            v=k;
        }
        printf("-> %d\n",inputnode2);//print the final node
        fprintf(fpw,"%10.6lf   %10.6lf\n",node[v].x,node[v].y);
        fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",node[w].x,node[w].y);
        fclose(fpw);

        return 1;
    }
    else
    {//if there is something wrong in input or during the finding
        printf("\n %d -> %d shortest path is NULL\n", inputnode1,inputnode2);
        printf("sorry! There is something wrong in input or finding!\n");

        return 0;
    }
}

void printMap()
{
    FILE *fpw;
    if ((fpw=fopen(PLOTSCRIPTFILE,"w+"))==NULL)//if the file is error, it will give the warnings
    {
        printf(" Plot script file3 cannot be created,please check the file!\n");
        exit(-5);
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
        system(PLOTSCRIPTFILE);//start the gnuplot
    }
//don't link 550173412->304898150
//has link 27081332->304898150,342660317,274246828,250133218
}


