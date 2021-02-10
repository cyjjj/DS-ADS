#include <stdio.h>
#include <stdlib.h>

/*data structure*/
typedef struct Node {
    int *Data;
    int Top;
    int MaxSize;
}*Stack;

int M, N, K;

/*declaration*/
Stack CreateStack(int MaxSize);
void Push(Stack S, int x);
void Pop(Stack S);
int StackCheck(int *a,Stack S);

/*function*/
Stack CreateStack(int MaxSize)
{
    Stack S = (Stack)malloc(sizeof(struct Node));
    S->Data = (int*)malloc(MaxSize*sizeof(int));
    S->Top = -1;
    S->MaxSize = MaxSize;
    return S;
}

void Push(Stack S, int x)
{
    if (S->Top == S->MaxSize) return;
    S->Data[++S->Top] = x;
}

void Pop(Stack S)
{
    if (S->Top < 0) return;
    S->Top--;
}

int StackCheck(int *a,Stack S)
{
    int i = 0;
    int num = 1;
    S->Top = -1;
    while(i != N){
        while((S->Top!=-1 && S->Top<M-1 && S->Data[S->Top]<a[i]) || S->Top<0){
        //ջ�ǿշ�����ջ��Ԫ��С�ڱȽ϶����ջΪ��
            Push(S,num);
            num++;
        }
        if(S->Top!=-1 && S->Data[S->Top]==a[i]){
        //ջ�ǿ���ջ��Ԫ�ص��ڱȽ϶���
            Pop(S);
            i++;
        }
        if((S->Top!=-1 && S->Data[S->Top]>a[i]) || (S->Top==M-1 && S->Data[S->Top]<a[i])){
        //ջ�ǿ���ջ��Ԫ�ش��ڱȽ϶����ջ����ջ��Ԫ����С�ڱȽ϶���
            return 0;
        }//�����в�����
    }
    return 1;
}

/*main function*/
int main()
{
    int i, j;
    extern int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    Stack S = CreateStack(M);
    int *a = (int*)malloc(N*sizeof(int));

    for(i=0;i<K;i++){
        for(j=0;j<N;j++)
            scanf("%d", &a[j]);
        if(StackCheck(a, S)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
