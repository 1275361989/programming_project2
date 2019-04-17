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
//̰�ķ���
void DIJ(int v0,int dst)
{
        int final[MAX_VEX] = {0};
        int path[MAX_VEX] = {0}; //����·�� Path[i]��ʾ��i���·������һ���ڵ�
        int dis[MAX_VEX] = {0};  //����v0��i�ľ���̰�ĸı�
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
                //ÿ��ѡ��һ����Դ�����Сֵ
                for(k=0;k<n;k++)
                {
                        if(!final[k] && dis[k] <min)
                        {
                                min = dis[k];
                                tmp = k;
                        }
                }
                final[tmp] = 1;

                //�����Ѿ��������Сֵ����·�� ��������·���ľ���
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
        //�����·�����浽trace�����д˴�Ϊ���򱣴�  ��������������Ϊ��ȷ˳��
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