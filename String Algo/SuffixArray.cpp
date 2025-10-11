struct SuffixArray {
    string s;
    int n;
    vector<int> sa, rank, lcp, lg;
    vector<vector<int>> st;

    SuffixArray(string& text) : s(text), n(s.length()){
        bsa();
        blcpa();
        bst();
    }

    void bsa() {
        string a = s;
        a += "$";
        int n2 = a.size();

        sa.resize(n2);
        rank.resize(n2);
        vector<int> new_rank(n2);

        {
            vector<int> c(256, 0);
            for (int i = 0; i < n2; ++i) c[a[i]]++;
            for (int i = 1; i < 256; ++i) c[i] += c[i - 1];
            for (int i = n2 - 1; i >= 0; --i) sa[--c[a[i]]] = i;

            rank[sa[0]] = 0;
            for (int i = 1; i < n2; ++i) {
                rank[sa[i]] = rank[sa[i - 1]];
                if (a[sa[i]] != a[sa[i - 1]]) {
                    rank[sa[i]]++;
                }
            }
        }

        for (int k = 1; k < n2; k <<= 1) {
            vector<int> last(n2);
            for (int i = 0; i < n2; ++i) last[i] = (sa[i] - k + n2) % n2;

            vector<int> c(n2, 0);
            for (int pos : last) c[rank[pos]]++;
            for (int i = 1; i < n2; ++i) c[i] += c[i - 1];
            for (int i = n2 - 1; i >= 0; --i) sa[--c[rank[last[i]]]] = last[i];

            new_rank[sa[0]] = 0;
            for (int i = 1; i < n2; ++i) {
                new_rank[sa[i]] = new_rank[sa[i - 1]];
                pair<int, int> prev = {rank[sa[i - 1]], rank[(sa[i - 1] + k) % n2]};
                pair<int, int> curr = {rank[sa[i]], rank[(sa[i] + k) % n2]};
                if (curr != prev) {
                    new_rank[sa[i]]++;
                }
            }
            rank = new_rank;

            if (rank[sa[n2 - 1]] == n2 - 1) break;
        }

        sa.erase(sa.begin());

        rank.resize(n);
        for(int i = 0; i < n; ++i) {
            rank[sa[i]] = i;
        }
    }

    void blcpa() {
        if (n <= 1) return;
        lcp.resize(n - 1);
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                h = 0;
                continue;
            }

            int j = sa[rank[i] + 1];

            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;

            lcp[rank[i]] = h;

            if(h > 0) h--;
        }
    }

    void bst() {
        if (n <= 1) return;
        int len = n - 1;
        lg.resize(len + 1);
        lg[1] = 0;
        for (int i = 2; i <= len; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        int mx = lg.empty() ? -1 : lg.back();
        if (mx < 0) return;

        st.assign(mx + 1, vector<int>(len));
        
        if (!lcp.empty()) {
            st[0] = lcp;
        }

        for (int k = 1; k <= mx; k++) {
            for (int i = 0; i + (1 << k) <= len; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r)  {
        if (l > r) return n;
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }

    int getLCP(int i, int j)  {
        if (i == j) return n - i;

        int ri = rank[i];
        int rj = rank[j];

        if (ri > rj) swap(ri, rj);
        return query(ri, rj - 1);
    }
};
