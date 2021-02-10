int FindMin( MGraph Graph, int dist[], int known[]);//find smallest unknown distance vertex

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
	Vertex V, W;
	int known[MaxVertexNum] = {0};//false
	int i;
	WeightType newdist;
	//initial
	for(i=0;i<Graph->Nv;i++)
	{
		dist[i] = INFINITY;
		path[i] = -1;
	}
	dist[S] = 0;
	
	//dijkstra
	for( ; ; )
	{
		V = FindMin(Graph, dist, known);
		if(V == -1)//Not a vertex
		    break;
		known[V] = 1;//true
		for(W=0;W<Graph->Nv;W++)//each W adjacent to V
		{
			if(Graph->G[V][W] > 0)
			{
				newdist = dist[V] + Graph->G[V][W];
				if(newdist < dist[W])
				{
					dist[W] = newdist;
                    path[W] = V;
				}
			}
		}
	}
	
	for(i=0;i<Graph->Nv;i++)
    {
        if(dist[i] == INFINITY)//vertex left
        {
            dist[i] = -1;
            path[i] = -1;
        }
    }
}

int FindMin( MGraph Graph, int dist[], int known[])
{
	int i, min = 0;
    while(known[min] || dist[min] == INFINITY)
        min++;
	for(i=min+1;i<Graph->Nv;i++)
	{
		if(dist[i] < dist[min] && !known[i])
		{
			min = i;
			return min;
		}
	}
	if(min >= Graph->Nv) return -1;
	else return min;
}
