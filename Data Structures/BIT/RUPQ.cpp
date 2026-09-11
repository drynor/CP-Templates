struct BIT {
    int n;
    vector<int> bit;
    BIT(int sz) {
        n = sz + 1;
        bit.assign(n, 0);
    }
    int qry(int j) {
        int v = 0;
        for (int i = j + 1; i > 0; i -= (i & -i)) v += bit[i];
        return v;
    }
    void upd(int j, int v) {
        for (int i = j + 1; i < n; i += (i & -i)) bit[i] += v;
    }
    void upd(int l, int r, int v) {
        if (l > r) return;
        upd(l, v);
        upd(r + 1, -v);
    }
};
