struct FWHT {
    static const int MOD = 1e9 + 7;

    static int add(int a, int b) { return (a + b) % MOD; }
    static int sub(int a, int b) { return (a - b + MOD) % MOD; }
    static int mul(long long a, long long b) { return (a * b) % MOD; }

    static int power(int a, long long b) {
        int res = 1; a %= MOD;
        while (b > 0) {
            if (b & 1) res = mul(res, a);
            a = mul(a, a);
            b >>= 1;
        } return res;
    }

    // flag: 0 = OR, 1 = AND, 2 = XOR
    void transform(vector<int>& a, bool inv, int flag) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    int u = a[i + j], v = a[i + j + len];
                    if (flag == 0) { // OR
                        if (!inv) a[i + j + len] = add(v, u);
                        else a[i + j + len] = sub(v, u);
                    } else if (flag == 1) { // AND
                        if (!inv) a[i + j] = add(u, v);
                        else a[i + j] = sub(u, v);
                    } else { // XOR
                        a[i + j] = add(u, v);
                        a[i + j + len] = sub(u, v);
                    }
                }
            }
        }
        if (flag == 2 && inv) {
            int inv_n = power(n, MOD - 2);
            for (int& x : a) x = mul(x, inv_n);
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b, int flag) {
        int n = 1;
        while (n < max(a.size(), b.size())) n <<= 1;
        a.resize(n); b.resize(n);

        transform(a, false, flag);
        transform(b, false, flag);
        for (int i = 0; i < n; i++) a[i] = mul(a[i], b[i]);
        transform(a, true, flag);
        return a;
    }
} fwht;
