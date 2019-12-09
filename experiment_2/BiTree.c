#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAXSIZE 100

/**************用于构造二叉树*/
// 全局变量
int indexx = 1;

typedef char String[24];
String str;

// 🔑添加字符串
int StrAssign(String T,char *chars){

    if (strlen(chars) > MAXSIZE)
        return -1;
    else {
        T[0] = strlen(chars);
        for (int i = 1; i <= T[0]; i++)
        {
            T[i] = *(chars+i-1);
        }
        return 0;
    }
}
/**************************/

typedef char TElemType;

TElemType Nil = ' '; /*字符型以空格为空*/

// 🔨节点结构
typedef struct BiTNode{
    TElemType data; // data
    struct BiTNode *lchild, *rchild; // leftchild and right child
}BiTNode, *BiTree;


/********stack************/

typedef struct stack
{
    BiTNode *elements[50];
    int top;
}seqstack;


seqstack s;

void init(){
    s.top = 0;
}

void Push(BiTNode *temp){
    s.top ++;
    s.elements[s.top] = temp;
}

BiTNode *Pop(){
    BiTNode *temp = s.elements[s.top];
    s.top--;
    return temp;
}

/********************/
// 🔑 访问节点
int visit(TElemType e){
    printf("%c",e);
    return 0;
}

// 🔑 构造空二叉树
int InitBiTree(BiTree *T){
    *T = NULL;
    return 0;
}

// 🔑 条件：二叉树存在  功能：销毁二叉树
int DestroyBiTree(BiTree *T){
    if(*T){
        if ( (*T)->lchild )   // leftchild
            DestroyBiTree(&(*T)->lchild);
        if ( (*T)->rchild )
            DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T = NULL;
    }
    return 0;
}

// 🔑创建二叉树，按照先根顺序输入节点的值
// #->表示空树，构建二叉链表表示二叉树 T
int CreateBiTree(BiTree *T){
    TElemType ch;

    ch = str[indexx++];

    if (ch == '#')
        *T = NULL;
    else{
        //  分配内存
        *T = (BiTree)malloc(sizeof(BiTNode));

        // 异常情况
        if(!*T)
            exit(OVERFLOW);

        // 构建新节点
        (*T) -> data = ch;
        CreateBiTree(&(*T) -> lchild); // 构建左子树
        CreateBiTree(&(*T) -> rchild); // 构建右子树

    }

    return 0;
}

int PreOrder(BiTree T,int location){
    BiTree temp = T;
    int visit = 0;
    while(temp != NULL || s.top != 0 ){

        while(temp != NULL)// 先遍历左子树；
        {
            if(visit == location) {
                return 0;
            }
            //printf("序号：%d,内容:%c \n",visit, temp -> data);
            printf("%c ", temp -> data);
            visit++;
            Push(temp);
            temp = temp ->lchild;
        }
        if (s.top != 0){
            temp = Pop();
            temp = temp ->rchild;
        }

    }
	

//    printf("%c ", temp -> data);
//    Push(temp);
//    //temp = temp ->lchild;
//    printf("%c ", temp -> data);
//    temp = Pop();
//    temp = temp ->rchild;
//    printf("%c ", temp -> data);
    return 0;

}

int PreOrderVisit(BiTree T,int location){
    printf("路径: ");
	PreOrder(T,location);
    printf(" 长度：%d",location);
    printf("\n");
	return 0;
}

/************************************************/
int main (){
    BiTree T;
    InitBiTree(&T);
    init();
    StrAssign(str,"124#67##8###3#5##"); //先根遍历输入
    int num = 8;
    CreateBiTree(&T);

    for (int i = 1; i <=num ; ++i) {
        PreOrderVisit(T,i);
    }



    return 0;
}
