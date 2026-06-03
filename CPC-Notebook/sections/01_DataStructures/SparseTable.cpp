/*
Algorithm: Sparse Table
When to use: Use for static idempotent range queries like min/max/gcd.
Indexing: 0-indexed unless noted
Complexity: See code and notes.
Common bugs: No updates.
*/

struct ST {
    vector<vector<int>> st;
    ST(vector<int>& a) {
        int n = a.size(), k = __lg(n);
        st.assign(k + 1, a);
        for (int j = 0; j < k; j++)
            for (int i = 0; i + (2 << j) <= n; i++)
                st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)]);
    }
    int query(int l, int r) {
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
