/*
Algorithm: Dinic Max Flow
When to use: Use for dinic max flow problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct Dinic{struct E{int to,rev;long long cap;};int n;vector<vector<E>>g;vector<int>lvl,it;Dinic(int n):n(n),g(n),lvl(n),it(n){}void add_edge(int v,int to,long long c){E a{to,(int)g[to].size(),c},b{v,(int)g[v].size(),0};g[v].push_back(a);g[to].push_back(b);}bool bfs(int s,int t){fill(lvl.begin(),lvl.end(),-1);queue<int>q;lvl[s]=0;q.push(s);while(!q.empty()){int v=q.front();q.pop();for(auto&e:g[v])if(e.cap>0&&lvl[e.to]==-1)lvl[e.to]=lvl[v]+1,q.push(e.to);}return lvl[t]!=-1;}long long dfs(int v,int t,long long f){if(v==t)return f;for(int&i=it[v];i<(int)g[v].size();i++){E&e=g[v][i];if(e.cap>0&&lvl[e.to]==lvl[v]+1){long long r=dfs(e.to,t,min(f,e.cap));if(r){e.cap-=r;g[e.to][e.rev].cap+=r;return r;}}}return 0;}long long max_flow(int s,int t){long long flow=0,p;while(bfs(s,t)){fill(it.begin(),it.end(),0);while((p=dfs(s,t,LLONG_MAX)))flow+=p;}return flow;}};
