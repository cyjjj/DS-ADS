#include <stdio.h>
#include <stdlib.h>

/*data structure*/
#define MAXN 35
typedef struct node* tree;
struct node
{
    int data;
    tree left;
    tree right;
};

int front=0,rear=0;//��ʼ����ͷ�Ͷ�βָ��
tree Queue[MAXN];

int v[MAXN] = {0};//�������
int post[MAXN] = {0}, in[MAXN] = {0};
int sum[MAXN] = {0};//sum[]��ÿ��Ľڵ���

/*declaration*/
tree build(int postl, int postr, int inl, int inr);//���������
void bfs(tree t, int n);//�������
void dfs(tree t, int depth);//��ÿ��ڵ���

void EnQueue(tree node);//���
tree DeQueue(void);//����
tree Qfront(void);//����
int isempty(void);//����Ϊ��

/*main function*/
int main()
{
    int N, i, j;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &in[i]);
    for (i = 0; i < N; i++)
        scanf("%d", &post[i]);
    
    tree t = NULL;
    t = build(0, N-1, 0, N-1);
    bfs(t, N);
    dfs(t, 0);

    printf("%d", v[0]);
    int depth = 0;//�ӵ�0�㿪ʼ
    for(i=1; v[i]; i+=sum[depth])
    {
        depth++;
        if(depth%2 == 1)
        {
            for(j=0; j<sum[depth]; j++)
                printf(" %d", v[i+j]);
        }
        else
        {
            for(j=sum[depth]-1; j>=0; j--)//�������
                printf(" %d", v[i+j]);
        }
    }
    return 0;
}

/*function*/
tree build(int postl, int postr, int inl, int inr)
{
    if(postl > postr) return NULL;
    int i = inl;
    while(i<inr && post[postr]!=in[i]) i++;
    int sum = i-inl;
    tree t = (tree)malloc(sizeof(struct node));
    t->data = post[postr];
    t->left = build(postl, postl+sum-1, inl, i-1);
    t->right = build(postl+sum, postr-1, i+1, inr);
    return t;
}

void bfs(tree t, int n)
{
	int i = 0; 
    EnQueue(t);
    v[i++] = t->data;
    while(!isempty())
    {
        tree x = Qfront();
        if(x->left)
        {
            EnQueue(x->left);
            v[i++] = x->left->data;
        }
        if(x->right)
        {
            EnQueue(x->right);
            v[i++] = x->right->data;
        }
        DeQueue();
    }
}

void dfs(tree t, int depth)
{
    if(!t) return;
    sum[depth]++;
    dfs(t->left, depth+1);
    dfs(t->right, depth+1);
}

void EnQueue(tree node){
    Queue[rear++]=node;
}

tree DeQueue(void)
{
    return Queue[front++];
}

tree Qfront(void)
{
    return Queue[front];
}

int isempty(void)
{
    return (front == rear);
}

