struct Query {
    int l, r, idx;
};

int B = max(1, int(sqrt(n)));
vector<Query> qs(q);
for (int i = 0; i < q; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].idx = i;
}

sort(qs.begin(), qs.end(), [&](const Query &A, const Query &BQ){
    int b1 = A.l / B, b2 = BQ.l / B;
    if (b1 != b2) return b1 < b2;
    return (b1 & 1) ? (A.r > BQ.r) : (A.r < BQ.r);
});

vector<int> ans(q);
int curL = 1, curR = 0;
for (auto &Q : qs) {
    int L = Q.l, R = Q.r;
    while (curL > L) addl(a[--curL]);
    while (curR < R) addr(a[++curR]);
    while (curL < L) rmvl(a[curL++]);
    while (curR > R) rmvr(a[curR--]);
    ans[Q.idx] = curAns;
}
