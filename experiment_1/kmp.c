#include<stdio.h>
#include<string.h>

#define MAXSIZE 100

typedef char String[MAXSIZE + 1];/*第零位用于存储字符长度*/

// 获取失败函数组
int getNext(String T, int lenT, int *nextArr){
    int i = 1;
    int j = 0;

    nextArr[0] = 0;

    while (i < lenT){
        // T[i] 代表后缀中的每一项
        // T[j] 代表前缀中的每一项
        if (T[j] == T[i]){
            nextArr[i] = j + 1; // 安排数组值；
            i ++ ;
            j ++ ;
        }else{
            nextArr[i] = 0;
            if (j != 0 ) {
                j = nextArr[j-1];
                if (T[j] == T[i]){
                    nextArr[i] = j + 1;
                    j++;
                }
            } //j回溯,再次判断
            i++;
        }
    }



    return 0;
}

int kmp(String S,int lenS,String T, int lenT,int *nextArr){
    int s = 0;
    int t = 0;
    int result[lenS]; // 记录出现的坐标
    int count = 0;
    int flag = 0;

    while (s < lenS){

        if(S[s] == T[t]){
            flag ++;
            //printf("S[%d] = %c ",s,S[s]);
            //printf("T[%d] = %c \n",t,T[t]);
            s++;
            t++;
            //printf("flag = %d\n",flag);
        } else if(S[s] != T[t]){
            //printf("S[%d] = %c ",s,S[s]);
            //printf("T[%d] = %c \n",t,T[t]);
            flag = 0;
            if (t == 0){s++;}
            t = nextArr[t-1];
            //printf("flag = %d\n",flag);

        }

        // 成功匹配串
        if (flag == lenT){
            result[count] = s-lenT;
            //printf("success,loc:%d\n",result[count]);
            flag = 0;
            count ++;
        }
    }

    printf("---------final:-------------\n");
    printf("数目:%d\n",count);
    for (int i = 0; i < count; i++) {
        printf("出现的坐标:%d\n",result[i]);
    }
    return 0;
}


int main(){
    String T = "abc";
    int lenT = 3;

    String S = "123abxabcqqqabc789abc";
    int lenS = 21;

    int nextArr[lenT];
    getNext(T,lenT,nextArr);
    /*----------------------next arr------------------------*/
    // printf("nextarr:");
    // for (int i = 0; i < lenT; ++i) {
    //     printf("%d",nextArr[i]);
    // }
    // printf("\n");
    /*-------------------------------------------------*/

    kmp(S,lenS,T,lenT,nextArr);
    return 0;

}
