/*
Algorithm: 0-1 BFS
When to use: Use for 0-1 bfs problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: O(n+m).
Common bugs: Only valid for weights 0 and 1.
*/

const int INF=1e9;
vector<int> zero_one_bfs(int n, vector<vector<pair<int,int>>>& g, int s){ vector<int>d(n,INF); deque<int>q; d[s]=0; q.push_front(s); while(!q.empty()){ int v=q.front(); q.pop_front(); for(auto [to,w]:g[v]) if(d[to]>d[v]+w){ d[to]=d[v]+w; if(w==0) q.push_front(to); else q.push_back(to); } } return d; }
