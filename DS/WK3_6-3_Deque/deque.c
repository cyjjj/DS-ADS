Deque CreateDeque()
{
    PtrToNode p = (PtrToNode)malloc(sizeof(struct Node));
    p->Next = NULL;
    p->Last = NULL;
    Deque D = (Deque)malloc(sizeof(struct DequeRecord));
    D->Front = p;
    D->Rear = p;
    return D;
}

int Push( ElementType X, Deque D )
{
    PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
    if(!temp) return 0;
    temp->Element = X;
    temp->Last = D->Front;
    temp->Next = D->Front->Next;
    if(D->Front->Next == NULL)//空
        D->Rear = temp;
    else D->Front->Next->Last = temp;
    D->Front->Next = temp; 
    return 1;
}

ElementType Pop( Deque D )
{
    if(D->Front->Next == NULL) return ERROR;//空
    PtrToNode temp = D->Front->Next;
    ElementType popval = temp->Element;
    if(temp == D->Rear){//一个元素
        D->Front->Next = NULL;
        D->Rear = D->Front;
    } else {
        D->Front->Next = D->Front->Next->Next;
        D->Front->Next->Last = D->Front;
    }
    free(temp);
    return popval; 
}

int Inject( ElementType X, Deque D )
{
    PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
    if(!temp) return 0;
    temp->Element = X;
    temp->Next = NULL;
    if(D->Front->Next == NULL){//空
        D->Front->Next = temp;
        temp->Last = D->Front;
        D->Rear = temp;
    } else {
        D->Rear->Next = temp;
        temp->Last = D->Rear;
        D->Rear = temp;
    }
    return 1;
}

ElementType Eject( Deque D )
{
    if(D->Front->Next == NULL) return ERROR;//空
    ElementType Ejectval = D->Rear->Element;
    if(D->Front->Next == D->Rear){//一个元素
        free(D->Rear);
        D->Front->Next = NULL;
		D->Rear = D->Front;
	}else {
		D->Rear = D->Rear->Last;
		free(D->Rear->Next);
		D->Rear->Next = NULL;
	}
    return Ejectval;
}
