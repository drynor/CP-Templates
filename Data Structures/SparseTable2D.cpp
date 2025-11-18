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

struct Sparse {
    int n, m, B = 21;
    vector<int> lg;
    vector<vector<array<int, B>>> table;
    Sparse(int _n, int _m) {
        n = _n, m = _m;
        lg.assign(max(n, m) + 3, 0);
        for (int i = 2; i < lg.size(); ++i) lg[i] = lg[i / 2] + 1;
        table.assign(n + 1, vector<array<int, B>>(m + 1));
    }
    void build(vector<vector<int>> &g) {
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) table[i][j][0] = g[i][j];
        for (int x = 1; x < B; ++x) {
            int len = (1ll << (x - 1));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (i + len * 2 > n || j + len * 2 > m) continue;
                    int a = table[i][j][x - 1];
                    int b = table[i + len][j][x - 1];
                    int c = table[i][j + len][x - 1];
                    int d = table[i + len][j + len][x - 1];
                    a = gcd(a, b);
                    a = gcd(a, gcd(c, d));
                    table[i][j][x] = a;
                }
            }
        }
    }
    int query(int x0, int y0, int sz) {
        int x = lg[sz];
        int x1 = x0 + sz - (1ll << x);
        int y1 = y0 + sz - (1ll << x);
        int a = table[x0][y0][x];
        int b = table[x1][y0][x];
        int c = table[x0][y1][x];
        int d = table[x1][y1][x];
        return gcd(gcd(a, b), gcd(c, d));
    }
};
