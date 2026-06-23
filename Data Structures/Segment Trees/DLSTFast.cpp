struct seg {
    struct node {
        int val, l, r, us; bool lz;
        node() {
            val = us = lz = 0;
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
 
    void apply(int i, int s, int e, int u) {
        t[i].val += u * (e - s + 1);
        t[i].us += u;
        t[i].lz = true;
    }
 
    void push(int i, int s, int e) {
        if (!t[i].lz || s == e) return;
 
        int m = s + (e - s) / 2;
        if (t[i].l == -1) t[i].l = ptr++;
        if (t[i].r == -1) t[i].r = ptr++;
 
        apply(t[i].l, s, m, t[i].us);
        apply(t[i].r, m + 1, e, t[i].us);
 
        t[i].us = t[i].lz = 0;
    }
 
    void upd(int s, int e, int i, int l, int r, int u) {
        if (i == -1 || e < l || s > r) return;
        if (l <= s && e <= r) {
            apply(i, s, e, u); return;
        }
        push(i, s, e);
 
        int m = s + (e - s) / 2;
        if (l <= m) {
            if (t[i].l == -1) t[i].l = ptr++;
            upd(s, m, t[i].l, l, r, u);
        }
        if (r > m) {
            if (t[i].r == -1) t[i].r = ptr++;
            upd(m + 1, e, t[i].r, l, r, u);
        }
 
        t[i].val = (t[i].l == -1 ? 0 : t[t[i].l].val) + (t[i].r == -1 ? 0 : t[t[i].r].val);
    }
    void upd(int l, int r, int u) {
        upd(mn, mx, root, l, r, u);
    }
 
    int qry(int s, int e, int i, int l, int r) {
        if (i == -1 || e < l || s > r) return 0;
        if (l <= s && e <= r) {
            return t[i].val;
        }
        push(i, s, e);
        
        int m = s + (e - s) / 2;
        return qry(s, m, t[i].l, l, r) + qry(m + 1, e, t[i].r, l, r);
    }
    int qry(int l, int r) {
        return qry(mn, mx, root, l, r);
    }
};
