# 6-3 Deque (10 分)

A "deque" is a data structure consisting of a list of items, on which the following operations are possible:

- Push(X,D): Insert item X on the front end of deque D.
- Pop(D): Remove the front item from deque D and return it.
- Inject(X,D): Insert item X on the rear end of deque D.
- Eject(D): Remove the rear item from deque D and return it. Write routines to support the deque that take O(1) time per operation.

### Format of functions:

```c
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );
```

where `Deque` is defined as the following:

```c
typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
```

Here the deque is implemented by a doubly linked list with a header. `Front` and `Rear` point to the two ends of the deque respectively. `Front` always points to the header. The deque is empty when `Front` and `Rear` both point to the same dummy header. Note: `Push` and `Inject` are supposed to return 1 if the operations can be done successfully, or 0 if fail. If the deque is empty, `Pop` and `Eject` must return `ERROR` which is defined by the judge program.

### Sample program of judge:

```c
#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */
```

### Sample Input:

```in
Pop
Inject 1
Pop
Eject
Push 1
Push 2
Eject
Inject 3
End
```

### Sample Output:

```out
Deque is Empty!
Deque is Empty!
Inside Deque: 2 3
```