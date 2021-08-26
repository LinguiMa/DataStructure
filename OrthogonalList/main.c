#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int OrthType;
//ͼOrthogonal�洢�ṹ
typedef struct EdgeList//�߱�ṹ
{
    int tailvex;//����±�
    int headvex;//�յ��±�
    struct EdgeList *headlink,*taillink;//ָ���ս����ͬ����һ���ߣ�ָ�������ͬ����һ����
}EdgeList,*EdgeListPtr;
typedef struct VexNode//�����ṹ
{
    OrthType data;//����Ԫ��
    EdgeListPtr firstin;//ָ��߱��иö�������
    EdgeListPtr firstout;//ָ��
}VexNode,OrthList[MAXSIZE];
//ʮ������洢�ṹ
typedef struct
{
    OrthList orthlist;
    int numVertexes,numEdges;
}OGraph;

void CreatOrthList(OGraph *O)
{
    printf("������ʮ������Ľڵ����ͱ�����\n");
    scanf("%d %d",&O->numVertexes,&O->numEdges);
    printf("��������%d \n ������%d\n",O->numVertexes,O->numEdges);
    //�����������飬ָ�����ÿ�
    for(int i=0;i<O->numVertexes;++i)
    {
        printf("�����붥�㣺\n");
        scanf("%d",&O->orthlist[i].data);
        O->orthlist[i].firstin=NULL;
        O->orthlist[i].firstout=NULL;
    }
    //�ȳ�ʼ�����ߣ��ٳ�ʼ�����
    for(int k=0;k<O->numEdges;k++)
    {
        int i,j;
        printf("������ߵ������յ㣺\n");
        scanf("%d %d",&i,&j);
        EdgeListPtr e = (EdgeListPtr)malloc(sizeof(EdgeList));//����һ���ߴ洢�ռ�
        e->tailvex=i;
        e->headvex=j;
        e->headlink=NULL;
        e->taillink=O->orthlist[i].firstout;//ͷ�巨
        O->orthlist[i].firstout=e;
    }
    //��ʼ�����
    for(int k=0;k<O->numEdges;k++)
    {
        int i,j;
        printf("������ߵ������յ�: \n");
        scanf("%d %d",&i,&j);
        EdgeListPtr p=O->orthlist[i].firstout;
        while(p)
        {
            if(p->tailvex==i&&p->headvex==j)
            {
                p->headlink=O->orthlist[j].firstin;//ͷ�巨
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
