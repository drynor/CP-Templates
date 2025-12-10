struct node { 
    vector<int> v; 
    node() {}; 
    node(int x) : v({x}) {}; 
};
struct mst{ 
    vector<node> t; 
    int sz; 
    mst(int tn) { 
        sz = 1; 
        while (sz < tn) sz <<= 1; 
        t.assign(sz * 2, node()); 
    } 
    node merge(node &l, node &r) { 
        node res; 
        int i = 0, j = 0; 
        while (i < l.v.size() && j < r.v.size()) { 
            if (l.v[i] < r.v[j]) res.v.push_back(l.v[i++]); 
            else res.v.push_back(r.v[j++]); 
        } 
        while (i < l.v.size()) res.v.push_back(l.v[i++]); 
        while (j < r.v.size()) res.v.push_back(r.v[j++]); 
        return res; 
    } 
    void build(vector<int> &v, int x, int lx, int rx) { 
        if (rx - lx == 1) {
            if (lx < v.size()) t[x] = node(v[lx]); 
            return; 
        } 
        build(v, (x * 2 + 1), lx, (lx + rx) / 2); 
        build(v, (x * 2 + 2), (lx + rx) / 2, rx); 
        t[x] = merge(t[(x * 2 + 1)], t[(x * 2 + 2)]); 
    } 
    int query(int l, int r, int x, int lx, int rx, int val) { 
        if (rx <= l || lx >= r) return 0; 
        if (lx >= l && rx <= r) return calc(t[x], val); 
        return query(l, r, (x * 2 + 1), lx, (lx + rx) / 2, val) + query(l, r, (x * 2 + 2), (lx + rx) / 2, rx, val); 
    } 
    int query(int l, int r, int val) {
        return query(l, r, 0, 0, sz, val); 
    }
    int calc(node &no, int val) { 
        return greater_than(no, val); 
    }
    int less_than(node &no, int val) {
        return lower_bound(no.v.begin(), no.v.end(), val) - no.v.begin(); 
    } 
    int greater_than(node &no, int val) { 
        return no.v.size() - less_than(no, val) - equal(no, val); 
    } 
    int equal(node &no, int val) { 
        return upper_bound(no.v.begin(), no.v.end(), val) - lower_bound(no.v.begin(), no.v.end(), val); 
    } 
};
