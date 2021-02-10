#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
int init[MAXN];
int aim[MAXN];

int Judge (int *init, int *aim, int n);//1--Insertion Sort,0--Heap Sort
void Insertion (int *aim, int n);
void HeapSort (int *aim, int n);

int main()
{
	int n, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	    scanf("%d", &init[i]);
	for(i = 0; i < n; i++)
	    scanf("%d", &aim[i]);
	
	if(Judge(init, aim, n))
	{
		
		printf("Insertion Sort\n");
		Insertion(aim, n);
	}   
	else
	{
		printf("Heap Sort\n");
		HeapSort(aim, n);
	}
	
	printf("%d", aim[0]);
	for(i = 1; i < n; i++)
	    printf(" %d", aim[i]); 
	return 0;
}

int Judge (int *init, int *aim, int n)
{
	int i = 1;
	while(aim[i-1] <= aim[i]) i++;
	while(i<n)
	{
		if(aim[i] != init[i]) return 0;//not insertion sort
		i++;
	}
	return 1;//insertion sort
}

void Insertion (int *aim, int n)
{
	int i = 1, temp;
	while(i<n && aim[i-1] <= aim[i]) i++;
	if(i == n) return;
	temp = aim[i];
	while(aim[i-1] > temp)
	{
		aim[i] = aim[i-1];
		i--;
	}
	aim[i] = temp;
}

void HeapSort (int *aim, int n)
{
	int i = n - 1, temp, j, p;    
	while(i >= 0 && aim[i] >= aim[0]) i--;
	temp = aim[i];
	aim[i] = aim[0];
	i--;
	for(j = 0; 2*j+1 <= i; j = p)
	{
		p = 2 * j + 1;
		if(p + 1 <= i && aim[p+1] > aim[p]) p++;
		if(aim[p] <= temp) break;
		else aim[j] = aim[p];
	}
	aim[j] = temp;
}
