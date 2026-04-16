struct sgt {
    int n;
    vector<int> t;

    sgt(int tn, vector<int> &a) {
        n = tn;
        t.assign(2 * n, 0); 
        for (int i = 0; i < n; i++) {
            t[n + i] = a[i];
        }
        build();
    }

    void build() {
        for(int i = n - 1; i > 0; i--) {
            t[i] = max(t[i<<1], t[i<<1|1]);
        }
    }

    void upd(int i, int v) {
        for (t[i += n] = v; i > 1; i >>= 1) {
            t[i>>1] = max(t[i], t[i^1]);
        }
    }

    int qry(int l, int r) {
        int v = -1e9;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)    v = max(v, t[l++]);
            if (!(r & 1)) v = max(v, t[r--]);
        }
        return v;
    }
};
