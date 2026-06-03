/*
Algorithm: Floyd Warshall
When to use: Use for floyd warshall problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

using ll=long long; const ll INF=(1LL<<60);
void floyd_warshall(vector<vector<ll>>& d){ int n=d.size(); for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(d[i][k]<INF&&d[k][j]<INF) d[i][j]=min(d[i][j],d[i][k]+d[k][j]); }
