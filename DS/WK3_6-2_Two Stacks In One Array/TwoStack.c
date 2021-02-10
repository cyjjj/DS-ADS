Stack Ring( Stack S, int Stacknum )
{
    switch(Stacknum){
        case 1: 
            if(S->Top1 < 0) S->Top1 = S->Capacity;
            else if(S->Top1 > S->Capacity) S->Top1 = 0;
            break;
        case 2:
            if(S->Top2 < 0) S-> Top2 = S->Capacity;
            else if(S->Top2 > S->Capacity) S->Top2 = 0;
            break;
    }
    return S;
}
Stack CreateStack( int MaxElements )
{
    Stack s = (Stack)malloc(sizeof(struct StackRecord));
    int *a = (int *)malloc((MaxElements+1)*sizeof(int));
    s->Capacity = MaxElements;
    s->Top1 = MaxElements-1;
    s->Top2 = MaxElements;
    s->Array = a;
    return s;
}
int IsEmpty( Stack S, int Stacknum )
{
    switch(Stacknum){
        case 1:
            if(S->Top1 == S->Capacity-1) return 1;
            break;
        case 2:
            if(S->Top2 == S->Capacity) return 1;
            break;
    }
    return 0;
}

int IsFull( Stack S )
{
    if(S->Top1 == S->Top2)
        return 1;
    return 0;
}

int Push( ElementType X, Stack S, int Stacknum )
{
    if(IsFull(S)) return 0;
    switch(Stacknum){
        case 1: 
            S->Array[S->Top1--] = X;
            S = Ring(S, 1);
            break;
        case 2:
            S->Array[S->Top2++] = X;
            S = Ring(S, 2);
            break;
    }
    return 1;
}

ElementType Top_Pop( Stack S, int Stacknum )
{
    if(IsEmpty(S,Stacknum)) return ERROR;

    switch(Stacknum){
        case 1:
            S->Top1++;
            S = Ring(S, 1);
            return (S->Array[S->Top1]);
        case 2:
            S->Top2--;
            S = Ring(S, 2);
            return (S->Array[S->Top2]);
    }
}

