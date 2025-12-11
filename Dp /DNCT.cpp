/*
Given an array of n elements, your task is to divide into k subarrays.
The cost of each subarray is the square of the sum of the values in the subarray.
What is the minimum total cost if you act optimally?
1 <= k <= n <= 3000
1 <= x_i <= 10^5
*/

const int N = 3010;
int a[N];
int p[N];
int dp[N][N];
 
void fun(int i, int l, int r, int optl, int optr){
    if(l > r) return;
 
    int m = l + (r - l) / 2;
    int best = 1e18;
    int ind = 1e18;
    for(int j = optl;j < min(optr + 1, m);j++){
        int cost = (p[m] - p[j]) * (p[m] - p[j]) + dp[j][i-1];
        if(cost < best){
            best = cost;
            ind = j;
        }
    }
    dp[m][i] = best;
    fun(i, l, m-1, optl, ind);
    fun(i, m+1, r, ind, optr);
}
 
void solve(){
    int n,k;cin >> n >> k;
    for(int i = 1;i<=n;i++){
        cin >> a[i];
        p[i] = p[i-1] + a[i];
    }
    dp[0][0] = 0;
    for(int i = 1;i<=n;i++){
        dp[i][0] = 1e18;
    }
    for(int i = 1;i<=k;i++){
        fun(i, 1, n, 0, n-1);
    }
    cout << dp[n][k] << endl;
}
