#include <stdio.h>

/*declaration*/
#define Maxsize 10000
int N;//total number of computers
int S[Maxsize];

int Find(int X);
void Union(int Root1, int Root2);

void Check(int a, int b);
void Input(int a, int b);
void Check_network(void);

/*function*/
int Find(int X)//path compression
{
	if(S[X] <= 0) return X;
	else return S[X] = Find(S[X]);
}

void Union(int Root1, int Root2)//union by height
{
	if(S[Root2] < S[Root1])
		S[Root1] = Root2;
	else 
	{
	    if(S[Root1] = S[Root2])
		    S[Root1]--;
		S[Root2] = Root1;
	}
}

void Input(int a, int b)
{
	int Root1, Root2;
	Root1 = Find(a);
	Root2 = Find(b);
	if(Root1 != Root2)
	    Union(Root1, Root2);
}

void Check(int a, int b)
{
	int Root1, Root2;
	Root1 = Find(a);
	Root2 = Find(b);
	if(Root1 == Root2) 
	  printf("yes\n");
	else printf("no\n");
}

void Check_network(void)
{
	int i, rootnum = 0;
	for(i=1;i<=N;i++)
	{
		if(S[i] <= 0) rootnum++;//count root
	}
	   
	if(rootnum == 1) printf("The network is connected.\n");
	else printf("There are %d components.\n", rootnum);
}

/*main function*/
int main()
{
	int i, a, b;
	char ch;
	scanf("%d", &N);
	for(i=1;i<=N;i++)
	    S[i] = -1;//initial
	    
	while((ch = getchar()) != 'S')
	{
		scanf("%d %d\n", &a, &b);
		switch (ch) {
            case 'C':
                Check(a, b);break;
            case 'I':
                Input(a, b);break;
        }
	}
	Check_network();
	return 0;
}
