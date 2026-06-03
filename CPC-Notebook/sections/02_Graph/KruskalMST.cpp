/*
Algorithm: Kruskal MST
When to use: Use for kruskal mst problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct DSU{vector<int>p,sz;DSU(int n):p(n),sz(n,1){iota(p.begin(),p.end(),0);}int find(int x){return p[x]==x?x:p[x]=find(p[x]);}bool unite(int a,int b){a=find(a);b=find(b);if(a==b)return false;if(sz[a]<sz[b])swap(a,b);p[b]=a;sz[a]+=sz[b];return true;}};struct Edge{int u,v;long long w;};pair<long long,vector<Edge>> kruskal(int n,vector<Edge> e){sort(e.begin(),e.end(),[](auto&a,auto&b){return a.w<b.w;});DSU d(n);long long cost=0;vector<Edge>ch;for(auto x:e)if(d.unite(x.u,x.v))cost+=x.w,ch.push_back(x);return {cost,ch};}
