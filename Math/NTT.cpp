struct NTT {
    static const int MOD = 998244353;
    static int pw(int a, int b) {
        int r = 1;
        for (; b; b >>= 1, a = 1LL * a * a % MOD) if (b & 1) r = 1LL * r * a % MOD;
        return r;
    }
    static void ntt(vector<int>& a, bool inv) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            int wlen = pw(3, (MOD - 1) / len);
            if (inv) wlen = pw(wlen, MOD - 2);
            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len / 2; j++) {
                    int u = a[i + j], v = 1LL * a[i + j + len / 2] * w % MOD;
                    a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                    a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                    w = 1LL * w * wlen % MOD;
                }
            }
        }
        if (inv) {
            int inv_n = pw(n, MOD - 2);
            for (auto& x : a) x = 1LL * x * inv_n % MOD;
        }
    }
    static vector<int> conv(vector<int> a, vector<int> b) {
        int s = a.size() + b.size() - 1, n = 1;
        while (n < s) n <<= 1;
        a.resize(n); b.resize(n);
        ntt(a, 0); ntt(b, 0);
        for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % MOD;
        ntt(a, 1); a.resize(s);
        return a;
    }
} ntt;
