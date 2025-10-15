struct state {
    int len, link;
    map<char, int> next;
};

struct sam {
    vector<state> st;
    int sz, last;
    sam(const string &s) {
        st.resize(s.length() * 2);
        st[0].len = 0; st[0].link = -1;
        sz = 1; last = 0;
        for(char c : s){
            extend(c);
        }
    }
    void extend(char c){
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
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
                st[nw].len = st[p].len + 1;
                st[nw].next = st[q].next;
                st[nw].link = st[q].link;
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
