// generic lazy segment tree. 2n-1 nodes: root 0, left = i + 1, right = i + 2 * (m - s + 1). 0-based [l, r]
template<typename node, typename update>
struct seg {
    vector<node> t;
    vector<char> lazy;
    vector<update> us;
    int n;
    seg(int tn) {
        n = tn;
        t.resize(2 * n);
        lazy.assign(2 * n, 0);
        us.resize(2 * n);
    }
    void build(int s, int e, int i, vector<node>& a) { // reference only: build(0, n - 1, 0, a)
        if (s == e) { t[i] = a[s]; return; }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        build(s, m, l, a); build(m + 1, e, r, a);
        t[i].merge(t[l], t[r]);
    }
    void apply(int i, int s, int e, update& u){
        if(s != e){
            lazy[i] = 1;
            us[i].combine(u, s, e);
        }
        u.apply(t[i], s, e);
    }
    void push(int i, int s, int e){
        if(lazy[i]){
            int m = (s + e) / 2;
            apply(i + 1, s, m, us[i]);
            apply(i + 2 * (m - s + 1), m + 1, e, us[i]);
            us[i] = update();
            lazy[i] = 0;
        }
    }
    void upd(int s, int e, int i, int l, int r, update& u) {
        if(s > r || e < l) return;
        if(s >= l && e <= r){
            apply(i, s, e, u); return;
        }
        push(i, s, e);
        int m = (s + e) / 2, lc = i + 1, rc = i + 2 * (m - s + 1);
        upd(s, m, lc, l, r, u);
        upd(m + 1, e, rc, l, r, u);
        t[i].merge(t[lc], t[rc]);
    }
    node qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l)   return node();
        if (s >= l && e <= r) return t[i];
        push(i, s, e);
        int m = (s + e) / 2;
        node ln, rn, ans;
        ln = qry(s, m, i + 1, l, r);
        rn = qry(m + 1, e, i + 2 * (m - s + 1), l, r);
        ans.merge(ln, rn);
        return ans;
    }
    void upd(int l, int r, int val) { update nw = update(val); upd(0, n - 1, 0, l, r, nw); }
    void upd(int l, int r, update u) { upd(0, n - 1, 0, l, r, u); }
    node qry(int l, int r) { return qry(0, n - 1, 0, l, r); }
};
struct node1 {
    int sum = 0;
    void merge(node1 &l, node1 &r) {
        sum = l.sum + r.sum;
    }
};
struct upd1 {
    int val;
    upd1(int val1 = 0){
        val = val1;
    }
    void apply(node1 &a, int s, int e) {
        a.sum += val * (e - s + 1);
    }
    void combine(upd1& nw, int s, int e){
        val += nw.val;
    }
};
