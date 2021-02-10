#include <stdio.h>
#include <stdio.h>
#define Max 100

struct Node{
	int weight;
    int fa;
	int child[Max];
	int childnum;
}node[Max];

int N, M, S;
int sum = 0;//sum of weight of path
char path[Max][Max] = {0};//paths found satisfying requirement
int pathnum = 0;//the number of paths found satisfying requirement

int cmp(const void *a ,const void *b);
void DFS(int id);

int main(){
    int i, j, id, num, k;
    scanf("%d %d %d", &N, &M, &S);
    for(i=0;i<N;i++)
	    scanf("%d", &node[i].weight);//initial tree
    node[0].fa = -1;//root node
    
    for(i=0;i<M;i++)//read in children
	{
        scanf("%d %d", &id, &num);
        node[id].childnum = num;
        for(j=0;j<num;j++)
		{
            scanf("%d", &k);
            node[id].child[j] = k;
            node[k].fa = id;
        }
    }
    
    DFS(0);//find paths whose weight is S
    qsort(path,pathnum,sizeof(path[0]),cmp);//sort paths found from max to min according to weight
    
    for(i=0;i<pathnum;i++)//output the paths found
	{
        printf("%d", path[i][0]);
        for(j=1;path[i][j];j++)
		    printf(" %d", path[i][j]);
		printf("\n");
    }
    return 0;
}

int cmp(const void *a ,const void *b)
{
	//sort paths from max to min
	char *ac, *bc;
	ac = (char *)a;
	bc = (char *)b;
	return strcmp(bc, ac);
}

void DFS(int id)
{
    int i, j = 0, v;
	int stack[Max];
	int top = -1;
	
    sum += node[id].weight;
    if(sum == S && node[id].childnum == 0)
    {
		//find a path successfully   
        v = id;
        while(v != -1)//not root node
		{
            stack[++top] = node[v].weight;//push
            v = node[v].fa;
        }
        while(top >= 0)
		    path[pathnum][j++] = stack[top--];//pop
        path[pathnum++][j] = '\0';
    }
    
    for(i=0;i<node[id].childnum;i++)//find all paths satisfying requirement
	{
        v = node[id].child[i];
        DFS(v);
    }    
    sum -= node[id].weight;
}
