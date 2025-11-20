struct AC {
    int N, P, A = 26;
    vector<vector<int>> next;
    vector<int> link;
    vector<vector<int>> g;
    // vector<string> d_str;
    AC() {
        N = P = 0; node();
    }
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        // d_str.emplace_back("");
        return N++;
    }
    int add_pattern(const string& T) {
        int u = 0;
        for (char c : T) {
            int idx = c - 'a';
            if (!next[u][idx]) {
                int v = node();
                // d_str[v] = d_str[u] + c;
                next[u][idx] = v;
            }
            u = next[u][idx];
        }
        return P++;
    }
    void compute() {
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();     
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = (u ? next[link[u]][c] : 0);                    
                    q.push(v);
                }
            }
        } // g.resize(N); // for (int i = 1; i < N; i++) g[link[i]].push_back(i);
    }
    int advance(int u, char c) {
        return next[u][c - 'a'];
    }
};
