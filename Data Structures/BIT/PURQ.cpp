template <class T> struct BIT {
    int n;
    vector<T> bit;
    BIT(int sz) {
        n = sz + 1;
        bit.assign(n, 0);
    }
    T qry(int r) {
        T v = 0;
        for (int i = r + 1; i > 0; i -= (i & -i)) v += bit[i];
        return v;
    }
    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
    void upd(int j, T v) {
        for (int i = j + 1; i < n; i += (i & -i)) bit[i] += v;
    }
};
