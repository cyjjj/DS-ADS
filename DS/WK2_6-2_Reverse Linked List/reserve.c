List Reverse(List L)
{
    if(L->Next == NULL || L->Next->Next == NULL)
        return L;
    List p = L->Next; //Already reserved
    List q = p->Next; //Not resserved yet
    p->Next = NULL;

    while (q)
    {
        List t = q->Next;
        q->Next = p;
        p = q;
        q = t;
    }
    L->Next = p;

    return L;
}
