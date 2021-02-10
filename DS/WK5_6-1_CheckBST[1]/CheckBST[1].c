#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode{
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST ( BinTree T, int K );

int main()
{
    BinTree T;
    int K, out;

    T = BuildTree();
    scanf("%d", &K);
    out = CheckBST(T, K);
    if ( out < 0 )
        printf("No.  Height = %d\n", -out);
    else
        printf("Yes.  Key = %d\n", out);

    return 0;
}
/* 你的代码将被嵌在这里 *

/* 求出高度，用堆栈实现中缀遍历,然后检查是否为递增 */
#define MAX_SIZE 100
BinTree Q[MAX_SIZE];//队列
int front = 0, rear = 0;

int in[MAX_SIZE] = {0};//中序遍历结果
int i = 0;

void inorder(BinTree T);//中序遍历
void EnQueue(BinTree node);//队列入队
BinTree DeQueue(void);//队列出队
BinTree Qfront(void);//队列队首元素

int CheckBST ( BinTree T, int K )
{
    //顺序队列实现迭代求树高
    int last = 1, level = 0;
    if (!T) level = 0;
    EnQueue(T);//入队
    BinTree p;
    while (front < rear)  {
        p = DeQueue();//出队
        if (p->Left)
            EnQueue(p->Left);//入队
        if (p->Right)
            EnQueue(p->Right);//入队
        if (front == last){
            level++;
            last = rear;
        }
    }

    //实现中序遍历然后检查是否为递增
    inorder(T);
    int j;
    for(j=1;in[j];j++){
        if(in[j] <= in[j-1])
            return -level;//not BST
    }
    return in[j-K];//BST
}

void inorder(BinTree T)
{
    if(!T) return;
    inorder(T->Left);
    in[i++] = T->Key;
    inorder(T->Right);
}

void EnQueue(BinTree node){
    Q[rear++] = node;
}

BinTree DeQueue(void)
{
    return Q[front++];
}

BinTree Qfront(void)
{
    return Q[front];
}
