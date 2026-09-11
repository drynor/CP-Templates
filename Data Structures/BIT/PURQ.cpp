struct BIT {
    int n;
    vector<int> bit;
    BIT(int sz) {
        n = sz + 1;
        bit.assign(n, 0);
    }
    int qry(int r) {
        int v = 0;
        for (int i = r + 1; i > 0; i -= (i & -i)) v += bit[i];
        return v;
    }
    int qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
    void upd(int j, int v) {
        for (int i = j + 1; i < n; i += (i & -i)) bit[i] += v;
    }
};
