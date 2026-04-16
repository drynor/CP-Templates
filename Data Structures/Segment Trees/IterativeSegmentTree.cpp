const int N = 1e6;
int n;
int tree[N * 2];

void build() {
    for(int i = n - 1; i > 0; i--) {
        tree[i] = max(tree[i<<1], tree[i<<1|1]);
    }
}

void upd(int i, int v) {
    for (tree[i += n] = v; i > 1; i >>= 1) {
        tree[i>>1] = max(tree[i], tree[i^1]);
    }
}

int qry(int l, int r) {
    int ans = -1e9;
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if (l & 1)    ans = max(res, tree[l++]);
        if (!(r & 1)) ans = max(res, tree[r--]);
    }
    return ans;
}
