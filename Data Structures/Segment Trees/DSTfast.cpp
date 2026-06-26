struct seg {
    struct node {
        int val, l, r;
        node() {
            val = 0;
            l = r = -1;
        }
    };

    vector<node> t;
    int ptr = 0, root, mn, mx;

    seg(int tmn, int tmx, int n) {
        mn = tmn, mx = tmx;
        t.resize(n);
        root = ptr++;
    }

    void upd(int s, int e, int i, int qi, int v) {
        t[i].val += v;
        if (s == e) return;

        int m = s + (e - s) / 2;

        if (qi <= m) {
            if (t[i].l == -1) t[i].l = ptr++;
            upd(s, m, t[i].l, qi, v);
        } else {
            if (t[i].r == -1) t[i].r = ptr++;
            upd(m + 1, e, t[i].r, qi, v);
        }
    }

    int qry(int s, int e, int i, int l, int r) {
        if (i == -1 || e < l || s > r) return 0;
        if (l <= s && e <= r) return t[i].val;

        int m = s + (e - s) / 2;

        return qry(s, m, t[i].l, l, r) + qry(m + 1, e, t[i].r, l, r);
    }
    
    void upd(int ind, int v) {
        upd(mn, mx, root, ind, v);
    }

    int qry(int l, int r) {
        return qry(mn, mx, root, l, r);
    }
};
