#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 50

void Swap(int *heap, int len);        /* 交换根节点和数组末尾元素的值 */
void BuildMaxHeap(int *heap, int len,int num,int count);/* 构建大顶堆 */

/* Function: 构建大顶堆 */
void BuildMaxHeap(int *heap, int len,int num,int count)
{
    int i;
    int temp;
    //交换后输出一下：
    printf("比较次数：%d\n",count);
    printf("当前堆:");
    for (int j = 0; j < num ; ++j) {
        printf("%d ",heap[j]);
    }
    printf("\n");

    for (i = len/2-1; i >= 0; i--)
    {
        count++;
        if ((2*i+1) < len && heap[i] < heap[2*i+1])    /* 根节点大于左子树 */
        {
            // 交换操作

            temp = heap[i];
            heap[i] = heap[2*i+1];
            heap[2*i+1] = temp;


            /* 检查交换后的左子树是否满足大顶堆性质 如果不满足 则重新调整子树结构 */
            if ((2*(2*i+1)+1 < len && heap[2*i+1] < heap[2*(2*i+1)+1]) || (2*(2*i+1)+2 < len && heap[2*i+1] < heap[2*(2*i+1)+2]))
            {
                BuildMaxHeap(heap, len,num,count);
            }
        }
        count++;
        if ((2*i+2) < len && heap[i] < heap[2*i+2])    /* 根节点大于右子树 */
        {

            temp = heap[i];
            heap[i] = heap[2*i+2];
            heap[2*i+2] = temp;

            /* 检查交换后的右子树是否满足大顶堆性质 如果不满足 则重新调整子树结构 */
            if ((2*(2*i+2)+1 < len && heap[2*i+2] < heap[2*(2*i+2)+1]) || (2*(2*i+2)+2 < len && heap[2*i+2] < heap[2*(2*i+2)+2]))
            {


                BuildMaxHeap(heap, len,num,count);
            }
        }
    }
}

/* Function: 交换交换根节点和数组末尾元素的值*/
void Swap(int *heap, int len)
{
    int temp;

    temp = heap[0];
    heap[0] = heap[len-1];
    heap[len-1] = temp;

}


int getran(int *arr,int num){
    int i = 0;
    while (i < num){
        int ran = rand();
        if (ran >= 10 && ran <= 1000000){
            arr[i] = ran;
            i ++;
        }

    }

//    for (int j = 0; j < num; j++) {
//        printf("%d ",arr[j]);
//    }
//    printf("\n");
    return 0;
}

int heapRank(int *a,int len,int num){
    int i;

    for (i = len; i > 0; i--)
    {
        BuildMaxHeap(a, i,num,0);
        Swap(a, i);
    }
//    printf("比较次数：%d\n",count);

//    for (i = 0; i < len; i++)
//    {
//        printf("%d ", a[i]);
//    }
    return 0;
}

int main()
{
//    int a[6] = {7, 3, 8, 5, 1, 2};
//    int len = 6;    /* 数组长度 */
//    int i;
    FILE *fp =NULL;
    fp = fopen("/Users/levypan/geek/dataStructure/experiment_3/heapRank.txt","w+");
    fprintf(fp, "...运行结果...\n");
    int len = 0;

    printf("请输入数组长度（小于 50）:");
    scanf("%d",&len);
    for (int i = 0; i < 2; i++) {
        int arr[MAXSIZE];
//        int len = 0;
//
//        printf("请输入数组长度（小于 50）:");
//        scanf("%d",&len);

        getran(arr,len);
        printf("****生成的随机数:");
        for (int j = 0; j < len; j++) {
            printf("%d ",arr[j]);
        }
        printf("\n");
        fprintf(fp, "排序前:");
        for (int j = 0; j < len; j++) {
            fprintf(fp, "%d ",arr[j]);
        }

        fprintf(fp, "\n");

        heapRank(arr,len,len);
        fprintf(fp, "排序后:");
        for (int j = 0; j < len; j++) {
            fprintf(fp, "%d ",arr[j]);
        }
        fprintf(fp, "\n---------------------------------\n");
    }

//    int len = 0;
//    getran(arr,7);
//
//    printf("After Rank:\n");
//    heapRank(arr,7);
//
//    printf("\n----------------\n");
//    getran(arr,6);
//    printf("After Rank:\n");
//    heapRank(arr,6);

    fclose(fp);
    return 0;
}

