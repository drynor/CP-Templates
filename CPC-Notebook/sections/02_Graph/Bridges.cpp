/*
Algorithm: Bridges
When to use: Use for bridges problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct Bridges{int n,t=0;vector<vector<pair<int,int>>>g;vector<int>tin,low;vector<pair<int,int>>ans;Bridges(int n):n(n),g(n),tin(n,-1),low(n){}void add_edge(int a,int b,int id){g[a].push_back({b,id});g[b].push_back({a,id});}void dfs(int v,int pe=-1){tin[v]=low[v]=t++;for(auto [to,id]:g[v])if(id!=pe){if(tin[to]==-1){dfs(to,id);low[v]=min(low[v],low[to]);if(low[to]>tin[v])ans.push_back({v,to});}else low[v]=min(low[v],tin[to]);}}};
