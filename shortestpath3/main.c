/*--------------------------------------------------------------------------------------------------------------*/
/*  Program Name                                                                                                */
/*  Author: Jason Zhang                                                                                                            */
/*  Last changes datatime 2019.                                                                                 */
/*  Version 0.8                                                                                                 */
/*--------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAPDATAFILE "Final_Map.map"
#define OUTFILE1 "MapPointInfo.dat"
#define OUTFILE2 "MapLineInfo.dat"
#define OUTFILE3 "ShortestPath.dat"
#define DATALEN 1024
#define NODENUM 4000
#define PATHNUM 4000
#define MAXLENGTH 9999.0

long nodetable[NODENUM];   //store all node, old node's number  change to new node's number
double nodeX[NODENUM],nodeY[NODENUM];  //node X,Y coordinates
double distancenode[NODENUM][NODENUM]; //node diatance from A to B
int path[NODENUM][NODENUM]; //id, path from A to B
int pathtable[PATHNUM],pathfrom[PATHNUM],pathto[PATHNUM]; //link id列表 //某link起点  //某link终点


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
    {
        return d1*(-1);
    }
    else
    {
       return d1;
    }
}

//find sub string
//input: string,sub string
//output: index
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

//find sub string；secord
//input: string,sub string
//output: index
int findstring2(char* str1,char* str2)
{
    int i,j;

    i=findstring(str1,str2);   //first
    j=findstring(str1+i+strlen(str2),str2);   //secord

    return i+strlen(str2)+j;
}

//get sub string between of string1 and string2
//input:
//output:
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
//input:
//output:
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
//input:
//output:
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

//get sub string between of string1 and string2
//input:
//output:
double trunc2float(char total[], char left[], char right[])
{
    int i=0,j=0,k=0;
    char t[256];

//    for (i=0;i<256;i++) t[i]='\0';

    for ( i=findstring(total,left)+strlen(left),j=findstring(total,right); i<j; i++)
    {
        t[k] = total[i];
        k++;
    }
    t[k] = '\0';
    return round6(atof(t));
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

int shortestpathbyfloyd()
{
    int f,t,k;     //f from node;  t dest node;   k  mid node

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

 int main()
{
    FILE *fp,*fpw;
//    char tempstr[DATALEN],*first=NULL,*last=NULL;
    char tempstr[DATALEN],tempstr1[80],tempstr2[80];

    int i,j;
    int inputnode1,inputnode2;
    int maxnodenum=0,maxlinknum=0;
    int node1id,node2id,pathid;
    double dis;

    printf("       Welcome to use my program!\n ");
    printf("       Please input first node id:");
    printf("       Please input second node id:");
    scanf("%d,%d",&inputnode1,&inputnode2);
//    scanf("%d",);

//    scanf("%d", &a);  //输入整数并赋值给变量a
//    scanf("%d", &b);  //输入整数并赋值给变量b

    if ((fp=fopen(MAPDATAFILE,"r"))==NULL)
    {
        printf("Map Data file a cannot be opened,please check the file!\n");
        exit(0);
    }
    printf("\n We will parse map data file,wait...\n");
    //初始化变量
    for (i=0;i<NODENUM;i++)
    {
        nodetable[i]=0;
        nodeX[i]=0.0;
        nodeY[i]=0.0;
        for (j=0;j<NODENUM;j++)
        {
            if (i==j)
                distancenode[i][j]=0.0;    // from A to A Assign 0
            else
                distancenode[i][j]=MAXLENGTH;   //assign max value
        }
        for (j=0;j<NODENUM;j++) path[i][j]=j;  // from i to j assign j
//printf("ini node %d",i);   test run in large array
    }
    for (i=0;i<PATHNUM;i++)
    {
        pathtable[i]=0;
        pathfrom[i]=0;
        pathto[i]=0;
    }

    //首先找到所有结点，生成新旧编号对照表，并记录结点位置，供gnuplot画图
    i=0;
    while(fgets(tempstr,DATALEN-1,fp))
    {
        if (strstr(tempstr,"<node")!=NULL)
        {
             nodetable[i]=trunc2int(tempstr,"<node id=","lat=");
             nodeY[i]=trunc2float(tempstr,"lat=","lon=");
             nodeX[i]=trunc2float(tempstr,"lon=","/node>");
printf("newnodeid=%d,oldnodeid=%d, coordinates X=%lf Y=%lf \n",i,nodetable[i],nodeX[i],nodeY[i]);
            i++;
        }
    }
    maxnodenum=i;
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
             distancenode[getnewnodeid(node1id)][getnewnodeid(node2id)]=dis;     //distance of a to b =  distance of b to a
             distancenode[getnewnodeid(node2id)][getnewnodeid(node1id)]=dis;     //distance of a to b =  distance of b to a
             pathtable[i]=pathid;
             pathfrom[i]=getnewnodeid(node1id);
             pathto[i]=getnewnodeid(node2id);
           //  path[getnewnodeid(node1id)][getnewnodeid(node2id)]=pathid;

printf("pathid=%d,from node id=%d(%d)  to node id=%d(%d) %lf \n",pathid,node1id,getnewnodeid(node1id),node2id,getnewnodeid(node2id),dis);
            i++;
        }
    }
    maxlinknum=i;
    fclose(fp); //close map file point

//  check two node is alone
    if ((getnewnodeid(inputnode1)<0) || (getnewnodeid(inputnode2)<0))
    {
        printf(" sorry！ There is a error in input node id!\n");
        exit(0);
    }
//    int cat1=isalonenode(getnewnodeid(inputnode1));
//    int cat2=nodetable[getnewnodeid(inputnode2)];
    if ((isalonenode(getnewnodeid(inputnode1))==1)||(isalonenode(getnewnodeid(inputnode2))==1))
    {
        printf(" there is no path between these two nodes!\n");
        exit(0);
    }

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
    fclose(fpw);

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
    shortestpathbyfloyd();   //calculate node shortest path

//test modular
/*
printf("node 21545939(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(21545939),getnewnodeid(1601125136),distancenode[getnewnodeid(21545939)][getnewnodeid(1601125136)]);
printf("node 354734667(%d) to node 1601125136(%d) distance=%10.6lf \n",getnewnodeid(354734667),getnewnodeid(1601125136),distancenode[getnewnodeid(354734667)][getnewnodeid(1601125136)]);

printf("node 1601125136(%d) to node 21545939(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(21545939),distancenode[getnewnodeid(1601125136)][getnewnodeid(21545939)]);
printf("node 1601125136(%d) to node 354734667(%d) distance=%10.6lf \n",getnewnodeid(1601125136),getnewnodeid(354734667),distancenode[getnewnodeid(1601125136)][getnewnodeid(354734667)]);
*/
int v,w,k;
v=getnewnodeid(inputnode1);
w=getnewnodeid(inputnode2);
//27081332-> 354734667 1601125136
    if ((fpw=fopen(OUTFILE3,"w+"))==NULL)
    {
        printf(" OutData file3 cannot be opened,please check the file!\n");
        exit(0);
    }
printf("\n %d(%d) -> %d(%d) 的最小路径为：%10.6lf \n", inputnode1,v,inputnode2,w,distancenode[v][w]);

k=path[v][w];

printf("path: %d",inputnode1);//打印起点
while(k!=w)   //写代码防止死循环
{
printf("-> %d",nodetable[k]);//打印中间点

fprintf(fpw,"%10.6lf   %10.6lf\n",nodeX[v],nodeY[v]);
fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",nodeX[k],nodeY[k]);

v=k;
k = path[k][w];
}
printf("-> %d\n",inputnode2);
fprintf(fpw,"%10.6lf   %10.6lf\n",nodeX[v],nodeY[v]);
fprintf(fpw,"%10.6lf   %10.6lf\n\n\n",nodeX[k],nodeY[k]);

    fclose(fpw);

}
/*--------------------------------------------------------------------------------------------------------------------*/
/* reference documentation  https://blog.csdn.net/jeffleo/article/details/53349825
/*_____________________________________________________________________________________________________________________*/
