/*
Algorithm: Disjoint Set Union
When to use: Use for connectivity with only added edges, Kruskal, grouping, and offline union constraints.
Indexing: 0-indexed unless noted
Complexity: See code and notes.
Common bugs: Initialize every node.
*/

struct dsu {
    vector<int> p, sz;
    int n;
 
    dsu(int tn) : n(tn) {
        p.resize(n);
        sz.resize(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }
    inline bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            if (sz[x] < sz[y]) {
                swap(x, y); 
            }
            p[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};
