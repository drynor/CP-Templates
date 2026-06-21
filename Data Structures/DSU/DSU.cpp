struct dsu {
    int n;
    vector<int> p, sz;
    dsu(int tn) : n(tn) {
        p.resize(n);
        sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }
    inline bool unite(int x, int y) {
        x = get(x); y = get(y);
        if (x != y) {
            if (sz[x] < sz[y]) swap(x, y); 
            p[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};
