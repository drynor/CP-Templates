// lazy range add, range sum. 2n-1 nodes: root 0, left = i + 1, right = i + 2 * (m - s + 1). 0-based [l, r]
struct seg {
    vector<int> t, us;
    int n, def = 0;
    seg(int tn) {
        n = tn;
        t.assign(2 * n, def);
        us.assign(2 * n, 0);
    }
    void build(int s, int e, int i, vector<int>& a) { // reference only: build(0, n - 1, 0, a)
        if (s == e) { t[i] = a[s]; return; }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        build(s, m, l, a); build(m + 1, e, r, a);
        t[i] = t[l] + t[r];
    }
    void apply(int i, int s, int e, int u){
        us[i] += u;
        t[i] += u * (e - s + 1);
    }
    void push(int i, int s, int e){
        if(us[i]){
            int m = (s + e) / 2;
            apply(i + 1, s, m, us[i]);
            apply(i + 2 * (m - s + 1), m + 1, e, us[i]);
            us[i] = 0;
        }
    }
    void upd(int s, int e, int i, int l, int r, int u) {
        if(s > r || e < l) return;
        if(s >= l && e <= r){
            apply(i, s, e, u); return;
        }
        push(i, s, e);
        int m = (s + e) / 2, lc = i + 1, rc = i + 2 * (m - s + 1);
        upd(s, m, lc, l, r, u);
        upd(m + 1, e, rc, l, r, u);
        t[i] = t[lc] + t[rc];
    }
    int qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l)   return def;
        if (s >= l && e <= r) return t[i];
        push(i, s, e);
        int m = (s + e) / 2;
        return qry(s, m, i + 1, l, r) + qry(m + 1, e, i + 2 * (m - s + 1), l, r);
    }
    void upd(int l, int r, int u) { upd(0, n - 1, 0, l, r, u); }
    int qry(int l, int r) { return qry(0, n - 1, 0, l, r); }
};
