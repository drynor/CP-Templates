struct SQRT {
    int B;
    vector<int> f;
    vector<int> block;

    SQRT(const vector<int>& a) {
        int n = a.size();
        B = sqrt(n);
        f = a;
        
        block.assign((n + B - 1) / B, 0);
        for (int i = 0;i<n;i++){
        	block[i / B] += f[i];
        }
    }
    void update(int ind, int val) {
        block[ind / B] += val;
        f[ind] += val;
    }
    int query(int l, int r) {
        int ans = 0;
        while (l <= r && l % B != 0) {
            ans += f[l];
            l++;
        }
        while (l <= r && (r + 1) % B != 0) {
            ans += f[r];
            r--;
        }

        while (l <= r) {
            ans += block[l / B];
            l += B;
        }
        return ans;
    }
};
