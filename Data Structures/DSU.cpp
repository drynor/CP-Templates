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

// dsu WITH ROLLBACK
struct dsu {
    vector<int> p, sz;
    stack<tuple<int, int, int, int>> history;
    int components;

    dsu(int n){
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
        sz.assign(n + 1, 1);
        components = n;
    }

    int get(int x){
        return x == p[x] ? x : get(p[x]);
    }

    void unite(int x, int y){
        x = get(x);
        y = get(y);
        if (x != y) {
            if (sz[x] < sz[y]){
                swap(x, y);
            }
            history.push({x, sz[x], y, p[y]});

            p[y] = x;
            sz[x] += sz[y];
            components--;
        }
    }

    void rollback(){
        auto [root_x, old_sz_x, root_y, old_p_y] = history.top();
        history.pop();
        
        p[root_y] = old_p_y;
        sz[root_x] = old_sz_x;
        components++;
    }
};
