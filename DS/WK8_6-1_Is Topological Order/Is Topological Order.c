bool IsTopSeq( LGraph Graph, Vertex Seq[] )
{
	PtrToAdjVNode p;
	int Indegree[MaxVertexNum] = {0};
	int i, cv;
	
	for(i=0;i<Graph->Nv;i++)
	{
		p = Graph->G[i].FirstEdge;
		while(p)
		{
			Indegree[p->AdjV]++;
			p = p->Next;
		}
	}
	   
	for(i=0;i<Graph->Nv;i++)
	{
		cv = Seq[i] - 1;
		if(Indegree[cv] != 0)
		    return false;
		p = Graph->G[cv].FirstEdge;
		while(p)
		{
			if((--Indegree[p->AdjV]) < 0)
		        return false;
			p = p->Next;
		}
	}
	return true;
}
