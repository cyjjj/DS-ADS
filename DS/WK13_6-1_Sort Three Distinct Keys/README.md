# 6-1 Sort Three Distinct Keys (5 分)

Suppose you have an array of N elements, containing three distinct keys, "true", "false", and "maybe". Given an *O*(*N*) algorithm to rearrange the list so that all "false" elements precede "maybe" elements, which in turn precede "true" elements. You may use only constant extra space.

### Format of functions:

```c
void MySort( ElementType A[], int N );
```

where `ElementType A[]` contains the `N` elements.

### Sample program of judge:

```c
#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void Read( ElementType A[], int N ); /* details omitted */

void MySort( ElementType A[], int N );

void PrintA( ElementType A[], int N )
{
    int i, k;

    k = i = 0;
    for ( ; i<N && A[i]==false; i++ );
    if ( i > k )
        printf("false in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==maybe; i++ );
    if ( i > k )
        printf("maybe in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==true; i++ );
    if ( i > k )
        printf("true in A[%d]-A[%d]\n", k, i-1);
    if ( i < N )
        printf("Wrong Answer\n");
}

int main()
{
    int N;
    ElementType *A;

    scanf("%d", &N);
    A = (ElementType *)malloc(N * sizeof(ElementType));
    Read( A, N );
    MySort( A, N );
    PrintA( A, N );
    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```in
6
2 2 0 1 0 0
```

### Sample Output:

```out
false in A[0]-A[0]
maybe in A[1]-A[2]
true in A[3]-A[5]
```