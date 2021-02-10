#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
	int head = 0;//first node of comparision
	int left, right;
	int i = 0;
	while(head < N)
	{
		left = head;//first node of left part
		right = head + length;//first node of right part
		while(left < N && right <N)
		{
			if(left >= head + length || right >= head + 2 * length)
			    break;
			sorted[i++] = (list[left] < list[right]) ? list[left++] : list[right++];
		}
		while(left < head + length && left < N)//left nodes of the left part
		{
			sorted[i++] = list[left++];
		}
		while(right < head + 2 * length && right < N)//left nodes of the right part
		{
			sorted[i++] = list[right++];
		}
		head += 2 * length;
    }
}
