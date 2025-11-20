struct ST2D {
    vector<vector<int>> st[22];
    void build(const vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        st[0] = a;
        
        for (int k = 1; (1 << k) <= min(n, m); k++) {
            int h = 1 << (k - 1);
            int rows = n - (1 << k) + 1, cols = m - (1 << k) + 1;
            st[k].assign(rows, vector<int>(cols));
            
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    st[k][i][j] = gcd(st[k-1][i][j], 
                                  gcd(st[k-1][i + h][j], 
                                  gcd(st[k-1][i][j + h], 
                                      st[k-1][i + h][j + h])));
                }
            }
        }
    }
    int query(int r, int c, int sz) {
        int k = __lg(sz);
        int d = sz - (1 << k);
        return gcd(st[k][r][c], 
               gcd(st[k][r + d][c], 
               gcd(st[k][r][c + d], 
                   st[k][r + d][c + d])));
    }
};
