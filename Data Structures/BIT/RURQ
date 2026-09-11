template <class T> struct BIT {
    int n;
    vector<T> bit1, bit2;

    BIT(int sz) {
        n = sz + 1;
        bit1.assign(n, 0);
        bit2.assign(n, 0);
    }
    void upd(vector<T>& b, int idx, T val) {
        for (; idx < n; idx += idx & -idx)
            b[idx] += val;
    }
    T qry(vector<T>& b, int idx) {
        T v = 0;
        for (; idx > 0; idx -= idx & -idx)
            v += b[idx];
        return v;
    }
    void upd(int l, int r, T val) {
        upd(bit1, l + 1, val);
        upd(bit2, l + 1, val * l);
        upd(bit1, r + 2, -val);
        upd(bit2, r + 2, -val * (r + 1));
    }
    T pqry(int idx) {
        return qry(bit1, idx + 1) * (idx + 1) - qry(bit2, idx + 1);
    }
    T qry(int l, int r) {
        return pqry(r) - pqry(l - 1);
    }
};
