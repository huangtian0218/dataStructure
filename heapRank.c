#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 50

void Swap(int *heap, int len);        /* 交换根节点和数组末尾元素的值 */
int BuildMaxHeap(int *heap, int len,int num,int count);/* 构建大顶堆 */

/* Function: 构建小顶堆 */
int BuildMaxHeap(int *heap, int len,int num,int count)
{
    int i;
    int temp;
    //交换后输出一下：
    printf("当前堆:");
    for (int j = 0; j < num ; ++j) {
        printf("%d ",heap[j]);
    }
    printf("\n");

    for (i = len/2-1; i >= 0; i--)
    {
        count++;
        //printf("准备和左子树比，当前比较次数：%d\n",count);
        if ((2*i+1) < len && heap[i] < heap[2*i+1])    /* 根节点小于左子树 */
        {
            // 交换操作

            temp = heap[i];
            heap[i] = heap[2*i+1];
            heap[2*i+1] = temp;

            /* 检查交换后的左子树是否满足大顶堆性质 如果不满足 则重新调整子树结构 */
            count++;
            if ((2*(2*i+1)+1 < len && heap[2*i+1] < heap[2*(2*i+1)+1]) || (2*(2*i+1)+2 < len && heap[2*i+1] < heap[2*(2*i+1)+2]))
            {
                BuildMaxHeap(heap, len,num,count);
            }
        }

        count++;
        //printf("准备和右子树比，当前比较次数：%d\n",count);

        if ((2*i+2) < len && heap[i] < heap[2*i+2])    /* 根节点小于右子树 */
        {

            temp = heap[i];
            heap[i] = heap[2*i+2];
            heap[2*i+2] = temp;

            /* 检查交换后的右子树是否满足小顶堆性质 如果不满足 则重新调整子树结构 */
            count++;
            if ((2*(2*i+2)+1 < len && heap[2*i+2] < heap[2*(2*i+2)+1]) || (2*(2*i+2)+2 < len && heap[2*i+2] < heap[2*(2*i+2)+2]))
            {
                BuildMaxHeap(heap, len,num,count);
            }
        }
    }
    return count;
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
    int result = 0;
    for (i = len; i > 0; i--)
    {
        result = BuildMaxHeap(a, i,num,result);

        Swap(a, i);
    }
    printf("总比较次数：%d\n",result);

//    for (i = 0; i < len; i++)
//    {
//        printf("%d ", a[i]);
//    }
    return result;
}

int main()
{

    FILE *fp =NULL;
    fp = fopen("./tets.txt","w+"); // 路径
    fprintf(fp, "...运行结果...\n");
    int len = 0;
    int total = 0;
    printf("请输入数组长度（小于 50）:");
    scanf("%d",&len);
    for (int i = 0; i < 10; i++) {
        int arr[MAXSIZE];


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

        int result = heapRank(arr,len,len);
        total += result;
        fprintf(fp, "排序后:");
        for (int j = 0; j < len; j++) {
            fprintf(fp, "%d ",arr[j]);
        }
        fprintf(fp, "\n本组比较次数：%d\n",result);
        fprintf(fp, "\n---------------------------------\n");
    }

    int average = total/10;
    fprintf(fp, "\n--------------结束-----------------\n");
    fprintf(fp, "\n平均比较次数：%d\n",average);


    fclose(fp);
    return 0;
}
