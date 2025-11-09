struct min_st{
    int n;
    vector<int> lg;
    vector<vector<int>> st;
    void init(vector<int> &arr){
        n = (int)arr.size();
        lg.resize(n + 1, 0); lg[1] = 0;
        for(int i = 2;i <= n;i++){
            lg[i] = lg[i - 1];
            if(i == (1 << (lg[i] + 1))) lg[i]++;
        }
        int mx = lg[n];
        st.resize(mx + 1, vector<int>(n, 0));
        st[0] = arr;
        for(int k = 1;k <= mx;k++){
            for(int i = 0;i + (1 << k) <= n;i++){
                st[k][i] = min(st[k - 1][i] , st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    int getmin(int l, int r){
        int cur = lg[r - l + 1];
        return min(st[cur][l], st[cur][r - (1 << cur) + 1]);
    }
};
