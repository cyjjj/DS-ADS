#include <stdio.h>
#include <stdlib.h>

/* data structure */
#define ElementType int

typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

/* declaration */
SearchTree MakeEmpty(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
int IsSameBST(SearchTree T1, SearchTree T2);

/* main function */
int main()
{
    int N, L, i, j, temp, flag;
    SearchTree S = NULL, T = NULL;
    while (1)
    {
        scanf("%d", &N);//total number of integers in an insertion sequence
        if(N == 0) break;
        scanf("%d", &L);//number of sequences to be tested

        for(i=0;i<N;i++)
        {
            scanf("%d", &temp);
            S = Insert(temp, S);//initially inserted numbers
        }

        for(i=0;i<L;i++)
        {
            T = MakeEmpty(T);
            for(j=0;j<N;j++)
            {
                scanf("%d", &temp);
                T = Insert(temp, T);//a sequence to be checked
            }

            flag = IsSameBST(S, T);
            if(flag) printf("Yes\n");
            else printf("No\n");
        }
        S = MakeEmpty(S);
    }
    return 0;   
}

/* function */
SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL)
    { /* Create and return a one-node tree */
        T = malloc(sizeof(struct TreeNode));
        if (T == NULL)
            printf("Out of space!!!");
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    } /* End creating a one-node tree */
    /* If there is a tree */
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* Else X is in the tree already; we'll do nothing */
    return T;
}

int IsSameBST(SearchTree T1, SearchTree T2)
{
    if((T1 == NULL) && (T2 == NULL))//both NULL
 	    return 1;
 	else if(((T1 == NULL)&&(T2 != NULL)) || ((T1 != NULL)&&(T2 == NULL)))//one of the two NULL
	    return 0;
	else if(T1->Element != T2->Element) //both not NULL
	    return 0;
    return((IsSameBST(T1->Left, T2->Left) && IsSameBST(T1->Right, T2->Right)));
}