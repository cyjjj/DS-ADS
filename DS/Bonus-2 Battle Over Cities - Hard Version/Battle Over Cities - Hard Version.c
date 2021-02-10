#include <stdio.h>
#include <stdlib.h>
#define INFINITY 999999
#define MAXN 500

typedef struct HNode{
    int city1;
	int city2;
	int cost;
	int status;
}*Highway;

int N;//the total number of cities
int M;//the number of highways
int S[MAXN];//Union-Find

int cost[MAXN] = {0};//the effort needed when city_i is conquered
int maxcost = 0;//the maximum effort to rebuild the connection

int ans[MAXN] = {0};//cities we must protest most
int count = 0;//the number of cities we must protest most

int cmp(const void *a,const void *b);
int Find(int X);
void Union(int Root1, int Root2);

int main()
{
    int i, j, k;
	scanf("%d %d", &N, &M);
    Highway H = (Highway)malloc(M*sizeof(struct HNode));
    for(i=0;i<M;i++)
        scanf("%d %d %d %d", &H[i].city1, &H[i].city2, &H[i].cost, &H[i].status);
    qsort(H,M,sizeof(struct HNode),cmp);//sort H in increasing order of cost,in use before destroyed
     
    int root1, root2;
    for(i=1;i<=N;i++)//if city_i is conquered
    {
        for(j=1;j<=N;j++)
	        S[j] = -1;//initial
	    
	    int num = 0;
        for(j=0;j<M;j++)
        {
            if(H[j].city1 == i || H[j].city2 == i)//city at either end is conquered
                continue;
            root1 = Find(H[j].city1);
            root2 = Find(H[j].city2);
			if(root1 != root2)
            {
            	Union(root1, root2);
            	num++;
            	if(!H[j].status)//the highway is detroyed
            	    cost[i] += H[j].cost;//update the cost of city_i
			    if(num == N - 2) break;
			}
        }
        
        if(num < N - 2)//cannot reconnect the cities
			cost[i] = INFINITY;
			
        if(cost[i] > maxcost)//update maxcost
            maxcost = cost[i];
    }

    if(maxcost == 0)//there is no need to repair any highway at all
        printf("0");
    else
    {
    	for(i=1;i<=N;i++)
    	{
    		if(cost[i] == maxcost)//city we must protest most
                ans[count++] = i;
		}
		printf("%d", ans[0]);
		for(i=1;i<count;i++)
		    printf(" %d", ans[i]);
	}

    return 0;

}

int cmp(const void *a,const void *b)
{
	//highway in use before highway destroyed
	//in increasing order of the cost
    Highway A = (Highway)a;
	Highway B = (Highway)b;
    if(A->status != B->status)
        return B->status - A->status;
    else
        return A->cost - B->cost;
}

int Find(int X)
{
	if(S[X] <= 0) return X;
	else return S[X] = Find(S[X]);//path compression
}

void Union(int Root1, int Root2)//union by height
{
	if(S[Root2] < S[Root1])
		S[Root1] = Root2;
	else 
	{
	    if(S[Root1] = S[Root2])
		    S[Root1]--;
		S[Root2] = Root1;
	}
}
