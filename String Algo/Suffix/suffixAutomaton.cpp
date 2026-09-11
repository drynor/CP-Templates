struct sam {
    struct state {
        int len, link;
        map<char, int> next;
    };
    
    vector<state> st;
    int sz, last;
    sam(string &s) : st(s.size() * 2), sz(1), last(0) {
        st[0] = {0, -1, {}};
        for(char c : s) extend(c);
    }
    void extend(char c){
        int cur = sz++, p = last;
        st[cur].len = st[last].len + 1;

        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int nw = sz++;
                st[nw] = {st[p].len+1, st[q].link, st[q].next};
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = nw;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = nw;
            }
        }
        last = cur;
    }
};
