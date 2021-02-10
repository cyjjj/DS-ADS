#include <stdio.h>
#include <stdlib.h>
#define N 7
typedef struct Node Tree;
struct Node
{
    int x;
    Tree *left;
    Tree *right;
};
int t; //记录数组pre或post的位置，t对应的都为root
Tree *tree_insert(Tree *T, int x);
void tree_print(Tree *T);
//返回a[p,r]中等于x的下标
int find(int a[], int x, int p, int r);
//已知前序，中序遍历建树，p为数组mid最左下标，r为数组mid最右下标
Tree *build1(Tree *T, int pre[], int mid[], int p, int r);
//已知中序，后序遍历建树，p为数组mid最左下标，r为数组mid最右下标
Tree *build2(Tree *T, int mid[], int post[], int p, int r);

int main(int argc, char *argv[])
{
    int i;
    Tree *T = NULL;
    int a[N] = {6, 2, 8, 1, 4, 3, 5};
    int pre[N] = {6, 2, 1, 4, 3, 5, 8};
    int mid[N] = {1, 2, 3, 4, 5, 6, 8};
    int post[N] = {1, 3, 5, 4, 2, 8, 6};
    //for(i=0;i<7;++i)
    //  T=tree_insert(T,a[i]);
    //t=0;
    //T=build1(T,pre,mid,0,6);
    t = N - 1;
    T = build2(T, mid, post, 0, 6);
    tree_print(T);
    return 0;
}
Tree *build2(Tree *T, int mid[], int post[], int p, int r)
{
    int index;
    if (p == r)
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->x = post[t--];
        T->left = NULL;
        T->right = NULL;
        return T;
    }
    index = find(mid, post[t], p, r);
    T = (Tree *)malloc(sizeof(Tree));
    T->x = post[t--];
    T->right = build2(T->right, mid, post, index + 1, r);
    T->left = build2(T->left, mid, post, p, index - 1);
    return T;
}
Tree *build1(Tree *T, int pre[], int mid[], int p, int r)
{
    int index;
    if (p == r)
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->x = pre[t++];
        T->left = NULL;
        T->right = NULL;
        return T;
    }
    index = find(mid, pre[t], p, r);
    T = (Tree *)malloc(sizeof(Tree));
    T->x = pre[t++];
    T->left = build1(T->left, pre, mid, p, index - 1);
    T->right = build1(T->right, pre, mid, index + 1, r);
    return T;
}
int find(int a[], int x, int p, int r)
{
    int i = 0;
    for (i = 0; i < N; ++i)
        if (x == a[i])
            return i;
}
Tree *tree_insert(Tree *T, int x)
{
    if (T == NULL)
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->x = x;
        T->left = NULL;
        T->right = NULL;
        return T;
    }
    else if (x < T->x)
        T->left = tree_insert(T->left, x);
    else
        T->right = tree_insert(T->right, x);
    return T;
}
void tree_print(Tree *T)
{
    if (T == NULL)
        return;
    //printf("%d ",T->x);
    tree_print(T->left);
    printf("%d ", T->x);
    tree_print(T->right);
    //printf("%d ",T->x);
}