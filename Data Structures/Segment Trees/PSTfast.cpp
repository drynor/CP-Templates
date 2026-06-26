struct seg {
    struct node {
        int l, r, sum;
        node() {
            l = r = sum = 0;
        }
        node(int tl, int tr, int tsum) {
            l = tl; r = tr; sum = tsum;
        }
    };

    vector<node> t;
    vector<int> roots;
    int sz, ptr = 0;

    seg(vector<int>& a, int n) {
        sz = a.size();
        t.resize(n);
        nw(0, 0, 0); // node 0 = null node
        roots.pb(build(a, 0, sz - 1));
    }

    int nw(int l, int r, int sum) {
        t[ptr] = node(l, r, sum);
        return ptr++;
    }

    int cpy(int i) { 
        return nw(t[i].l, t[i].r, t[i].sum); 
    }

    int build(vector<int>& a, int s, int e) {
        if (s == e) return nw(0, 0, a[s]);

        int m = s + (e - s) / 2,
            l = build(a, s, m),
            r = build(a, m + 1, e);

        return nw(l, r, t[l].sum + t[r].sum);
    }

    int upd(int s, int e, int i, int ind, int v) {
        if (s == e) return nw(0, 0, v);

        int nw = cpy(i), m = s + (e - s) / 2;

        if (ind <= m) t[nw].l = upd(s, m, t[nw].l, ind, v);
        else           t[nw].r = upd(m + 1, e, t[nw].r, ind, v);

        t[nw].sum = t[t[nw].l].sum + t[t[nw].r].sum;
        return nw;
    }

    int qry(int s, int e, int i, int l, int r) {
        if (i == 0 || e < l || s > r) return 0;
        if (l <= s && e <= r) return t[i].sum;

        int m = s + (e - s) / 2;
        return qry(s, m, t[i].l, l, r) + qry(m + 1, e, t[i].r, l, r);
    }
    int upd(int ver, int i, int v) {
        int root = upd(0, sz - 1, roots[ver], i, v);
        roots.push_back(root);
        return roots.size() - 1;
    }
    int qry(int ver, int l, int r) {
        return qry(0, sz - 1, roots[ver], l, r);
    }
};
