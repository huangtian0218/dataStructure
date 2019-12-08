#include "stdio.h"
#include "stdlib.h"

#define MAXSIZE 50

typedef struct TreeNode {
    struct TreeNode *leftPtr;  /* pointer to left subtree */
    int data;
    int level;
    struct TreeNode *rightPtr; /* pointer to right subtree */
}TreeNode, *Tree;


int initTree(Tree *T){
    *T = NULL;
    return 0;
}

void insertNode(Tree *T,int value,int level){
    level ++;

    if (*T == NULL){
        // 树为空时
        *T = malloc(sizeof(TreeNode));

        if (*T  != NULL){
            (*T)->data = value;
            (*T)->leftPtr = NULL;
            (*T)->rightPtr = NULL;
            (*T)->level = level;
            //printf("Insert value: %d success, lelevl:%d\n",value,level-1);
            //return 0;
        } else{
            printf("error occured\n");

        }

    }
    else{
        // 树不为空

        // 插入到左子树
        if(value < (*T)->data){
            insertNode(&(*T)->leftPtr,value,level);
        }
        else{
            // 插入右子树
            if (value > (*T)->data){
                insertNode(&(*T)->rightPtr,value,level);
            }
            else {
                if ((*T)->rightPtr == NULL || (*T)->leftPtr == NULL){
                    printf("叶子结点");
                }
//                printf("%d ",((*T)->leftPtr)->data);
//                printf("%d ",((*T)->rightPtr)->data);
                printf("结点已存在 值域: %d; 层数:%d", (*T)->data,(*T)->level);
                // return 1;
            }

        }

    }

}
int printTree(Tree T){

    while (T != NULL){
        printTree(T->leftPtr);
        printf("[%d] ",T->data);
        printTree(T->rightPtr);
        T = NULL;
    }
    return 0;
}

int getLevel(Tree *T, int value){
    int level = 0;

    return level;
}

int main(){
    TreeNode *T = NULL;
    int temp = 0;
    int arr[MAXSIZE] = {8,3,10,1,6,14,4,7,13};
    int len = 9;
    for (int i = 0; i < len; i++) {
        insertNode(&T,arr[i],0);

    }
    printf("查找二叉树构建完成\n");

    printf("请输入要插入的数字：\n");

    scanf("%d",&temp);

    insertNode(&T,temp,0);

    printf("\n中序遍历：\n");

    printTree(T);
    return 0;
}
