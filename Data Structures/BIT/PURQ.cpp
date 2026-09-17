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
    // smallest i (0-indexed) with prefix sum qry(i) >= k; returns sz if none. needs all values >= 0
    int kth(int k) {
        int pos = 0;
        for (int pw = 1 << __lg(n); pw; pw >>= 1)
            if (pos + pw < n && bit[pos + pw] < k) pos += pw, k -= bit[pos];
        return pos;
    }
};
