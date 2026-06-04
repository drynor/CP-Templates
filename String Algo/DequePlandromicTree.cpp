struct eertree {
    eertree(int q) {
        q += 2;
        cnt = len = par = link = slink = vector(q, 0);
        to.resize(q);
        link[0] = slink[0] = 1;
        len[1] = -1;
    }

    template<bool back = 1>
    static int get(auto const& d, int idx) {
        if(idx >= size(d)) return -1;
        else if constexpr (back) return prev(end(d))[-idx];
        else return begin(d)[idx];
    }
    template<bool back = 1>
    static void push(auto &d, auto c) {
        if constexpr (back) d.push_back(c);
        else d.push_front(c);
    }
    template<bool back = 1>
    static void pop(auto &d) {
        if constexpr (back) d.pop_back();
        else d.pop_front();
    }

    template<bool back = 1>
    void add_letter(char c) {
        c -= 'a';
        push<back>(s, c);
        int pre = get<back>(states, 0);
        int last = make_to<back>(pre, c);
        active += !(cnt[last]++);
        int D = 2 + len[pre] - len[last];
        while(D + len[pre] <= len[last]) {
            pop<back>(states);
            if(!empty(states)) {
                pre = get<back>(states, 0);
                D += get<back>(diffs, 0);
                pop<back>(diffs);
            }
            else break;
        }
        if(!empty(states)) push<back>(diffs, D);
        push<back>(states, last);
    }
    template<bool back = 1>
    void pop_letter() {
        int last = get<back>(states, 0);
        active -= !(--cnt[last]);
        pop<back>(states);
        pop<back>(s);
        array cands = {pair{link[last], len[last] - len[link[last]]},
                       pair{par[last], 0}};
        for(auto [state, diff]: cands) {
            if(empty(states)) {
                states = {state};
                diffs = {diff};
            } else {
                int D = get<back>(diffs, 0) - diff;
                int pre = get<back>(states, 0);
                if(D + len[state] > len[pre]) {
                    push<back>(states, state);
                    pop<back>(diffs);
                    push<back>(diffs, D);
                    push<back>(diffs, diff);
                }
            }
        }
        pop<back>(diffs);
    }
    void add_letter(char c, bool back = 1) {
        back ? add_letter<1>(c) : add_letter<0>(c);
    }
    void pop_letter(bool back = 1) {
        back ? pop_letter<1>() : pop_letter<0>();
    }
    int distinct() { return active; }

    template<bool back = 1>
    int maxlen() { return len[get<back>(states, 0)]; }

    void pop_front() { pop_letter(0); }
    void pop_back() { pop_letter(1); }
    void push_front(char c) { add_letter(c, 0); }
    void push_back(char c) { add_letter(c, 1); }
    int longest_prefix_pal() { return maxlen<0>(); }
    int longest_suffix_pal() { return maxlen<1>(); }

    vector<array<int, 26>> to;
    vector<int32_t> len, link, slink, par, cnt;

    deque<char> s;
    deque<int> states = {0}, diffs;
    int sz = 2, active = 0;

    template<bool back = 1>
    int get_link(int v, char c) {
        while(c != get<back>(s, len[v] + 1)) {
            if(c == get<back>(s, len[link[v]] + 1)) v = link[v];
            else v = slink[v];
        }
        return v;
    }

    template<bool back = 1>
    int make_to(int last, char c) {
        last = get_link<back>(last, c);
        if(!to[last][c]) {
            int u = to[get_link<back>(link[last], c)][c];
            link[sz] = u;
            par[sz] = last;
            len[sz] = len[last] + 2;

            if(len[sz] - len[u] == len[u] - len[link[u]]) slink[sz] = slink[u];
            else slink[sz] = u;
            
            to[last][c] = sz++;
        }
        return to[last][c];
    }
};
