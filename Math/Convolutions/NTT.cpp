/* NTT / polynomial convolution: conv(A, B)[k] = sum_{i+j=k} A[i] * B[j]
   Rule of thumb: put a value v at index v (as a count/indicator), convolve, read index = sum.

 1) Multiply two polynomials
    A[i] = coeff of x^i. conv(A, B) = A(x) * B(x). deg = deg A + deg B.

 2) Raise a polynomial to a power n
    Repeated squaring with conv, truncating to the needed degree each step.
    Counting use: P[v] = 1 if a single item may have value v -> P^n[s] = #ordered ways
    n items sum to s (e.g. n dice, allowed steps).

 3) Multiply two big integers
    Little-endian digits: A[i] = i-th digit from the right (base 10 or 1e4).
    conv, then carry left-to-right: c[i+1] += c[i] / base, c[i] %= base.
    Digit^2 * len must stay < mod (base 10, len 1e6 -> 8.1e7 < 998244353 ok).

 4) All pairs sums / differences
    A[v] = #elements equal to v (frequency array), same for B.
    conv(A, B)[s] = #pairs (i, j) with a_i + b_j = s.
    Same array, i != j: subtract A[s/2] when s even; unordered pairs: divide by 2.
    Differences a_i - b_j = d: reverse B around M (B'[M - v] = B[v]) -> read index M + d.

 5) All subarray sums
    Prefix sums P[0..n]; subarray sum = P[r] - P[l], l < r. Frequency array of P,
    convolve with its reverse (item 4) -> cnt[d] = #pairs with P[r] - P[l] = d.
    If all a_i > 0 then d > 0 iff l < r, so index M + d for d >= 1 is exactly the answer.

 6) All subsets sums
    #subsets with sum s = coeff of x^s in prod_i (1 + x^{a_i}).
    Multiply the n factors by divide & conquer (pair up, conv, repeat): O(S log^2).
    Only need "is sum s reachable"? use bitset shift-or instead, it is faster.

 7) Cyclic shift stuff
    Dot product of A with every cyclic shift of B: let BB = B + B, R = reverse(A).
    conv(R, BB)[n - 1 + k] = sum_i A[i] * B[(i + k) mod n]   for shift k in [0, n).
    Best rotation / cyclic pattern match = argmax over k.

 8) Counting & probability
    Independent random variables X, Y with distributions p[v], q[v]:
    distribution of X + Y is conv(p, q). Sum of n i.i.d. = p^n (item 2).
    Use a modular inverse of the denominators to keep everything in Z_mod.

 9) String matching (wildcards & Hamming distance)
    T text (len n), P pattern (len m). For each letter c: Tc[i] = [T[i]==c],
    Pc[j] = [P[m-1-j]==c] (pattern reversed). match[i+m-1] = sum_c conv(Tc, Pc)
    = #positions agreeing when P is placed at i; Hamming(i) = m - match.
    Wildcard '?' = value 0, letters = 1..26 as numbers t_i, p_j: P fits at i iff
    sum_j (t_{i+j} - p_j)^2 * t_{i+j} * p_j == 0, expand:
    conv(T^3, P) - 2 * conv(T^2, P^2) + conv(T, P^3) (P reversed), zero at index i+m-1.
*/

// NTT-friendly primes: mod = c * 2^k + 1. Max convolution length is 2^k.
//   mod           g   2^k    max len
//   998244353     3   2^23   8.3e6   (default)
//   167772161     3   2^25   3.3e7
//   469762049     3   2^26   6.7e7
//   1224736769    3   2^24   1.6e7
//   595591169     3   2^23   8.3e6
//   645922817     3   2^23   8.3e6
//   897581057     3   2^23   8.3e6
//   754974721    11   2^24   1.6e7
//   1004535809    3   2^21   2.0e6   (> 1e9, for 3-mod CRT)
// To switch: change `mod` and `G` below. Unknown mod: G = generator().
const int mod = 998244353, G = 3;
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
    static const int MOD = mod;
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
            int wlen = pw(G, (MOD - 1) / len);
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
