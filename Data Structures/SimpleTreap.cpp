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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct treap {
    struct node {
        int val, sum;
        int sz, prior;
        node *l, *r;

        node() {
            val = 0;
            sum = 0;
            sz = 0;
            prior = 0;
            l = r = NULL;
        }

        node(int nw) {
            val = nw;
            sum = nw;
            sz = 1;
            prior = rnd();
            l = r = NULL;
        }
    };
    typedef node* pnode;
    pnode root;

    void clear() {
        root = NULL;
    }
    treap() {
        clear();
    }
    int size(pnode t) {
        return t ? t->sz : 0;
    }
    void update_size(pnode &t) {
        if(t) t->sz = size(t->l) + size(t->r) + 1;
    }
    void reset(pnode &t) {
        if(!t) return;
        t->sum = t->val;
    }
    void combine(pnode &t, pnode l, pnode r) {
        if(!l) {
            t = r;  return;
        }
        if(!r) {
            t = l; return;
        }
        t->sum = (l->sum ^ r->sum);
    }

    void operation(pnode &t) {
        if(!t) return;
        reset(t);
        combine(t, t->l, t);
        combine(t, t, t->r);
    }

    void split(pnode t, pnode &l, pnode &r, int k, int add = 0) {
        if(!t) {
            l = r = NULL; return;
        }
        int idx = add + size(t->l);
        if(idx <= k)    split(t->r, t->r, r, k, idx + 1), l = t;
        else            split(t->l, l, t->l, k, add), r = t;
        update_size(t);
        operation(t);
    }

    void merge(pnode &t, pnode l, pnode r) {
        if(!l) {
            t = r; return;
        }
        if(!r) {
            t = l; return;
        }
        if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
        else                    merge(r->l, l, r->l), t = r;
        update_size(t);
        operation(t);
    }
    void insert(int pos, int val) {
        if(root == NULL) {
            pnode to_add = new node(val);
            root = to_add;
            return;
        }
        pnode l, r, mid;
        mid = new node(val);
        split(root, l, r, pos - 1);
        merge(l, l, mid);
        merge(root, l, r);
    }
    void erase(int qL, int qR) {
        pnode l, r, mid;
        split(root, l, r, qL - 1);
        split(r, mid, r, qR - qL);
        merge(root, l, r);
    }
    int query(int qL, int qR) {
        pnode l, r, mid;
        split(root, l, r, qL - 1);
        split(r, mid, r, qR - qL);
        int answer = mid->sum;
        merge(r, mid, r);
        merge(root, l, r);
        return answer;
    }
};

treap t;

void solve() {
    int n;cin >> n;
    for(int i = 1;i<=n;i++){
        int x;cin >> x;
        t.insert(i, x);
    }
    int q;
    cin >> q;
    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int inx;
            int val;
            cin >> inx >> val;
            t.insert(inx - 1, val);
        } else if(type == 2) {
            int inx;
            cin >> inx;
            t.erase(inx - 1, inx - 1);
        } else if(type == 3) {
            int l, r;
            cin >> l >> r;
            cout << t.query(l - 1, r - 1) << endl;
        }
    }
}
