/*
Algorithm: Articulation Points
When to use: Use for articulation points problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct ArticulationPoints{int n,t=0;vector<vector<int>>g;vector<int>tin,low,cut;ArticulationPoints(int n):n(n),g(n),tin(n,-1),low(n),cut(n){}void add_edge(int a,int b){g[a].push_back(b);g[b].push_back(a);}void dfs(int v,int p=-1){tin[v]=low[v]=t++;int ch=0;for(int to:g[v])if(to!=p){if(tin[to]!=-1)low[v]=min(low[v],tin[to]);else{dfs(to,v);low[v]=min(low[v],low[to]);if(low[to]>=tin[v]&&p!=-1)cut[v]=1;ch++;}}if(p==-1&&ch>1)cut[v]=1;}};
