/*
Algorithm: Dijkstra Shortest Path
When to use: Use for dijkstra shortest path problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: O((n+m) log n).
Common bugs: This breaks if graph has negative edges.
*/

using ll=long long; const ll INF=(1LL<<62);
vector<ll> dijkstra(int n, vector<vector<pair<int,int>>>& g, int s){ vector<ll>d(n,INF); priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq; d[s]=0; pq.push({0,s}); while(!pq.empty()){ auto [du,v]=pq.top(); pq.pop(); if(du!=d[v]) continue; for(auto [to,w]:g[v]) if(d[to]>du+w){ d[to]=du+w; pq.push({d[to],to}); } } return d; }
