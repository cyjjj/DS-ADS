#include <stdio.h>
#include <math.h>

#define MAXSIZE 1000

int a[MAXSIZE];//input
int BST[MAXSIZE];//array for binary search tree

void Sort(int *a, int n);
int GetLeftLength(int n);
void BuildCBST(int left, int right, int root);

void Sort(int *a, int n)
{
    int temp, i, j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int GetLeftLength(int n)
{
    int H = 0, X, L;
    int i = n;
    while(i)
    {
    	i /= 2;
    	H++;
	}
    X = n + 1 - pow(2, H-1);//number of nodes in the last line
    if(X > pow(2, H-2))
	    X = pow(2, H-2);
    L = pow(2, H-2) - 1 + X;
    
    return L;
}

void BuildCBST(int left, int right, int root)
{
	int n = right - left + 1;//number of nodes included
	if(n == 0) return;
	int L = GetLeftLength(n);
	BST[root] = a[left+L];//root of current tree
	BuildCBST(left, left+L-1, 2*root);//left tree
	BuildCBST(left+L+1, right, 2*root+1);//right tree
}

int main()
{
	int N,i;
	scanf("%d", &N);
	for(i=0;i<N;i++)
	    scanf("%d", &a[i]);
		  
	Sort(a, N);
	BuildCBST(0,N-1,1);
	
	printf("%d", BST[1]);
	for(i=2;i<=N;i++)
		printf(" %d",BST[i]);

	return 0;
}
