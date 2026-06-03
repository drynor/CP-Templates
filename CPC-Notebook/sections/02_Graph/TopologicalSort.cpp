/*
Algorithm: Topological Sort
When to use: Use for topological sort problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

vector<int> topological_sort(int n,const vector<vector<int>>& g){vector<int>in(n),ord;for(int v=0;v<n;v++)for(int to:g[v])in[to]++;queue<int>q;for(int i=0;i<n;i++)if(!in[i])q.push(i);while(!q.empty()){int v=q.front();q.pop();ord.push_back(v);for(int to:g[v])if(--in[to]==0)q.push(to);}return ord;}
