#include <MacTypes.h>
#include "stdio.h"
#include "stdlib.h"

#define maxsize 100

// 边表结点
typedef struct EdgeNode{
    int adjvex; /* 邻接点域,存储该顶点对应的下标 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

// 表顶点结点
typedef struct VertexNode {
    int data; /* 顶点域,存储顶点信息 */
    EdgeNode *firstedge; /* 边表头指针 */
}VertexNode, AdjList[maxsize];

// 边链表
typedef struct {
    AdjList adjList;
    /* 图中当前顶点数和边数 */
    int numNodes;
    int numEdges;
}GraphAdjList;

int CreateALGraph(GraphAdjList *G){
    int i = 0;
    int j,k;
    EdgeNode *e;
    printf("请输入顶点数和边数：");
    scanf("%d,%d",&G->numNodes,&G->numEdges); /* 输入顶点数和边数 */

    /*建立顶点表*/
    for (i = 0; i < G->numNodes; i++) {
        printf("请输入顶点序号为%d的数据：",i);
        scanf("%d",&G->adjList[i].data);    /* 输入顶点信息 */
        G->adjList[i].firstedge=NULL;   /* 将边表置为空表 */
    }

    /*建立边表*/
    for (k = 0;  k< G->numEdges ; k++) {
        printf("输入边(vi,vj)上的顶点序号:\n");
        scanf("%d,%d", &i, &j); /* 输入边(vi,vj)上的顶点序号 */

        e = (EdgeNode *) malloc(sizeof(EdgeNode)); //生成边表结点
        e->adjvex = j; // 临接序号为j
       // e->next =NULL;

        e->next = G->adjList[i].firstedge; // 将e的指针只想当前顶点上指向的顶点
        G->adjList[i].firstedge = e; // 将当前顶点的指针指向e

//        e = (EdgeNode *) malloc(sizeof(EdgeNode)); //生成边表结点
//        e->adjvex = i; // 临接序号为i
//        e->next = G->adjList[j].firstedge; // 将e的指针只想当前顶点上指向的顶点
//        G->adjList[j].firstedge = e; // 将当前顶点的指针指向e

    }

    printf("图创建完成。\n");
    return 0;
}

int visited[maxsize];

void DFS(GraphAdjList *G, int i){
    // 访问从序号i开始的
    int j;
    EdgeNode *p = G->adjList[i].firstedge;
    visited[i] = 1;
    printf("[%d]",G->adjList[i].data);
   // printf("%d ",G->adjList[p->adjvex].data);
    while (p != NULL){
        if(visited[p->adjvex] != 1){
            DFS(G,p->adjvex);
            p = p->next;
        }
    }

}

void DFS_Main(GraphAdjList *G){
    for(int i = 0; i< G->numNodes ;i++){
        visited[i] = 0;
    }

    for(int i = 0; i<G->numNodes;i++){
        if(visited[i] == 0){
            DFS(G,i);
        }
    }

}

/*队列***/
typedef struct
{
    int data[maxsize];
    int front;      /* 头指针 */
    int rear;       /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}Queue;
/* 初始化一个空队列Q */
int InitQueue(Queue *Q)
{
    Q->front=0;
    Q->rear=0;
    return  0;
}
/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
int QueueEmpty(Queue Q)
{
    if(Q.front==Q.rear) /* 队列空的标志 */
        return 0;
    else
        return -1;
}
/* 若队列未满，则插入元素e为Q新的队尾元素 */
int  EnQueue(Queue *Q,int e)
{
    if ((Q->rear+1)%maxsize == Q->front)    /* 队列满的判断 */
        return -1;
    Q->data[Q->rear]=e;         /* 将元素e赋值给队尾 */
    Q->rear=(Q->rear+1)%maxsize;/* rear指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    return  0;
}
/* 若队列不空，则删除Q中队头元素，用e返回其值 */
int DeQueue(Queue *Q)
{
    if (Q->front == Q->rear)            /* 队列空的判断 */
        return -1;
    int result =Q->data[Q->front];              /* 将队头元素赋值给e */
    Q->front=(Q->front+1)%maxsize;  /* front指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    return  result;
}
/**/

Queue Q;

void BFS(GraphAdjList *G, int i) {
    InitQueue(&Q);
    for (int i = 0; i < G->numNodes; i++) {
        visited[i] = 0;
    }
    printf("[%d]", G->adjList[i].data);
    visited[i] = 1;
    EnQueue(&Q, i);

    while (QueueEmpty(Q) != 0) {
        i = DeQueue(&Q);
        EdgeNode *p = G->adjList[i].firstedge;
        while (p != NULL) {
            if (visited[p->adjvex] != 1) {
                printf("[%d]", G->adjList[p->adjvex].data);
                visited[p->adjvex] = 1;
                EnQueue(&Q, p->adjvex);
                p = p->next;
            }
        }
    }
}

void clearVisited(GraphAdjList *G){
    for (int i = 0; i < G->numNodes; i++) {
        visited[i] = 0;
    }
}

int main(){
    GraphAdjList G;
    CreateALGraph(&G);

    printf("DFS：");
    DFS_Main(&G);
    clearVisited(&G);

    printf("\nBFS：");
    BFS(&G,0);
    return 0;
}
