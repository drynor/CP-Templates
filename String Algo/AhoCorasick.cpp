struct AC {
    int N;
    vector<vector<int>> next, g;
    vector<int> link;
    // vector<string> str;
    AC() {
        N = 0; node();
    }
    int node() {
        next.emplace_back(26, 0);
        link.emplace_back(0);
        // str.emplace_back("");
        return N++;
    }
    void add(string s) {
        int u = 0;
        for (char c : s) {
            int i = c - 'a';
            if (!next[u][i]) {
                int v = node();
                // str[v] = str[u] + c;
                next[u][i] = v;
            }
            u = next[u][i];
        }
        return;
    }
    void compute() {
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();     
            for (int c = 0; c < 26; c++) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = (u ? next[link[u]][c] : 0);                    
                    q.push(v);
                }
            }
        } // g.resize(N); // for (int i = 1; i < N; i++) g[link[i]].push_back(i);
    }
    int adv(int u, char c) {
        return next[u][c - 'a'];
    }
};
