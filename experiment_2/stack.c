#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define MAXSIZE 10;
typedef int datatype;

struct stack
{
    datatype data[10];
    datatype top;
};

typedef struct stack Stack;

Stack s;
void init(){
    s.top = -1;
}

void Push(datatype element){
    s.top ++;
    s.data[s.top] = element;
}

datatype Pop(){
    datatype element;
    element = s.data[s.top];
    s.top--;
    return element;
}

int main(){
    Push(1);
    int temp = Pop();
    printf("temp:%d\n",temp);
}
