Polynomial Add(Polynomial a, Polynomial b)
{
	Polynomial head, r;
	head = (Polynomial)malloc(sizeof(struct Node));
	head->Next = NULL;
	r = head;

	while (a && b)
	{
		if (a->Exponent > b->Exponent)
		{
			r->Next = a;
			r = a;
			a = a->Next;
		}
		else if (a->Exponent < b->Exponent)
		{
			r->Next = b;
			r = b;
			b = b->Next;
		}
		else
		{ //a->Exponent=b->Exponent
			if (a->Coefficient + b->Coefficient)
			{
				Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
		        temp->Next = NULL;
				temp->Exponent = b->Exponent;
				temp->Coefficient = a->Coefficient + b->Coefficient;
				r->Next = temp;
				r = temp;
			}
			a = a->Next;
			b = b->Next;
		}
	}
	while (a)
	{
		r->Next = a;
		r = a;
		a = a->Next;
	}
	while (b)
	{
		r->Next = b;
		r = b;
		b = b->Next;
	}
	r->Next = NULL;

	return head;
}
