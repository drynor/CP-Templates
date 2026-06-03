/*
Algorithm: Min-Cost Max-Flow
When to use: Use for min-cost max-flow problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: O(flow*m log n) for full implementation.
Common bugs: For min-cost max-flow, potentials are needed with Dijkstra.
*/

struct MinCostMaxFlow{struct E{int to,rev;long long cap,cost;};int n;vector<vector<E>>g;MinCostMaxFlow(int n):n(n),g(n){}void add_edge(int v,int to,long long cap,long long cost){E a{to,(int)g[to].size(),cap,cost},b{v,(int)g[v].size(),0,-cost};g[v].push_back(a);g[to].push_back(b);} /* potentials are needed with Dijkstra; add Bellman-Ford init if initial negative reduced costs exist */ };
