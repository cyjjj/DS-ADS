#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define INFINITE 1000000

char planet[MAXN][4];
int nodenum = 0;//number of vertexes
int left[MAXN][MAXN] = {0};
int flow[MAXN][MAXN] = {0};
int pre[MAXN];//augmenting path

int get(char *s);
int BFS(int s, int d);
int MaxFlow(int s, int d);

int get(char *s)
{
    int i;
    for(i=0;i<nodenum;i++)
    {
        if(strcmp(s, planet[i]) == 0)
            return i;
    }
    strcpy(planet[nodenum], s);
    nodenum++;
    return (nodenum - 1);
}

int BFS(int s, int d)
{
	int queue[MAXN], v, i;
	int front = -1, rear = -1;
	for(i=0;i<MAXN;i++)
	    pre[i] = -1;
	queue[++rear] = s;//push source
	pre[s] = s;
	while(front != rear)//queue not empty
	{
		v = queue[++front];//pop
		for(i=0;i<nodenum;i++)
		{
			if(pre[i] == -1 && (flow[v][i] < left[v][i] || flow[i][v] > 0))
			{
				pre[i] = v;
				queue[++rear] = i;//push
				if(i == d) return 1;//arrive destination
			}
		}
	}
	return 0;
}

int MaxFlow(int s, int d)
{
	int maxflow = 0, i, v, min;
	while(BFS(s, d))
	{
		i = d;
		min = INFINITE;
		while(i != s)
		{
			v = pre[i];
			if (flow[v][i] < left[v][i])
			{
			    if(min > left[v][i] - flow[v][i])
                    min = left[v][i] - flow[v][i];
			}
			else if (flow[i][v] > 0)
			{
                if(min > flow[i][v])
                    min = flow[i][v];
            }
			i = v;
		}//find the min flow of the path
		
		i = d;
		while (i != s)
		{
		    v = pre[i];
			if (flow[v][i] < left[v][i])
			    flow[v][i] += min;
			else if (flow[i][v] > 0)
                flow[i][v] -= min;
			i = v;
		}
	}
	
	for(i=0;i<nodenum;i++)
	{
		if(i != s) maxflow += flow[s][i];
	}
	return maxflow;
}

int main()
{
	char source[4], dest[4];
	int planet_s, planet_d, n, i;
	int s, d, capacity;
	scanf("%s %s %d", source, dest, &n);
	planet_s = get(source);
	planet_d = get(dest);
	for(i=0;i<n;i++)
	{
		scanf("%s %s %d", source, dest, &capacity);
		s = get(source);
		d = get(dest);
		left[s][d] = capacity;
	}
	
	printf("%d\n", MaxFlow(planet_s, planet_d));
	return 0;
}
