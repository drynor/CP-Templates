// merge sort tree: count of elements <, ==, > val in a[l..r]. 0-based inclusive [l, r].
// 2n-1 nodes: root 0, left = i + 1, right = i + 2 * (m - s + 1). build O(n log n), qry O(log^2 n)
struct mst {
    int n;
    vector<vector<int>> t;
    mst(vector<int>& a) : n(a.size()), t(2 * n) { build(0, n - 1, 0, a); }

    void build(int s, int e, int i, vector<int>& a) {
        if (s == e) { t[i] = {a[s]}; return; }
        int m = (s + e) / 2, l = i + 1, r = i + 2 * (m - s + 1);
        build(s, m, l, a); build(m + 1, e, r, a);
        t[i].resize(t[l].size() + t[r].size());
        merge(ALL(t[l]), ALL(t[r]), t[i].begin());
    }
    int qry(int s, int e, int i, int l, int r, int val) {
        if (e < l || s > r) return 0;
        if (l <= s && e <= r) return calc(t[i], val);
        int m = (s + e) / 2;
        return qry(s, m, i + 1, l, r, val) + qry(m + 1, e, i + 2 * (m - s + 1), l, r, val);
    }
    int qry(int l, int r, int val) { return qry(0, n - 1, 0, l, r, val); }

    int calc(vector<int>& v, int val) { return greater_than(v, val); }   // pick which one qry answers
    int less_than(vector<int>& v, int val)    { return lower_bound(ALL(v), val) - v.begin(); }
    int greater_than(vector<int>& v, int val) { return v.end() - upper_bound(ALL(v), val); }
    int equal(vector<int>& v, int val)        { return upper_bound(ALL(v), val) - lower_bound(ALL(v), val); }
};
