#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <queue>

#define int long long
using namespace std;
int p[100005];
int ans[100005],n,a,b,deg[100005];
map <int,int> mp;
vector <int> e[100005];
queue <int> q;
vector <int> v;
inline void dfs(int u)
{
	v.push_back(u);
	for(auto x:e[u])
		if(x!=v.back()&&x!=v[0]) dfs(x);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> a >> b;
	for(int i=1;i<=n;i++)
	{
		cin >> p[i];
		mp[p[i]]=i,ans[i]=-1;
	}
	for(int i=1;i<=n;i++)
	{
		if(mp[a-p[i]]) e[i].push_back(mp[a-p[i]]);
		if(a!=b) if(mp[b-p[i]]) e[i].push_back(mp[b-p[i]]);
	}
	for(int i=1;i<=n;i++)
	{
		deg[i]=e[i].size();
		if(deg[i]==1) q.push(i);
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(auto v:e[x])
		{
			if(ans[v]==-1)
			{
				if(ans[x]==-1)
				{
					if(p[x]+p[v]==a) ans[x]=ans[v]=0;
					else ans[x]=ans[v]=1;
				}
				if(--deg[v]==1) q.push(v);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(deg[i]==2)
		{
			v.clear(),dfs(i);
			if(v.size()%2)
			{
				cout << "NO";
				return 0;
			}
			for(int i=1;i<v.size();i+=2)
			{
				if(p[v[i]]+p[v[i-1]]==a) ans[v[i]]=ans[v[i-1]]=0;
				else ans[v[i]]=ans[v[i-1]]=1;
			}
			for(auto t:v) deg[t]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]==-1)
		{
			cout << "NO";
			return 0;
		}
	}
	cout << "YES\n";
	for(int i=1;i<=n;i++)
		cout << ans[i] << " ";
	return 0;
}
// g++ -std=c++17 -o a test.cpp && ./a < a.in