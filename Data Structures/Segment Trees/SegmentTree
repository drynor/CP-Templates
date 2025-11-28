template<typename node, typename update>
struct seg {
    int n; vector<node> t;
    seg (int tn) {
        n = tn; t.resize(4 * n);
    }
    void upd(int s, int e, int i, int qi, update &u) {
        if (s == e) {
            u.apply(t[i]); return;
        }
        int m = (s + e) / 2;
        if(qi <= m) upd(s, m, 2 * i, qi, u);
        else        upd(m + 1, e, 2 * i + 1, qi, u);
        t[i].merge(t[2 * i], t[2 * i + 1]);
    }
    void upd(int i, int v) {
        update nw = update(v);
        upd(0, n - 1, 1, i, nw);
    }
    node qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l) return node();
        if (s >= l && e <= r) return t[i];
        int m = (s + e) / 2;
        node ln, rn, ans;
        ln = qry(s, m, 2 * i, l, r);
        rn = qry(m + 1, e, 2 * i + 1, l, r);
        ans.merge(ln, rn);
        return ans;
    }
    node qry(int l, int r) {
        return qry(0, n - 1, 1, l, r);
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
