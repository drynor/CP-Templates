#include <bits/stdc++.h>
#define int long long
#define ALL(c) begin(c), end(c)
#define SORT(c) sort(begin(c), end(c))
#define rSORT(c) sort(rbegin(c), rend(c))
#define f first
#define s second
#define pb push_back
#define endl "\n"
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<int>(l, r)(rng)
 
void solve();
int32_t main() {
    #ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output1.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false);cin.tie(0);int t = 1;int i = 1;
    // cin >> t;
    while (t--){//cout<<"_________________________________\n";cout<<"Test case Number: "<<i++<<endl<<endl;
        solve();
    }
    #ifndef ONLINE_JUDGE
        cout << "(=== Code Execution Successful ===)";
    #endif
}
 
vector<int> ans(500010, false);
struct AC {
  int N, P;
  const int A = 26;
 
  vector<vector<int>> next;      // trie edges
  vector<int> link;              // suffix link
  vector<int> out_link;          // nearest suffix link to an output node
  vector<vector<int>> out;       // pattern ids ending at this node
  // vector<string> str;            // string represented by each node (prefix)
  vector<bool> vis;
 
  AC() : N(0), P(0) {
    node(); // create root
  }
 
  // Create a new node and initialize data structures
  int node() {
    next.emplace_back(A, 0);     // A edges, all initially 0
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    // str.emplace_back("");        // empty string for new node
    return N++;
  }
 
  // Convert char to alphabet index
  inline int get(char c) {
    return c - 'a';
  }
 
  // Add a pattern and assign prefix strings to nodes
  int add_pattern(const string& T) {
    int u = 0;
    for (char c : T) {
      int idx = get(c);
      if (!next[u][idx]) {
        int v = node();
        // str[v] = str[u] + c;     // Build prefix string for new node
        next[u][idx] = v;
      }
      u = next[u][idx];
    }
    out[u].push_back(P);
    return P++;
  }
 
  // Build suffix and output links
  void compute() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) {
          next[u][c] = next[link[u]][c];
        } else {
          link[v] = (u ? next[link[u]][c] : 0);
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
      }
    }
    vis.resize(N, false);
  }
 
  // Advance along character c from node u
  int advance(int u, char c) {
    while (u && !next[u][get(c)]) {
      u = link[u];
    }
    u = next[u][get(c)];
    return u;
  }
 
    void dfs(int u){
        if(u == 0) return;
        if(vis[u]) return;
        vis[u] = true;
        for(auto i : out[u]){
            ans[i] = true;
        }
        dfs(link[u]);
    }
};
 
void solve(){
    AC aho;
    string a;cin >> a;
    int n;cin >> n;
    vector<string> b(n);
    for(int i = 0;i<n;i++){
        cin >> b[i];
        aho.add_pattern(b[i]);
    }
    aho.compute();
    int u = 0;
    for(char c : a){
        u = aho.advance(u, c);
        aho.dfs(u);
    }
    for(int i = 0;i<n;i++){
        if(ans[i]) cout << "YES" << endl;
        else       cout << "NO" << endl;
    }
}
