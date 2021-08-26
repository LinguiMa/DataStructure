#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int OrthType;
//图Orthogonal存储结构
typedef struct EdgeList//边表结构
{
    int tailvex;//起点下标
    int headvex;//终点下标
    struct EdgeList *headlink,*taillink;//指向终结点相同的下一条边，指向起点相同的下一条边
}EdgeList,*EdgeListPtr;
typedef struct VexNode//顶点表结构
{
    OrthType data;//顶点元素
    EdgeListPtr firstin;//指向边表中该顶点的入边
    EdgeListPtr firstout;//指向
}VexNode,OrthList[MAXSIZE];
//十字链表存储结构
typedef struct
{
    OrthList orthlist;
    int numVertexes,numEdges;
}OGraph;

void CreatOrthList(OGraph *O)
{
    printf("请输入十字链表的节点数和边数：\n");
    scanf("%d %d",&O->numVertexes,&O->numEdges);
    printf("顶点数：%d \n 边数：%d\n",O->numVertexes,O->numEdges);
    //建立顶点数组，指针域置空
    for(int i=0;i<O->numVertexes;++i)
    {
        printf("请输入顶点：\n");
        scanf("%d",&O->orthlist[i].data);
        O->orthlist[i].firstin=NULL;
        O->orthlist[i].firstout=NULL;
    }
    //先初始化出边，再初始化入边
    for(int k=0;k<O->numEdges;k++)
    {
        int i,j;
        printf("请输入边的起点和终点：\n");
        scanf("%d %d",&i,&j);
        EdgeListPtr e = (EdgeListPtr)malloc(sizeof(EdgeList));//申请一个边存储空间
        e->tailvex=i;
        e->headvex=j;
        e->headlink=NULL;
        e->taillink=O->orthlist[i].firstout;//头插法
        O->orthlist[i].firstout=e;
    }
    //初始化入边
    for(int k=0;k<O->numEdges;k++)
    {
        int i,j;
        printf("请输入边的起点和终点: \n");
        scanf("%d %d",&i,&j);
        EdgeListPtr p=O->orthlist[i].firstout;
        while(p)
        {
            if(p->tailvex==i&&p->headvex==j)
            {
                p->headlink=O->orthlist[j].firstin;//头插法
                O->orthlist[j].firstin=p;
            }
            p=p->taillink;
        }
    }
}
void PrintOGraph(OGraph *O)
{
    EdgeListPtr p1,p2;
    for(int i=0;i<O->numVertexes;i++)
    {
        p1=O->orthlist[i].firstout;
        p2=O->orthlist[i].firstin;
        printf("%d ",O->orthlist[i].data);
        while(p1)
        {
            printf("%d_%d ",p1->tailvex,p1->headvex);
            p1=p1->taillink;
        }
        while(p2)
        {
            printf("%d_%d ",p2->tailvex,p2->headvex);
            p2=p2->headlink;
        }
            printf("\n");
    }
}

int main()
{
    OGraph O;
    CreatOrthList(&O);
    PrintOGraph(&O);

    printf("Hello world!\n");
    return 0;
}
