
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

//find sub string
//input: string,sub string
//output: the first index of sub string
int findstring(char* str1,char* str2)
{
    int i,j,flag=-1;
    for(i=0,j=0;str1[i]!=NULL;i++)
    {
        while(str1[i]==str2[j]&&str1[i]&&str2[j])
        {
            i++;
            j++;
            if(str2[j]==NULL)
            {
                flag=i-j;
                return flag;
            }
        }
        j=0;
    }
    return flag;
}

//find sub string£»secord
//input: string,sub string
//output: index
int findstring2(char* str1,char* str2)
{
    int i,j;

    i=findstring(str1,str2);   //first
    j=findstring(str1+i+strlen(str2),str2);   //secord

    return i+strlen(str2)+j;//there are two same string in tag <link>, the function will return the second one
}

//get sub string between of string1 and string2
//input: string,sub string
//output: index
long trunc2int(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

    for ( i=findstring(total,left)+strlen(left),j=findstring(total,right); i<j; i++)
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
        if (nodetable[i]==oldnodeid)
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
//calculate shortest path by floyd
//imes: show process message
int shortestpathbyfloyd(int imes)
{
    int f,t,k,icount;     //f from node;  t dest node;   k  mid node

    for (k=0;k<NODENUM;k++)
    {
        for (f=0;f<NODENUM;f++)
        {
            for (t=0;t<NODENUM;t++)
            {
                if (distancenode[f][t]>(distancenode[f][k]+distancenode[k][t]))
                {
                    distancenode[f][t]=distancenode[f][k]+distancenode[k][t];
                    path[f][t]=path[f][k];
                }
            }
        }
        if ((imes==1)&&((k%50)==0))     // show a dot per 10
        {
           printf(".");
        }
    }
    return 0;
}

//IS the node alone?
//input: a node new id
//output: 0-not alone 1- alone
int isalonenode(int newnodeid)
{
    int i,flag=1;

    for (i=0;i<NODENUM;i++)
    {
       if (distancenode[i][newnodeid]<MAXLENGTH)
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
