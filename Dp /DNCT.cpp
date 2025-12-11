/* Given an array of n elements, your task is to divide into k subarrays.
The cost of each subarray is the square of the sum of the values in the subarray.
What is the minimum total cost if you act optimally?
1 <= k <= n <= 3000
1 <= x_i <= 10^5 */
int N = 3010, a[N], p[N], dp[N][N];
void fun(int i, int l, int r, int optl, int optr){
    if(l > r) return;
    int m = l + (r - l) / 2;
    int best = 1e18, ind = 1e18;
    for(int j = optl;j < min(optr + 1, m);j++){
        int cost = (p[m] - p[j]) * (p[m] - p[j]) + dp[j][i-1];
        if(cost < best){ best = cost; ind = j; }
    }
    dp[m][i] = best; fun(i, l, m-1, optl, ind); fun(i, m+1, r, ind, optr);
}
void solve(){
    int n,k;cin >> n >> k;
    for(int i = 1;i<=n;i++){cin >> a[i]; p[i] = p[i-1] + a[i];}
    dp[0][0] = 0;
    for(int i = 1;i<=n;i++) dp[i][0] = 1e18;
    for(int i = 1;i<=k;i++) fun(i, 1, n, 0, n-1);
    cout << dp[n][k] << endl;
}
int count_numbers_has_ith_bit(int n, int k) { 
    ++n; 
    int d = ( 1LL << (k + 1) ), p = (1LL << k); 
    return n / d * p + max(0LL, n % d - p); 
} 
int highest_bit(int x) { 
    int t = 63 - __builtin_clzll(x); 
    return (1LL << t); 
} 
int lowest_bit(int x) { 
    int t = __builtin_ctzll(x); 
    return (1LL << t); 
} 
// loop through submasks 
for (int j = mask; j; j = (j - 1) & mask)

int xor_range(int n) { // from 1 to n 
    if (n % 4 == 0) return n; 
    if (n % 4 == 1) return 1; 
    if (n % 4 == 2) return n + 1; 
    return 0; 
} 
 
int odd_xor(int n) { 
    if (n % 2 == 0) return ((xor_range(n)) ^ (2LL * xor_range(n / 2LL))); 
    else return ((xor_range(n)) ^ (2LL * xor_range((n - 1LL) / 2LL))); 
} 
 
int odd_xor_range(int l, int r) { return odd_xor(l - 1) ^ odd_xor(r); } 
 
int even_xor_range(int l, int r) { 
    int xor_r = 2LL * xor_range(r / 2LL); 
    int xor_l = 2LL * xor_range((l - 1LL) / 2LL); 
    return (xor_l ^ xor_r); 
}
