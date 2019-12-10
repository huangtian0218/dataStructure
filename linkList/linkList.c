#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"

#define MAXSIZE 50     /*masize of the linklist*/

// define the node [data][right]
typedef struct node
{
    int data;
    struct node *right;
}node;

// define the double node [left][data][right]
typedef struct doubleNode
{
    struct doubleNode *left;
    int data;
    struct doubleNode *right;
}doubleNode;

// define linklist
typedef struct  node *linkList;

// define double link list
typedef struct doubleNode *doubleLinkList;

// visit one node
int visit(int c){
    printf("[%d]",c);
    return 1;
}

// initialize the linkList
int initList(linkList *L){
    *L = (linkList)malloc(sizeof(node));

    if (!(*L))
        return -1;
    (*L)->right = NULL;
    return 0;
}

// initialize the doublelist
int initDoubleList(doubleLinkList *L){
    *L = (doubleLinkList)malloc(sizeof(doubleNode));

    if (!(*L))
        return -1;

    (*L)->right = *L; // point to the head
    (*L)->left = *L;

    return 0;
}

//clear the list
int clearList(linkList *L){
    linkList p,q;
    p = (*L)->right;
    while(p)                /*  没到表尾 */
    {
        q=p->right;
        free(p); // 释放空间
        p=q;
    }
    (*L)->right=NULL;        /* 头结点指针域为空 */
    return 0;
}

// get the length of the list
int listLength(linkList L){
    int i = 0;

    linkList p = L->right; // p points to the first one node

    while (p){
        i++;
        p = p->right;
    }
    return i;
}

// Insert a new node to the list
int listInsert(linkList *L,int location ,int input){
    int j;
    linkList p,s;
    p = *L; // p points to the head of the list
    j = 1; // j means the first

    // locate to the i node -> p
    while ((p) && (j < location) ){
        p = p->right;
        j++;
    }
    if (!p && j>1) // the node donot exist
    {
        printf("the node location do not exist!\n");
        return -1;
    }

    s = (linkList)malloc(sizeof(node)); // create a new node;

    // insert the node 1 = right; 0 = left;
    s -> data = input;
    s -> right = p->right;
    p -> right = s;

    return 0;
}

// Traverse the whole list
int listTraverse(linkList L, int mathod){
    // mathod means the display mode
    linkList p = L->right;
    int result = 0;
    int max = 0;
    int min = 9999999;

    if (p != NULL){
        visit(p->data);
        result += (p->data);
        if (p->data >= max ){max = p->data;}
        if (p->data <= min ){min = p->data;}
        p = p -> right;
    }

    while (p){
        printf("->");
        visit(p->data);
        result += (p->data);
        if (p->data >= max ){max = p->data;}
        if (p->data <= min ){min = p->data;}
        p = p -> right;

    }

    printf("\n");

    if(mathod == 2){
        printf("数据域之和：%d\n",result);

    }else if (mathod == 1){
        printf("最大值：%d ; 最小值：%d\n",max,min);
    }else if (mathod == 0){
        return 0;
    }

    return 0;
}

// Build the list
int listBuild(linkList L ,int *arr,int len){
    int location = 1;

    listInsert(&L,1,arr[0]); // insert the first data

    for (int i = 1; i< len; i++){
        location++;
        listInsert(&L,location,arr[i]);
    }

    return 0;
}

// get the length of the double link list
int doubleListLength(doubleLinkList *L){
    int i = 0;
    doubleLinkList head = *L;
    doubleLinkList p = (*L)->right; // p points to the first one node

    while (p != head){
        i++;
        p = p->right;
    }
    return i;
}

int doubleListInsert(doubleLinkList *L, int location, int input){
    int j;
    doubleLinkList p,s,head;
    p = *L;
    head = *L;
    j = 1;

    // locate to the i node -> p
    while ((p) && (j < location) ){
        p = p->right;
        j++;
    }
    if (!p && j>1) // the node donot exist
    {
        printf("the node location do not exist!\n");
        return -1;
    }

    s = (doubleLinkList)malloc(sizeof(doubleNode)); // create a new node;

    s -> data = input;
    s->left = p;
    s -> right = *L; // the new node's right is the head

    p -> right = s;
    (*L)-> left = s; // the head's left is the new node

    return 0;

}

// build the double list
int doubleListBuild(doubleLinkList L,int *arr, int len){
    int locaion = 1;

    doubleListInsert(&L,1,arr[0]);
    for(int i = 1; i<len; i++){
        locaion ++;
        doubleListInsert(&L,locaion,arr[i]);
    }
    return 0;
}

// Traverse the double list
int doubleListTraverse(doubleLinkList *L, int location) {
    // location means the first node to visit
    int j;
    doubleLinkList p, start;
    p = *L;
    j = 1;

    while (j <= location) {
        p = p->right;
        j++;
    }

    start = p;

    printf("双链表起始数值：%d\n遍历：", p->data);
    visit(p->data);
    p = p->right;

    while (p != start) {
        if (p == *L) {
            p = p->right; // skip the head node
        } else {
            visit(p->data);
            p = p->right;
        }
    }

    return 0;
}

// 链表排序
int linkListSort(linkList L){
    // 交换排序法
    linkList p = L->right;// 第一个排序结点
    while (p){
        linkList min = p; // min指向当前结点
        linkList pointer = p; // pointer用于遍历未排序结点
        while(pointer){
            if(pointer->data < min->data){
                min = pointer;
            }
            pointer = pointer->right;
        }
        // 交换
        int temp = p->data;
        p->data = min->data;
        min->data = temp;

        p = p->right; //指向下一个排序结点
    }

    return 0;
}


int main(){
    linkList L1,L2;
    doubleLinkList L3;

    // test data 1
    // int arr[MAXSIZE] = {100,2,55,3,56,1,5,6,4};
    // int len = 9;

    // test datd 2
    int arr[MAXSIZE] = {1,2,75,4,56,31,25,65,9,4};
    int len = 10;

    initList(&L1);
    initList(&L2);
    initDoubleList(&L3);

    listBuild(L1,arr,len); // 无序
    printf("L1:");
    listTraverse(L1,1);

    listBuild(L2,arr,len); // 无序
    linkListSort(L2); //排序
    printf("L2:");
    listTraverse(L2,2);

    doubleListBuild(L3,arr,len);
    doubleListTraverse(&L3,2);

}

