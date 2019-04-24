
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ShortestPath.h"

double round6(double d)
{
    int flag;
    double d1=0.0;
    if (d<0.0)
      flag=0;
    else
      flag=1;
    d1=fabs(d);
    d1=round((d1+0.000000001)*1000000)/1000000;
    if (flag==0)
        return d1*(-1);
    else
       return d1;
}

//find substring
//input: str1:string,str2:substring
//output: the first index of substring
int findstring(char* str1,char* str2)
{
    int i,j,flag=-1;
    for(i=0,j=0;str1[i]!=NULL;i++)
    {
        while(str1[i]==str2[j]&&str1[i]&&str2[j])
        {
            i++;
            j++;
            if(str2[j]==NULL)//if the function read the end of the str2
            {
                flag=i-j;//record the str2's first index in str1
                return flag;
            }
        }
       // j=0;
    }
    return flag;
}

//find sub string��secord
//input: string,sub string
//output: index
int findstring2(char* str1,char* str2)
{
    int i,j;

    i=findstring(str1,str2);   //first
    j=findstring(str1+i+strlen(str2),str2);   //find the second string after the first by skipping the proper length

    return i+strlen(str2)+j;//there are two same string in tag <link>, the function will return the second one
}

//get sub string between of string1 and string2
//input: string,sub string
//output: index
long trunc2int(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

    for ( i=findstring(total,left)+strlen(left),j=findstring(total,right); i<j; i++)//i is the start of the string we need, and j is the end
    {
        t[k] = total[i];
        k++;
    }
    t[k] = '\0';
    return atol(t);
}

//get sub string between of string1 and string2
//input: string,sub string
//output: index
long trunc2int2(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

    for ( i=findstring(total,left)+strlen(left),j=findstring2(total,right); i<j; i++)
    {
        t[k] = total[i];
        k++;
    }
    t[k] = '\0';
    return atol(t);
}

//get sub string between of string1 and string2
//input: string,sub string
//output: index
long trunc2int3(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

    for ( i=findstring2(total,left)+strlen(left),j=findstring(total,right); i<j; i++)
    {
        t[k] = total[i];
        k++;
    }
    t[k] = '\0';
    return atol(t);
}

int getnewnodeid(long oldnodeid)
{
    int i,index=-1;
    for(i=0;i<NODENUM;i++)
    {
        if (node[i].oldID==oldnodeid)
        {
           index=i; break;
        }
    }
    return index;
}

//get sub string between of string1 and string2
//input:
//output:
double trunc2float(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

    for ( i=findstring(total,left)+strlen(left),j=findstring(total,right); i<j; i++)
    {
        t[k] = total[i];
        k++;
    }
    t[k] = '\0';
    return round6(atof(t));
}
//calculate shortest path by dijkstra
//imes: show process message

void dijkstra(long src)
{

     int sptSet[NODENUM]; // sptSet[i] will be true if vertex i is included in shortest
    // long road[NODENUM];

     src=getnewnodeid(src);

     for(int j=0;j<NODENUM;j++)
     {
          if(path[src][j].distance<MAXLENGTH)
            path[src][j].route=src;
          else
            path[src][j].route=-1;
     }


// path tree or shortest distance from src to i is finalized(已知)
//V=NODENUM
     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < NODENUM; i++)
        sptSet[i] = 0;// INT_MAX = MAXLENGTH

    sptSet[src]=1;
     // Distance of source vertex from itself is always 0
    // dist[src] = 0;

     // Find shortest path for all vertices
     for(int count = 0; count < NODENUM -1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in the first iteration.
       int u = minDistance(src,sptSet);

       // Mark the picked vertex as processed
       sptSet[u] = 1;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < NODENUM; v++)
        {
            if (!sptSet[v] && path[u][v].distance && path[src][u].distance != MAXLENGTH&& path[src][u].distance + path[u][v].distance < path[src][v].distance)
            {
                path[src][v].distance= path[src][u].distance+ path[u][v].distance;
                path[src][v].route=u;
            }
        }

        //dist[v] = dist[u] + graph[u][v];
         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
     }
     //for(int k=0;k<NODENUM;k++)
       // path[src][k].route=road[k];
     // print the constructed distance array
           // printSolution(dist, V);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(long src,int sptSet[])
{
   // Initialize min value
   int min = MAXLENGTH;
   double min_index=0;

   for (int v = 0; v < NODENUM; v++)
    {
        if (sptSet[v] == 0 && path[src][v].distance<=min)
         {
             min = path[src][v].distance;
             min_index = v;
         }
    }
   return min_index;
}


//IS the node alone?
//input: a node new id
//output: 0-not alone 1- alone
int isalonenode(int newnodeid)
{
    int i,flag=1;

    for (i=0;i<NODENUM;i++)
    {
       if (path[i][newnodeid].distance<MAXLENGTH)
       {
            if (i!=newnodeid)
            {
                flag=0;
                break;
            }
       }
    }
    return flag;
}
