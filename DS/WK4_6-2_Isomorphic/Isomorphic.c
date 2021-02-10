int Isomorphic(Tree T1, Tree T2)
{
    if((T1 == NULL) && (T2 == NULL)) //都为空
 	    return 1;
 	else if(((T1 == NULL)&&(T2 != NULL)) || ((T1 != NULL)&&(T2 == NULL)))  //其中之一为空
	    return 0;
	else if(T1->Element != T2->Element) //都非空
	    return 0;
    return((Isomorphic(T1->Left, T2->Left)&&Isomorphic(T1->Right, T2->Right)) 
        || (Isomorphic(T1->Left, T2->Right)&&Isomorphic(T1->Right, T2->Left)));
}
