#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
int dfn[MaxVertices], low[MaxVertices];
int visit[MaxVertices] = {0};
int stack[MaxVertices];
int top = -1;
int sccn = 0;//counter

void Tarjan( Graph G, Vertex V);

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
	int i;
	for(i=0;i<G->NumOfVertices;i++)
	{
		dfn[i] = -1;
		low[i] = -1;
	}
	for(i=0;i<G->NumOfVertices;i++)
	{
		if(dfn[i] == -1) Tarjan(G, i);
	}
}

void Tarjan( Graph G, Vertex V)
{
	PtrToVNode p = G->Array[V];
	Vertex x, temp;
	sccn++;//counter
	dfn[V] = low[V] = sccn;
	stack[++top] = V;//push V
	visit[V] = 1;
	while(p)
	{
		x = p->Vert;
		if(dfn[x] == -1)
		{
			Tarjan(G, x);
			if(low[x] < low[V])
			    low[V] = low[x];
		}
		else if(visit[x])
		{
			if(low[x] < low[V])
			    low[V] = low[x];
		}
		p = p->Next;
	}
	if(dfn[V] == low[V])
	{
	    while(1)
		{
            temp = stack[top--];//pop
            printf("%d ", temp);
            visit[temp] = 0;
            if(temp == V) break;
        }
        printf("\n");
	}
}
