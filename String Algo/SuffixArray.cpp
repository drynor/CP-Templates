struct SA {
    string s;
    int n;
    vector<int> sa, rank, lcp;
    ST st;

    SA(string& text) : s(text), n(s.size()) {
        bsa(); blcpa(); bst();
    }

    void bsa() {
        string a = s + "$";
        int m = a.size();

        sa.resize(m);
        rank.resize(m);

        vector<int> nw(m), p(m), c(max(256, m), 0);

        for (char ch : a) c[ch]++;
        for (int i = 1; i < 256; i++) c[i] += c[i - 1];
        for (int i = m - 1; i >= 0; i--) sa[--c[a[i]]] = i;

        for (int i = 1; i < m; i++)
            rank[sa[i]] = rank[sa[i - 1]] + (a[sa[i]] != a[sa[i - 1]]);

        for (int k = 1; k < m; k <<= 1) {
            for (int i = 0; i < m; i++) p[i] = (sa[i] - k + m) % m;

            fill(c.begin(), c.begin() + m, 0);
            for (int x : p) c[rank[x]]++;
            for (int i = 1; i < m; i++) c[i] += c[i - 1];
            for (int i = m - 1; i >= 0; i--) sa[--c[rank[p[i]]]] = p[i];

            auto key = [&](int i) {
                return pair<int, int>{rank[i], rank[(i + k) % m]};
            };

            nw[sa[0]] = 0;
            for (int i = 1; i < m; i++)
                nw[sa[i]] = nw[sa[i - 1]] + (key(sa[i]) != key(sa[i - 1]));

            rank.swap(nw);

            if (rank[sa[m - 1]] == m - 1) break;
        }

        sa.erase(sa.begin());

        rank.resize(n);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
    }

    void blcpa() {
        lcp.assign(n - 1, 0);

        for (int i = 0, h = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                h = 0;
                continue;
            }

            int j = sa[rank[i] + 1];

            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;

            lcp[rank[i]] = h;
            if (h) h--;
        }
    }

    void bst() {
        if (!lcp.empty()) st.build(lcp);
    }

    int query(int l, int r) {
        return l > r ? n : st.query(l, r);
    }

    int getLCP(int i, int j) {
        if (i == j) return n - i;

        int ri = rank[i], rj = rank[j];
        if (ri > rj) swap(ri, rj);

        return query(ri, rj - 1);
    }
};
