#include <iostream>
#include <vector>
#include <cmath>
#define MAXN 100
using namespace std;

int N, M, L;//number of players,wolves,liers
int id[MAXN], visit[MAXN];
vector<int> v, res;//statement, result 

void dfs(vector<int> res);//dfs for the result

int main() {
	int i;
	cin >> N >> M >> L;	
	v.resize(N+1);
	fill(id + 1, id + N + 1, 1);//initialized as 1
	for(i = 1; i <= N; i++)
		cin >> v[i];
	dfs(res);
	cout << "No Solution";//not find
	return 0;
}

void dfs(vector<int> res) {
	int i;
	int liernum = 0;
	int wolfliernum = 0; 
	if(res.size() == M) //find M werewolves
	{
		for (i = 1; i <= N; i++) 
		{
			if(id[abs(v[i])] * v[i] < 0) //lie
			{
				liernum++;
				if(id[i] == -1) wolfliernum++;
			}
		}
		if (liernum == L && wolfliernum > 0 && wolfliernum < M) 
		{
		    //print out the result
			cout << res[0];
			for(i = 1; i < res.size(); i++)
				cout << " " << res[i];
			exit(0); 
		}
		return;
	}
	for (i = N; i > 0; i--) {
		if(res.size() + i < M)
		    break;//cannot find M werewolves
		if(!visit[i]) 
		{
			visit[i] = 1;
			id[i] = -1;//werewolf
			res.push_back(i);
			dfs(res);
			res.pop_back();
			id[i] = 1;
			visit[i] = 0;
		}
	}
}
