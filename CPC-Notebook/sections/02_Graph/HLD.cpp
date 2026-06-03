/*
Algorithm: Heavy-Light Decomposition
When to use: Use for heavy-light decomposition problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct HLD{ int n,t=0; vector<vector<int>>g; vector<int>par,dep,heavy,head,pos,sz; HLD(int n):n(n),g(n),par(n),dep(n),heavy(n,-1),head(n),pos(n),sz(n){} void add_edge(int a,int b){g[a].push_back(b);g[b].push_back(a);} int dfs(int v,int p){par[v]=p;sz[v]=1;int best=0;for(int to:g[v])if(to!=p){dep[to]=dep[v]+1;int s=dfs(to,v);sz[v]+=s;if(s>best)best=s,heavy[v]=to;}return sz[v];} void decomp(int v,int h){head[v]=h;pos[v]=t++; if(heavy[v]!=-1)decomp(heavy[v],h); for(int to:g[v])if(to!=par[v]&&to!=heavy[v])decomp(to,to);} void build(int r=0){dfs(r,r);decomp(r,r);} template<class F> void path_query(int a,int b,F op){while(head[a]!=head[b]){if(dep[head[a]]<dep[head[b]])swap(a,b);op(pos[head[a]],pos[a]);a=par[head[a]];} if(dep[a]>dep[b])swap(a,b); op(pos[a],pos[b]);}};
