#include<bits/stdc++.h>
using namespace std;
vector<int> v,vr,vl,vi;
int n,m,k;
void dfs(int n,int ln,int wn,int un)
{
	if(ln>k||wn>m||wn+un<m)
	return;
	else if(n<k-ln)
	return;
	else if(n<1)
	{
		if(ln==k&&wn<=m&&wn+un>=m)
		{
			int first=0;
			bool flag=false;
			int fl=0;
			for(int i=v.size()-1;i>0&&!flag;--i)
			{
				if(vl[i]==-1&&vi[i]==-1)
				flag=true;
			}
			if(m-wn)
			for(int i=v.size()-1;i>0&&!flag;--i)
			{
				if(vl[i]==-1&&vi[i]==0)
				{
					fl=i;
					vi[i]=-1;
					wn++;
					un--;
					flag=true;
				}
			}
			if(flag)
			{
				vector<int> vrr;
				for(int i=v.size()-1;i>0&&vrr.size()<m;--i)
				{
					if(vi[i]==-1)
					vrr.emplace_back(i); //就地构造对象放入vector而不用调用拷贝构造 
				}
				for(int i=v.size()-1;i>0&&vrr.size()<m;--i)
				{
					if(vi[i]==0)
					vrr.emplace_back(i);
				}
				sort(vrr.begin(),vrr.end(),greater<int>());
				if(vr.empty())
				vr=vrr;
				else
				for(int i=0;i<vrr.size();++i)
				{
					if(vrr[i]>vr[i])
					{
						vr=vrr;
						break;
					}
				}
			}
			vi[fl]=0;
		}
	}
	else
	{
		
		int vln=vl[n];
		int vn=abs(v[n]);
		int vivn=vi[vn];

		if(v[n]>0)
		{
			if(vi[vn]<0)
			{
				vl[n]=-1;
				dfs(n-1,ln+1,wn,un);
			}
			else if(vi[vn]>0)
			{
				vl[n]=1;
				dfs(n-1,ln,wn,un);
			}
			else
			{
				vl[n]=1;
				vi[vn]=1;
				dfs(n-1,ln,wn,un-1);
				vl[n]=-1;
				vi[vn]=-1;
				dfs(n-1,ln+1,wn+1,un-1);
			}
		}
		else
		{
			if(vi[vn]<0)
			{
				vl[n]=1;
				dfs(n-1,ln,wn,un);
			}
			else if(vi[vn]>0)
			{
				vl[n]=-1;
				dfs(n-1,ln+1,wn,un);
			}
			else
			{
				vl[n]=1;
				vi[vn]=-1;
				dfs(n-1,ln,wn+1,un-1);
				vl[n]=-1;
				vi[vn]=1;
				dfs(n-1,ln+1,wn,un-1);
			}	
		}
		vi[vn]=vivn;
		vl[n]=vln;
		return;
	}
}
int main()
{
//	freopen("data.txt","r",stdin);
	ios::sync_with_stdio(false);
	int x;
	cin>>n>>m>>k;
	vl.resize(n+1,0);
	vi.resize(n+1,0);
	v.push_back(0);
	for(;n--;)
	{
		cin>>x;
		v.push_back(x);
	}
	dfs(v.size()-1,0,0,v.size()-1);
	
	if(vr.empty())
	cout<<"No Solution";
	else
	{
		cout<<vr[0];
		for(int i=1;i<vr.size();++i)
		cout<<" "<<vr[i];
	}
	return 0;
}
