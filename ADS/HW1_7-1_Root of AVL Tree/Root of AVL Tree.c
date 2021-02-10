#include <stdio.h>
#include <stdlib.h>
typedef struct Treenode *Tree;
struct Treenode
{
	int v;
	Tree left;
	Tree right;
};

Tree Insert( Tree T, int x );
int Height( Tree T );
Tree LLrotation( Tree T );
Tree RRrotation( Tree T );
Tree LRrotation( Tree T );
Tree RLrotation( Tree T );

int main()
{
	int N, x, i;
	scanf("%d", &N);//number of nodes
	Tree T = NULL;//empty tree
	for(i = 0; i < N; i++) 
	{
		scanf("%d", &x);
		T = Insert(T, x);//build AVL tree
	}
	printf("%d\n", T->v);//output the root node
	return 0;
}

Tree Insert( Tree T, int x )
{
	if (!T)//empty tree
	{
		T = (Tree)malloc(sizeof(struct Treenode));
		T->v = x;
		T->left = T->right = NULL;//new node
	} 
	else if (x < T->v)//left subtree
	{
		T->left = Insert(T->left, x);
		if (Height(T->left) - Height(T->right) == 2)//need rotation
		{
			if (x < T->left->v)
				T = LLrotation(T);//LL Single Rotation
			else
				T = LRrotation(T);//LR Double Rotation
		}
	}
	else if (x > T->v)//right subtree
	{
		T->right = Insert(T->right, x);
		if (Height(T->right) - Height(T->left) == 2)//need rotation
		{
			if (x > T->right->v)
				T = RRrotation(T);//RR Single Rotation
			else
				T = RLrotation(T);//RL Double Rotation
		}
	}
	
	return T;
}

int Height( Tree T )
{
	int HL, HR, H;
	if(!T) return 0;
	else
	{
		HL = Height(T->left);
		HR = Height(T->right);
		if(HL > HR) H = HL + 1;
		else H = HR + 1; 
		return H;
	}
}

Tree LLrotation(Tree T)//LL Single Rotation
{
	Tree A = T, B = T->left;
	Tree BR = B->right;
	A->left = BR;
	B->right = A;
	return B;
}

Tree RRrotation(Tree T)//RR Single Rotation
{
	Tree A = T, B = T->right;
	Tree BL = B->left;
	A->right = BL;
	B->left = A;
	return B;
}

Tree LRrotation(Tree T)
{
	T->left = RRrotation(T->left);//RR Single Rotation
	return LLrotation(T);//LL Single Rotation 
}

Tree RLrotation(Tree T)
{
	T->right = LLrotation(T->right);//LL Single Rotation
	return RRrotation(T);//RR Single Rotation 
}
