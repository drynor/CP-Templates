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
    ios::sync_with_stdio(false);cin.tie(0);int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    #ifndef ONLINE_JUDGE
        cout << "(=== Code Execution Successful ===)";
    #endif
}
 
struct PST{
    struct Node{
        int sum = 0;
        Node* left;
        Node* right;

        Node(){
            sum = 0;
        }
        Node(int s){
            sum = s;
        }
        Node(Node* l, Node* r){
            sum = l->sum + r->sum;
        }
        Node(Node l, Node r){
            sum = l.sum + r.sum;
        }
    };
 
    int sz;
    vector<int> arr;
    vector<Node*> roots;
 
    PST(vector<int>& a){
        sz = a.size();
        arr = a;
        
        Node* root = build(0, sz - 1);
        roots.push_back(root);
    }
 
    Node* build(int tl, int tr){
        if (tl == tr) {
            return new Node(arr[tl]);
        }
        int tm = tl + (tr - tl) / 2;
        Node* ln = build(tl, tm);
        Node* rn = build(tm + 1, tr);
        Node* cn = new Node(lc, rc);
        cn->left = lc;
        cn->right = rc;
        return cn;
    }
 
    Node* update(Node* pn, int tl, int tr, int pos, int val){
         if (tl == tr) {
            return new Node(val);
        }
        int tm = tl + (tr - tl) / 2;
        
        Node* ln;
        Node* rn;
 
        if(pos <= tm){
            ln = update(pn->left, tl, tm, pos, val);
            rn = pn->right;
        }
        else{
            ln = pn->left;
            rn = update(pn->right, tm + 1, tr, pos, val);
        }
        Node* cn = new Node(ln, rn);
        cn->left = ln;
        cn->right = rn;

        return cn;
    }
 
    Node query(Node* node, int tl, int tr, int l, int r){
        if (tl > r || tr < l)
            return 0;
        if (tl >= l && tr <= r)
            return node->sum;
 
        int tm = tl + (tr - tl) / 2;
        Node ln = query(node->left, tl, tm, l, r);
        Node rn = query(node->right, tm + 1, tr, l, r);
        return Node(ln, rn);
    }
 
    int query(int version, int l, int r){
        return query(roots[version], 0, sz - 1, l, r).sum;
    }
 
    int update(int version, int pos, int val){
        Node* root = update(roots[version], 0, sz - 1, pos, val);
        roots.push_back(root);
        return roots.size() - 1;
    }
};
 
 
void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1;i<=n;i++){
        cin >> a[i];
    }
    vector<int> b(n + 1, 1);
    PST sgt(b);
    map<int,int> mp;
    for(int i = 1;i<=n;i++){
        sgt.update(i-1, mp[a[i]], 0);
        mp[a[i]] = i;
    }
    while(q--){
        int l, r;cin >> l >> r;
        cout << sgt.query(r, l, r) << endl;
    }
} // number of distinct elements from left to right
