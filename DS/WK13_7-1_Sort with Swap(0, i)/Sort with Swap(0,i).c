#include <stdio.h>
#define MAXN 100000
//table sort, ring sort
int list[MAXN];//number to be sorted
int table[MAXN];//position of the number in list[]
int flag[MAXN] = {0};//already visited or not

int main()
{
	int n, i, temp, result = 0;
	int S = 0;//number of rings of one element
	int K = 0;//number of rings of more than one element
	//initial
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		scanf("%d", &list[i]);
		table[list[i]] = i;
	}
	//count rings
	for(i=0;i<n;i++)
	{
		if(flag[i]) continue;//already visited
		if(table[i] == i)
		{
			S++;//ring of one element
			flag[i] = 1;
		}
		else//ring of more than one element
		{
			temp = table[i];
			flag[i] = 1;
			while(table[temp] != i)
			{
				flag[temp] = 1;
				temp = table[temp];
			}
			flag[temp] = 1;
			K++;
		}
	}
	//calculate the result
	if(list[0] == 0) result = n - S + K;
	else result = n - S + K - 2;
	printf("%d", result);
	return 0;
}
