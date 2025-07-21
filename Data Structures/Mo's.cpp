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
      while (curL > L) add(a[--curL]);
      while (curR < R) add(a[++curR]);
      while (curL < L) remove_(a[curL++]);
      while (curR > R) remove_(a[curR--]);
      ans[Q.idx] = curAns;
  }

  for(int i = 0;i<q;i++){
      cout << ans[i] << " ";
  }
  cout << endl;
