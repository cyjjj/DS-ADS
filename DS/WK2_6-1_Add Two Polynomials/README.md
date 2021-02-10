# 6-1 Add Two Polynomials (8 分)

Write a function to add two polynomials. Do not destroy the input. Use a linked list implementation with a dummy head node. Note: The zero polynomial is represented by an empty list with only the dummy head node.

### Format of functions:

```c
Polynomial Add( Polynomial a, Polynomial b );
```

where `Polynomial` is defined as the following:

```c
typedef struct Node *PtrToNode;
struct Node {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;
/* Nodes are sorted in decreasing order of exponents.*/  
```

The function `Add` is supposed to return a polynomial which is the sum of `a` and `b`.

### Sample program of judge:

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```in
4
3 4 -5 2 6 1 -2 0
3
5 20 -7 4 3 1
```

### Sample Output:

```out
5 20 -4 4 -5 2 9 1 -2 0
```