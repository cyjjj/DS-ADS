# 6-1 Evaluate Postfix Expression (10 分)

Write a program to evaluate a postfix expression. You only have to handle four kinds of operators: +, -, x, and /.

### Format of functions:

```c
ElementType EvalPostfix( char *expr );
```

where `expr` points to a string that stores the postfix expression. It is guaranteed that there is exactly one space between any two operators or operands. The function `EvalPostfix` is supposed to return the value of the expression. If it is not a legal postfix expression, `EvalPostfix` must return a special value `Infinity` which is defined by the judge program.

### Sample program of judge:

```c
#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */
```

### Sample Input 1:

```in
11 -2 5.5 * + 23 7 / -
```

### Sample Output 1:

```out
-3.285714
```

### Sample Input 2:

```in
11 -2 5.5 * + 23 0 / -
```

### Sample Output 2:

```out
ERROR
```

### Sample Input 3:

```
11 -2 5.5 * + 23 7 / - *
```

### Sample Output 3:

```out
ERROR
```