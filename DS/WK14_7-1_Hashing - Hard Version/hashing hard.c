#include<stdio.h>
#include<stdlib.h>
#define Vertex int
#define MaxSize 1000
#define INFINITY 99999
int N;
int hash[MaxSize];
int InDegree[MaxSize];
int visited[MaxSize] = {0};
int ans[MaxSize];
Vertex Q[MaxSize];//queue
int front = -1;
int rear = -1;

typedef struct VNode *PtrToVNode;
struct VNode{
	Vertex V;
	PtrToVNode Next;
};
 
typedef struct AdjVNode{
	PtrToVNode FirstEdge;
	int Data;
}*AdjList;
 
typedef struct GNode *LGraph;
struct GNode{
	AdjList G;
};

void TopSort(LGraph G,int ans[]);
Vertex FindMinV(LGraph G);
 
int main()
{
	int i,pos,j;
    Vertex V;
    
	scanf("%d",&N);
	
    //Create Graph
	LGraph G = (LGraph)malloc(sizeof(struct GNode));
	G->G = (AdjList)malloc(N*sizeof(struct AdjVNode));
	for(V=0;V<N;V++)
		G->G[V].FirstEdge = NULL;
	for(i=0;i<N;i++)
	{
		scanf("%d",&hash[i]);
		G->G[i].Data = hash[i];
	}
		
	for(i=0;i<N;i++)
	{
		if(hash[i] < 0)//an empty cell
		{
			InDegree[i] = INFINITY;
		    continue;
	    }
		pos = hash[i] % N;
		if(pos != i)//collision
		{
			for(j = i - 1;j != pos; )
			{
				if(j < 0)	j += N;//loop
                PtrToVNode NewNode = (PtrToVNode)malloc(sizeof(struct VNode));
                NewNode->V = i;
                NewNode->Next = G->G[j].FirstEdge;
                G->G[j].FirstEdge = NewNode;//insert edge from j to i
				InDegree[i]++;
				if(j == 0) j = N - 1;
				else j--;
			}
			InDegree[i]++;//j == pos
			PtrToVNode NewNode = (PtrToVNode)malloc(sizeof(struct VNode));
            NewNode->V = i;
            NewNode->Next = G->G[j].FirstEdge;
            G->G[j].FirstEdge = NewNode;//insert edge from j to i
		}
	}

	TopSort(G, ans);
	
	for(i=0;i<N;i++)
	{
		if(ans[i] < 0)
		{
			printf("\n");
		    break;//ending
	    }
		if(i == 0) printf("%d", hash[ans[i]]);
		else printf(" %d", hash[ans[i]]);
	}
	
	return 0;
}
 
void TopSort(LGraph G,int ans[])
{
	Vertex V;
	int i = 0;
	PtrToVNode P = (PtrToVNode)malloc(sizeof(struct VNode));

	V = FindMinV(G);//the minimum vertex of indegree 0
	Q[(++rear) % N] = V;//enqueue
	while(front != rear)//not empty
	{
		V = Q[(++front) % N];//dequeue
		visited[V] = 1;//visited
		ans[i++] = V;
		for(P = G->G[V].FirstEdge; P; P = P->Next)
			InDegree[P->V]--;
		V = FindMinV(G);
		if(V == -1) break;//failed
		else Q[(++rear) % N] = V;//enqueue
	}
    ans[i] = -1;//ending
}
 
Vertex FindMinV(LGraph G)
{
	Vertex V, MinV = -1;
	for(V=0;V<N;V++)
	{
		if(InDegree[V] == 0 && !visited[V])
		{
			if(MinV == -1) MinV = V;
			else if(G->G[V].Data <G->G[MinV].Data)
				MinV = V;
		}
	}
	return MinV;
}
