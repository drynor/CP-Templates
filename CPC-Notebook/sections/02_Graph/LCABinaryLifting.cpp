/*
Algorithm: LCA Binary Lifting
When to use: Use for lca binary lifting problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct LCA{ int n,LOG; vector<int> dep; vector<vector<int>> up,g; LCA(int n):n(n),LOG(1),dep(n),g(n){ while((1<<LOG)<=n)LOG++; up.assign(LOG,vector<int>(n)); } void add_edge(int a,int b){g[a].push_back(b);g[b].push_back(a);} void dfs(int v,int p){ up[0][v]=p; for(int i=1;i<LOG;i++) up[i][v]=up[i-1][up[i-1][v]]; for(int to:g[v]) if(to!=p){ dep[to]=dep[v]+1; dfs(to,v);} } void build(int r=0){dfs(r,r);} int lift(int v,int k){ for(int i=0;i<LOG;i++) if(k>>i&1) v=up[i][v]; return v;} int lca(int a,int b){ if(dep[a]<dep[b]) swap(a,b); a=lift(a,dep[a]-dep[b]); if(a==b)return a; for(int i=LOG-1;i>=0;i--) if(up[i][a]!=up[i][b]) a=up[i][a],b=up[i][b]; return up[0][a]; } };
