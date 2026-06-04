struct eertree {
    vector<array<int,26>> to;
    vector<int> len, link, par, s;
    int n = 0, sz = 2, last = 0;

    eertree(int N) : to(N + 2), len(N + 2), link(N + 2),
                     par(N + 2), s(N + 1, -1) {
        for(auto &x : to) x.fill(0);
        len[1] = -1;
        link[0] = link[1] = 1;
    }

    int getlink(int v, int c) {
        while(s[n - len[v] - 1] != c) v = link[v];
        return v;
    }

    int add(char ch) {
        int c = ch - 'a';
        s[++n] = c;

        int v = getlink(last, c);

        if(!to[v][c]) {
            int u = sz++;
            len[u] = len[v] + 2;
            par[u] = v;
            link[u] = len[u] == 1 ? 0 : to[getlink(link[v], c)][c];
            to[v][c] = u;
        }

        return last = to[v][c];
    }

    int id(int v) {
        if(v == 0) return 0;   // EVEN
        if(v == 1) return -1;  // ODD
        return v - 1;
    }

    int distinct() { return sz - 2; }
};
