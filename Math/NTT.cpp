// 1) Multiply two polynomials
// 2) Raise a Polynomial to a power of n
// 3) Multiply two big integers
// 4) All pairs sums
// 5) All subarrays sums
// 6) All subsets sums
// 7) Cyclic shift stuffs
// 8) Counting & Probability
// 9) String matching (Wild Cards & Hamming Distance)

// NTT mods 998244353, 167772161, 469762049, 1224736769, 595591169, 645922817, 897581057
const int mod = ?;
int modpow(int b, int e) {
    int ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}
// Primitive Root of the mod of form 2^a * b + 1
int generator () {
    vector<int> fact;
    int phi = mod-1, n = phi;
    for (int i = 2;i*i <= n;i++) if (n % i == 0){
        fact.push_back(i);
        while (n % i == 0) n /= i;
    }
    if (n > 1) fact.push_back(n);
 
    for(int res = 2;res <= mod;res++){
        bool ok = true;
        for (size_t i = 0; i < fact.size() and ok; i++)
            ok &= modpow(res, phi / fact[i]) != 1;
        if(ok) return res;
    }
    return -1;
}

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
