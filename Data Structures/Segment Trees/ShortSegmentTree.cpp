struct seg {
    int n; vector<int> t;
    seg(int tn){
        n = tn; t.resize(4 * n, 1e18);
    }
    void upd(int s, int e, int i, int qi, int nw) {
        if (s == e) {
            t[i] = nw; return;
        }
        int m = (s + e) / 2;
        if(qi <= m) upd(s, m, 2 * i, qi, nw);
        else        upd(m + 1, e, 2 * i + 1, qi, nw);
        t[i] = min(t[2 * i], t[2 * i + 1]);
    }
    int qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l) return 1e18;
        if (s >= l && e <= r) return t[i];
        int m = (s + e) / 2;
        return min(qry(s, m, 2 * i, l, r), qry(m + 1, e, 2 * i + 1, l, r));
    }
};
