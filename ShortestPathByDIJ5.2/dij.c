#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define MAX_VEX 9
#define INFINITY 9999
int g[MAX_VEX][MAX_VEX] = {INFINITY};
void init()
{
        memset(g,INFINITY,sizeof(g));
        FILE * fp = fopen("edge.txt","r");
        if(!fp)
        {
                printf("edge.txt not exists!\n");
                return ;
        }
        while(!feof(fp))
        {
                int l,r,val;
                fscanf(fp,"%d",&l);
                fscanf(fp,"%d",&r);
                fscanf(fp,"%d",&val);
                g[l][r] = val;
                g[r][l] = val;
        }
        int i,j;
        for(i = 0;i<MAX_VEX;i++)
        {
                for(j = 0;j<MAX_VEX;j++)
                {
                        printf("g[%d][%d]=%d ",i,j,g[i][j]);
                }
                printf("\n");
        }
        fclose(fp);
}
//贪心法则
void DIJ(int v0,int dst)
{
        int final[MAX_VEX] = {0};
        int path[MAX_VEX] = {0}; //保存路径 Path[i]表示到i最短路径的上一个节点
        int dis[MAX_VEX] = {0};  //保存v0到i的距离贪心改变
        int n = MAX_VEX;
        int i,k,tmp;
        for(i =0;i<n;i++)
        {
                g[i][i] = 0;
                if(g[v0][i]==0 || g[v0][i] ==INFINITY)
                  path[i] = 0;
                else
                  path[i] = v0;
                dis[i] = g[v0][i];
        }


        for(i=0;i<n;i++)
        {
                int min = INFINITY*2;
                if(i==v0)
                  continue;
                //每次选出一个到源点的最小值
                for(k=0;k<n;k++)
                {
                        if(!final[k] && dis[k] <min)
                        {
                                min = dis[k];
                                tmp = k;
                        }
                }
                final[tmp] = 1;

                //利用已经求出的最小值更新路径 更新其他路径的距离
                for(k=0;k<n;k++)
                {
                        if(!final[k] && min+g[tmp][k] <dis[k])
                        {
                                dis[k] = min +g[tmp][k];
                                path[k] = tmp;
                        }
                }
        }

        //print src to dst path
        //将最短路径保存到trace数组中此处为逆序保存  最后在逆序输出即为正确顺序
        int trace[MAX_VEX];
        int tot= 0;
        trace[tot++] = dst;
        int temp = path[dst];
        while(temp!=v0)

        {
                trace[tot++] = temp;
                temp = path[temp];
        }
        trace[tot] = v0;
        for(k = tot;k>=0;tot--)
        {
                if(trace[tot]==dst)
                {
                        printf("%d\n",dst);
                        break;
                }
                else
                {
                        printf("%d->",trace[tot]);
                }
        }

}

int main()
{
        init();
        DIJ(0,3);
        return 0;
}