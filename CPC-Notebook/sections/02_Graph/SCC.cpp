/*
Algorithm: Strongly Connected Components
When to use: Use for strongly connected components problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct SCC{int n,t=0,cnt=0;vector<vector<int>>g;vector<int>tin,low,comp,st,ins;SCC(int n):n(n),g(n),tin(n,-1),low(n),comp(n,-1),ins(n){}void add_edge(int a,int b){g[a].push_back(b);}void dfs(int v){tin[v]=low[v]=t++;st.push_back(v);ins[v]=1;for(int to:g[v]){if(tin[to]==-1)dfs(to),low[v]=min(low[v],low[to]);else if(ins[to])low[v]=min(low[v],tin[to]);}if(low[v]==tin[v]){while(1){int x=st.back();st.pop_back();ins[x]=0;comp[x]=cnt;if(x==v)break;}cnt++;}}};
