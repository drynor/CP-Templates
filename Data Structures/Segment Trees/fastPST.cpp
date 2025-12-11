struct seg{
    vector<int> L, R, sum, roots;
    int sz;
    seg(vector<int>& a){
        sz = a.size();
        nw(0, 0, 0); 
        roots.pb(build(a, 0, sz - 1));
    }
    int nw(int l, int r, int s) {
        L.pb(l); R.pb(r); sum.pb(s);
        return sum.size() - 1;
    }
    int cpy(int i) {
        return nw(L[i], R[i], sum[i]);
    }
    int build(vector<int>& a, int tl, int tr) {
        if (tl == tr) {
            return nw(0, 0, a[tl]);
        }
        int tm = (tl + tr) >> 1;
        int lc = build(a, tl, tm);
        int rn = build(a, tm + 1, tr);
        return nw(lc, rn, sum[lc] + sum[rn]);
    }

    int upd(int v, int pos, int v) {
        int root = upd(roots[v], 0, sz - 1, pos, v);
        roots.pb(root);
        return roots.size() - 1;
    }
    int upd(int pn, int tl, int tr, int pos, int v) {
        if (tl == tr) {
            return nw(0, 0, v);
        }
        int cn = cpy(pn); 
        int tm = (tl + tr) >> 1;

        if (pos <= tm) L[cn] = upd(L[cn], tl, tm, pos, v);
        else           R[cn] = upd(R[cn], tm + 1, tr, pos, v);
        
        sum[cn] = sum[L[cn]] + sum[R[cn]];
        return cn;
    }

    int qry(int v, int l, int r) {
        return qry(roots[v], 0, sz - 1, l, r);
    }

    int qry(int u, int tl, int tr, int l, int r) {
        if (l > r || tl > r || tr < l || !u) return 0;
        if (l <= tl && tr <= r) return sum[u];

        int tm = (tl + tr) >> 1;
        return qry(L[u], tl, tm, l, r) + qry(R[u], tm + 1, tr, l, r);
    }
};
