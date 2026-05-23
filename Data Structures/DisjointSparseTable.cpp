const int mod = 764'854'400;
 
struct DST {
    int k, n;
    vector<vector<int>> left, right;
    
    DST(vector<int> & a) {
        n = (int)a.size(), k = log2(n) + 2;
        left.assign(k + 1, vector<int>(n));
        right.assign(k + 1, vector<int>(n));
        for(int j = 0; (1 << j) <= n; ++j) {
            int mask = (1 << j) - 1;
            int nw = 1; //default
            for(int i = 0; i < n; ++i) {
                left[j][i] = nw = 1LL * nw * a[i] % mod;//prefix value
                if((i & mask) == mask) nw = 1; //default
            }
            nw = 1; //default
            for(int i = n - 1; i >= 0; --i) {
                right[j][i] = nw = 1LL * nw * a[i] % mod;//prefix value
                if((i & mask) == 0) nw = 1; //default
            }
        }
    }
    int qry(int l, int r) {
        if(l == r) return left[0][l];
        int i = 31 - __builtin_clz(l ^ r);
        return 1LL * left[i][r] * right[i][l] % mod;
    }
};
