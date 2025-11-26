#include <bits/stdc++.h>
// #define int long long
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
    ios::sync_with_stdio(false);cin.tie(0);int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    #ifndef ONLINE_JUDGE
        cout << "(=== Code Execution Successful ===)";
    #endif
}
int n, q;
const int N = 1e5 + 10;
const int B = 350;
vector<int> g[N];
vector<int> a(N);
int st[N], en[N], T, par[N][20], dep[N], id[N * 2];
void dfs(int u, int p) {
    st[u] = ++T;
    id[T] = u;
    dep[u] = dep[p] + 1;
    par[u][0] = p;
    for(int k = 1; k < 20; k++) par[u][k] = par[par[u][k - 1]][k - 1];
    for(auto v : g[u]) if(v != p) dfs(v, u);
    en[u] = ++T;
    id[T] = u;
}
int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int k = 19; k >= 0; k--) if(dep[par[u][k]] >= dep[v]) u = par[u][k];
    if(u == v) return u;
    for(int k = 19; k >= 0; k--) if(par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}
struct Query {
    int l, r, lc, idx;
    bool mr;
};
int block[N / B + 5];
int f[N];
struct SQRT {
    void update(int ind, int val) {
        if (ind > N || ind < 0) return;
        if(f[ind] == 0){
            block[ind / B]++;
        }
        f[ind] += val;
        if(f[ind] == 0){
            block[ind / B]--;
        }
    }
    int query() {
        int ans = 0;
        for(int i = 0;i<N;i+=B){
            int cur = block[i / B];
            if(cur < B){
                for(int j = i;j<min(i + B, N);j++){
                    if(!f[j])break;
                    ans++;
                }
                break;
            }
            ans += cur;
        }
        return ans;
    }
} ds;
int freq[N];
void add(int i){
    freq[i]++;
    if(freq[i] & 1){
        ds.update(a[i] - 1, 1);
    }
    else{
        ds.update(a[i] - 1, -1);
    }
}
void rmv(int i){
    freq[i]--;
    if(freq[i] & 1){
        ds.update(a[i] - 1, 1);
    }
    else{
        ds.update(a[i] - 1, -1);
    }
}

void solve(){
    cin >> n >> q;
    for(int i = 0;i<n;i++){
        cin >> a[i];
    }
    for(int i = 1;i<n;i++){
        int u, v; cin >> u >> v; u--; v--; g[u].pb(v); g[v].pb(u);
    }
    dfs(0, 0);

    int B = max(1, (int)sqrt(n));
    vector<Query> qs(q);
    for (int i = 0; i < q; ++i) {
        int u, v;cin >> u >> v;u--; v--;
        if(st[u] > st[v]) swap(u, v);
        qs[i].lc = lca(u, v);
        if(qs[i].lc == u){
            qs[i].l = st[u];
            qs[i].r = st[v];
            qs[i].mr = false;
        }
        else{
            qs[i].l = en[u];
            qs[i].r = st[v];
            qs[i].mr = true;
        }
        qs[i].idx = i;
    }
    sort(qs.begin(), qs.end(), [&](const Query &A, const Query &BQ){
        int b1 = A.l / B, b2 = BQ.l / B;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (A.r > BQ.r) : (A.r < BQ.r);
    });
    vector<int> ans(q);
    int curL = 1, curR = 0;
    for (auto &Q : qs) {
        int L = Q.l, R = Q.r;
        while (curL > L) add(id[--curL]);
        while (curR < R) add(id[++curR]);
        while (curL < L) rmv(id[curL++]);
        while (curR > R) rmv(id[curR--]);
        if(Q.mr){
            add(Q.lc);
        }
        ans[Q.idx] = ds.query();
        if(Q.mr){
            rmv(Q.lc);
        }
    }
    for(int i = 0;i<q;i++){
        cout << ans[i] << endl;
    }
}
