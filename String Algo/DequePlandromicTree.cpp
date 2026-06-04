struct eertree {
    vector<array<int, 26>> to;
    vector<int> len, link, slink, par, cnt;
    deque<int> s, states = {0}, diffs;
    int sz = 2, active = 0;

    eertree(int q) : to(q + 2), len(q + 2), link(q + 2),
                     slink(q + 2), par(q + 2), cnt(q + 2) {
        link[0] = slink[0] = 1;
        len[1] = -1;
    }

    template<class D>
    static int get(const D& d, int i, bool back) {
        if(i >= (int)d.size()) return -1;
        return back ? d[(int)d.size() - 1 - i] : d[i];
    }

    template<class D, class T>
    static void push(D& d, T x, bool back) {
        if(back) d.pb(x);
        else d.pf(x);
    }

    template<class D>
    static void pop(D& d, bool back) {
        if(back) d.popb();
        else d.popf();
    }

    int get_link(int v, int c, bool back) {
        while(c != get(s, len[v] + 1, back)) {
            if(c == get(s, len[link[v]] + 1, back)) v = link[v];
            else v = slink[v];
        }
        return v;
    }

    int make_to(int last, int c, bool back) {
        last = get_link(last, c, back);

        if(!to[last][c]) {
            int u = to[get_link(link[last], c, back)][c];

            link[sz] = u;
            par[sz] = last;
            len[sz] = len[last] + 2;

            if(len[sz] - len[u] == len[u] - len[link[u]])
                slink[sz] = slink[u];
            else
                slink[sz] = u;

            to[last][c] = sz++;
        }

        return to[last][c];
    }

    void add(char ch, bool back = true) {
        int c = ch - 'a';
        push(s, c, back);

        int pre = get(states, 0, back);
        int last = make_to(pre, c, back);

        active += !(cnt[last]++);

        int D = 2 + len[pre] - len[last];

        while(D + len[pre] <= len[last]) {
            pop(states, back);

            if(states.empty()) break;

            pre = get(states, 0, back);
            D += get(diffs, 0, back);
            pop(diffs, back);
        }

        if(!states.empty()) push(diffs, D, back);
        push(states, last, back);
    }

    void pl(bool back = true) {
        int last = get(states, 0, back);

        active -= !(--cnt[last]);

        pop(states, back);
        pop(s, back);

        pair<int, int> cand[2] = {
            {link[last], len[last] - len[link[last]]},
            {par[last], 0}
        };

        for(auto [state, diff] : cand) {
            if(states.empty()) {
                states = {state};
                diffs = {diff};
            } else {
                int D = get(diffs, 0, back) - diff;
                int pre = get(states, 0, back);

                if(D + len[state] > len[pre]) {
                    push(states, state, back);
                    pop(diffs, back);
                    push(diffs, D, back);
                    push(diffs, diff, back);
                }
            }
        }

        pop(diffs, back);
    }

    void pb(char c) { add(c, true); }
    void pf(char c) { add(c, false); }

    void popb() { pl(true); }
    void popf() { pl(false); }

    int distinct() const { return active; }

    int maxlen(bool back = true) { return len[get(states, 0, back)]; }

    int longest_suffix_pal() { return maxlen(true); }
    int longest_prefix_pal() { return maxlen(false); }
};
