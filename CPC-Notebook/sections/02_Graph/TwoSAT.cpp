/*
Algorithm: 2SAT
When to use: Use for 2sat problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct TwoSAT{int n;vector<vector<int>>g,gr;vector<int>comp,ord,asg,vis;TwoSAT(int n):n(n),g(2*n),gr(2*n),comp(2*n),asg(n),vis(2*n){}int id(int x,bool val){return 2*x^(!val);}void imp(int a,int b){g[a].push_back(b);gr[b].push_back(a);}void add_or(int a,bool av,int b,bool bv){imp(id(a,!av),id(b,bv));imp(id(b,!bv),id(a,av));}void dfs1(int v){vis[v]=1;for(int to:g[v])if(!vis[to])dfs1(to);ord.push_back(v);}void dfs2(int v,int c){comp[v]=c;for(int to:gr[v])if(comp[to]==-1)dfs2(to,c);}bool solve(){for(int i=0;i<2*n;i++)if(!vis[i])dfs1(i);fill(comp.begin(),comp.end(),-1);reverse(ord.begin(),ord.end());int c=0;for(int v:ord)if(comp[v]==-1)dfs2(v,c++);for(int i=0;i<n;i++){if(comp[2*i]==comp[2*i+1])return false;asg[i]=comp[2*i]>comp[2*i+1];}return true;}};
