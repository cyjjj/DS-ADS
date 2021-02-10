#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*data structure*/
#define ElementType int
#define MaxN 31
#define LEFT 0
#define RIGHT 1
#define ERROR -1

ElementType postorder[MaxN];
static int num = 0;

typedef struct SNode *Stack;
struct SNode{
	ElementType *data;
	int top;
	int MaxSize; 
};

struct TreeNode{
	int left;
	int right;
}node[MaxN];

/*declaration*/
Stack CreateStack(int MaxSize); 
void Push(Stack S, ElementType X);
ElementType Pop(Stack S);
ElementType Read(Stack S, ElementType N);
void PostOrderTraversal(int r);

/*main function*/
int main()
{
    int N;
	int root;
    Stack s = CreateStack(MaxN);
	int i;
	for(i=0;i<MaxN;i++){
		node[i].left = -1;
		node[i].right = -1;
	}
	    

    scanf("%d", &N);
    root = Read(s, N);
	PostOrderTraversal(root);
	int j = 1;
	printf("%d", postorder[0]);
	while(postorder[j]){
		printf(" %d", postorder[j]);
		j++;
	}
	return 0;
}

/*function*/
ElementType Read(Stack S, ElementType N)
{
	int i, x;
	int root = -1,fa;
	int child = LEFT;
    char operation[5];
	for(i=0; i<2*N; i++){
		scanf("%s", operation);
		if (strcmp(operation, "Push") == 0){//push
            scanf("%d", &x);
			if(root == -1){
				root = x;  //first node must be the root 
			}else{
				if(!child){//LEFT
					node[fa].left = x;
				}else{//RIGHT
					node[fa].right = x;
				}
			} 
			fa = x;
			child = LEFT;
			Push(S,x);
		} else {//pop
			fa = Pop(S);
			child = RIGHT;
		}
	}
	return root;
}

void PostOrderTraversal(int r)
{
	if(r != -1){
		PostOrderTraversal(node[r].left);
		PostOrderTraversal(node[r].right);
		postorder[num++] = r;
	}
}


Stack CreateStack(int MaxSize)
{
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->data = (ElementType*)malloc(MaxSize*sizeof(ElementType));
    S->top = -1;
    S->MaxSize = MaxSize;
    
    return S;
}
 

void Push(Stack S,ElementType X)
{
	if(S->top == S->MaxSize - 1)
	    return; 
	else
	    S->data[++S->top] = X;
 } 

ElementType Pop(Stack S)
{
	if(S->top == -1)
		return ERROR;
	else
		return (S->data[S->top--]);
}