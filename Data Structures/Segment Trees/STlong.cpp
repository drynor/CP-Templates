// generic point update, range query. 2n-1 nodes: root 0, left = i + 1, right = i + 2 * (m - s + 1). 0-based [l, r]
template<typename node, typename update>
struct seg {
    int n; vector<node> t;
    seg (int tn) {
        n = tn; t.resize(2 * n);
    }
    void build(int s, int e, int i, vector<node>& a) { // reference only: build(0, n - 1, 0, a)
        if (s == e) { t[i] = a[s]; return; }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        build(s, m, l, a); build(m + 1, e, r, a);
        t[i].merge(t[l], t[r]);
    }
    void upd(int s, int e, int i, int qi, update &u) {
        if (s == e) {
            u.apply(t[i]); return;
        }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        if(qi <= m) upd(s, m, l, qi, u);
        else        upd(m + 1, e, r, qi, u);
        t[i].merge(t[l], t[r]);
    }
    node qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l) return node();
        if (s >= l && e <= r) return t[i];
        int m = (s + e) / 2;
        node ln, rn, ans;
        ln = qry(s, m, i + 1, l, r);
        rn = qry(m + 1, e, i + 2 * (m - s + 1), l, r);
        ans.merge(ln, rn);
        return ans;
    }
    void upd(int i, int v) {
        update nw = update(v);
        upd(0, n - 1, 0, i, nw);
    }
    node qry(int l, int r) {
        return qry(0, n - 1, 0, l, r);
    }
};
struct node1 {
    int mn = 1e18;

    void merge(node1 &l, node1 &r) {
        mn = min(l.mn, r.mn);
    }
};
struct update1 {
    int nw;
    update1(int x) {
        nw = x;
    }
    void apply(node1 &a) {
        a.mn = nw;
    }
};
