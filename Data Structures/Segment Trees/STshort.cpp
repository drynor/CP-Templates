// point set, range min. 2n-1 nodes: root 0, left = i + 1, right = i + 2 * (m - s + 1). 0-based [l, r]
struct seg {
    int n; vector<int> t;
    seg(int tn){
        n = tn; t.assign(2 * n, 1e18);
    }
    void build(int s, int e, int i, vector<int>& a) { // O(n) init from array; call build(0, n - 1, 0, a)
        if (s == e) {
            t[i] = a[s]; return;
        }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        build(s, m, l, a);
        build(m + 1, e, r, a);
        t[i] = min(t[l], t[r]);
    }
    void upd(int s, int e, int i, int qi, int v) {
        if (s == e) {
            t[i] = v; return;
        }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        if(qi <= m) upd(s, m, l, qi, v);
        else        upd(m + 1, e, r, qi, v);
        t[i] = min(t[l], t[r]);
    }
    int qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l) return 1e18;
        if (s >= l && e <= r) return t[i];
        int m = (s + e) / 2;
        return min(qry(s, m, i + 1, l, r), qry(m + 1, e, i + 2 * (m - s + 1), l, r));
    }
    void upd(int qi, int v) { upd(0, n - 1, 0, qi, v); }
    int qry(int l, int r) { return qry(0, n - 1, 0, l, r); }
};
