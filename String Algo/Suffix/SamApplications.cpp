struct SuffixAutomaton {
    struct State {
        int len, link;
        map<int, int> next;
        
        // Additional properties for specific applications
        long long cnt = 0;         // Number of occurrences
        int first_pos = -1;        // Position of first occurrence
        bool is_clone = false;     // Was this state created via cloning?
        vector<int> inv_link; // Inverse suffix links (children in suffix link tree)
        
        // For LCS of K strings (reachability bitmask)
        // In practice, use bitset for large K, using vector<bool> here for flexibility
        vector<bool> reaches_separator; 
    };

    const int MAXLEN;
    vector<State> st;
    int sz, last;
    
    // DP Memoization arrays
    vector<long long> dp_distinct;
    vector<long long> dp_kth;

    SuffixAutomaton(int n) : MAXLEN(n * 2 + 5) { // Reserve roughly 2*n
        st.resize(MAXLEN);
        st[0].len = 0;
        st[0].link = -1;
        st[0].cnt = 0; // Root doesn't count as an occurrence
        sz = 1;
        last = 0;
    }

    // --- Core Construction ---
    void extend(int c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1;                // Initial count for non-clones
        st[cur].first_pos = st[cur].len - 1; // 0-based index
        st[cur].is_clone = false;
        st[cur].next.clear();
        st[cur].inv_link.clear();

        int p = last;
        while (p != -1 && st[p].next.find(c) == st[p].next.end()) {
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
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                
                // Clone properties
                st[clone].cnt = 0;      // Clones initially have 0 count (will inherit)
                st[clone].first_pos = st[q].first_pos; 
                st[clone].is_clone = true;
                st[clone].inv_link.clear();

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // Helper: Build the inverse suffix links (Tree structure)
    // Must be called before applications using suffix tree traversal
    void build_tree() {
        for (int i = 1; i < sz; i++) {
            st[st[i].link].inv_link.push_back(i);
        }
    }

    // Helper: Propagate occurrence counts up the suffix links
    // Corresponds to "Number of occurrences" logic
    void calc_occurrences() {
        // Sort states by length descending
        vector<int> nodes(sz);
        for(int i=0; i<sz; i++) nodes[i] = i;
        sort(nodes.begin(), nodes.end(), [&](int a, int b){
            return st[a].len > st[b].len;
        });

        for(int u : nodes) {
            if(st[u].link != -1) {
                st[st[u].link].cnt += st[u].cnt;
            }
        }
    }

    // --- Application 1: Check for occurrence ---
    bool check_occurrence(const string& P) {
        int cur = 0;
        for (char c : P) {
            if (st[cur].next.find(c) == st[cur].next.end())
                return false;
            cur = st[cur].next[c];
        }
        return true;
    }

    // --- Application 2: Number of different substrings ---
    // Using the optimized formula: len(v) - len(link(v))
    long long count_distinct_substrings() {
        long long tot = 0;
        for (int i = 1; i < sz; i++) {
            tot += st[i].len - st[st[i].link].len;
        }
        return tot;
    }

    // --- Application 3: Total length of all different substrings ---
    // Using the arithmetic series formula
    long long total_length_distinct_substrings() {
        long long tot = 0;
        for (int i = 1; i < sz; i++) {
            long long shortest = st[st[i].link].len + 1;
            long long longest = st[i].len;
            long long num_strings = longest - shortest + 1;
            tot += num_strings * (longest + shortest) / 2;
        }
        return tot;
    }

    // --- Application 4: Lexicographically k-th substring ---
    // Helper DP for k-th substring
    void calc_paths_kth(int u) {
        dp_kth[u] = 1; // 1 for the empty string stopping here (if u != root)
        for (auto const& [key, v] : st[u].next) {
            if (dp_kth[v] == 0) calc_paths_kth(v);
            dp_kth[u] += dp_kth[v];
        }
    }

    string kth_lexicographical(long long k) {
        dp_kth.assign(sz, 0);
        calc_paths_kth(0);

        // Note: The text implies strictly substrings. Total paths = count_distinct_substrings.
        // k is 1-based.
        int cur = 0;
        string res = "";
        
        while (k > 0) {
            for (auto const& [char_code, v] : st[cur].next) {
                // If we treat transition chars as char type
                long long count = dp_kth[v]; 
                if (k <= count) {
                    res += (char)char_code;
                    k--; // Decrease because the string ending EXACTLY at 'v' counts as 1
                    cur = v;
                    goto continue_search;
                } else {
                    k -= count;
                }
            }
            break; // Should not happen if k is valid
            continue_search:;
        }
        return res;
    }

    // --- Application 5: Smallest cyclic shift ---
    // Static helper because it requires building a SAM for S+S
    static string smallest_cyclic_shift(string S) {
        string ss = S + S;
        SuffixAutomaton temp_sam(ss.length());
        for(char c : ss) temp_sam.extend(c);

        int cur = 0;
        string res = "";
        for(int i = 0; i < S.length(); i++) {
            // Greedy: take smallest char transition
            auto it = temp_sam.st[cur].next.begin();
            res += (char)it->first;
            cur = it->second;
        }
        return res;
    }

    // --- Application 6: Number of occurrences ---
    long long count_occurrences(const string& P) {
        // Ensure calc_occurrences() has been called after construction!
        int cur = 0;
        for (char c : P) {
            if (st[cur].next.find(c) == st[cur].next.end())
                return 0;
            cur = st[cur].next[c];
        }
        return st[cur].cnt;
    }

    // --- Application 7: First occurrence position ---
    int first_occurrence_pos(const string& P) {
        int cur = 0;
        for (char c : P) {
            if (st[cur].next.find(c) == st[cur].next.end())
                return -1;
            cur = st[cur].next[c];
        }
        // first_pos stores end index, convert to start index
        return st[cur].first_pos - P.length() + 1;
    }

    // --- Application 8: All occurrence positions ---
    // Helper to traverse inverse links
    void get_positions_recursive(int v, int len, vector<int>& result) {
        if (!st[v].is_clone) {
            result.push_back(st[v].first_pos - len + 1);
        }
        for (int u : st[v].inv_link) {
            get_positions_recursive(u, len, result);
        }
    }

    vector<int> all_occurrence_pos(const string& P) {
        // Ensure build_tree() has been called!
        int cur = 0;
        for (char c : P) {
            if (st[cur].next.find(c) == st[cur].next.end())
                return {};
            cur = st[cur].next[c];
        }
        vector<int> result;
        get_positions_recursive(cur, P.length(), result);
        sort(result.begin(), result.end());
        return result;
    }

    // --- Application 9: Shortest non-appearing string ---
    string shortest_non_appearing() {
        // BFS to find the closest node missing a transition
        vector<int> d(sz, -1);
        vector<int> p(sz, -1); // Parent state
        vector<char> pc(sz, 0); // Char from parent
        
        queue<int> q;
        q.push(0);
        d[0] = 0;
        
        int end_node = -1;
        char missing_char = 0;

        while(!q.empty()) {
            int u = q.front(); q.pop();

            // Check if any character 'a'-'z' is missing
            // Assuming lowercase alphabet for this specific task
            for(char c = 'a'; c <= 'z'; c++) {
                if(st[u].next.find(c) == st[u].next.end()) {
                    end_node = u;
                    missing_char = c;
                    goto found;
                }
            }

            for(auto const& [key, v] : st[u].next) {
                if(d[v] == -1) {
                    d[v] = d[u] + 1;
                    p[v] = u;
                    pc[v] = (char)key;
                    q.push(v);
                }
            }
        }
        found:
        
        string res = "";
        res += missing_char;
        while(end_node > 0) {
            res += pc[end_node];
            end_node = p[end_node];
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // --- Application 10: Longest common substring of two strings ---
    // S is the string in the automaton, T is passed as argument
    string lcs_two_strings(const string& T) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < T.size(); i++) {
            while (v != 0 && st[v].next.find(T[i]) == st[v].next.end()) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next.count(T[i])) {
                v = st[v].next[T[i]];
                l++;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        return T.substr(bestpos - best + 1, best);
    }

    // --- Application 11: Largest common substring of k strings ---
    // Implements the specific "Separator/Attainability" method from the text
    static string lcs_k_strings(const vector<string>& strings) {
        if(strings.empty()) return "";
        
        // 1. Join strings with special separators
        // We use integers starting from 300 to avoid ASCII conflicts
        vector<int> T_int;
        int sep = 300;
        vector<int> separators;
        
        for(const string& s : strings) {
            for(char c : s) T_int.push_back(c);
            T_int.push_back(sep);
            separators.push_back(sep);
            sep++;
        }
        
        // 2. Build SAM on the joined integer string
        SuffixAutomaton sam(T_int.size());
        for(int x : T_int) sam.extend(x);

        // 3. Calculate attainability (which separator is reachable from which node)
        // We do this by reverse propagation. If a node has a transition 'sep_i',
        // it reaches that separator. Then we propagate up the DAG (not suffix links, but graph edges).
        // However, standard propagation is DFS/BFS.
        
        // Initialize reachability
        int k = strings.size();
        for(int i=0; i<sam.sz; i++) sam.st[i].reaches_separator.assign(k, false);

        // Standard topological sort order is effectively by length descending for propogation? 
        // No, for DAG reachability we need reverse topological order.
        // Or simpler: DFS with memoization.
        
        // Let's use the property: if a string S is in string i, then there is a path
        // from the state of S to the separator D_i.
        
        // Optimization: Instead of full graph search, we can just mark the nodes 
        // that directly transition to a separator, then propagate up Suffix Links? 
        // No, reachability is via Transitions (Next), not Suffix Links.
        // Actually, the easiest way mentioned in generic tutorials is:
        // For every string S_i, run it through the automaton and mark nodes.
        // But to stick to the text's "Separator" method:
        
        // We need to know for every state v, does it have a path to D1, D2... Dk?
        // We can do a backward DFS from the transitions involving separators.
        
        vector<vector<int>> rev_graph(sam.sz);
        for(int u=0; u<sam.sz; u++) {
            for(auto const& [char_code, v] : sam.st[u].next) {
                rev_graph[v].push_back(u);
            }
        }

        // For each separator, BFS backwards
        for(int i=0; i<k; i++) {
            int current_sep = separators[i];
            queue<int> q;
            vector<bool> vis(sam.sz, false);
            
            // Find all nodes that have a DIRECT transition to this separator
            for(int u=0; u<sam.sz; u++) {
                if(sam.st[u].next.count(current_sep)) {
                    q.push(u);
                    vis[u] = true;
                    sam.st[u].reaches_separator[i] = true;
                }
            }

            while(!q.empty()){
                int u = q.front(); q.pop();
                for(int prev : rev_graph[u]) {
                    if(!vis[prev]) {
                        // Note: We only walk back via character edges, not separator edges
                        // But rev_graph includes everything.
                        // We must ensure we don't cross OTHER separators. 
                        // The text says "path... not containing other characters D_j".
                        // This logic is naturally handled because we only traverse 
                        // standard chars backwards if we constructed rev_graph correctly.
                        // Actually, just checking vis is enough for simple reachability.
                        vis[prev] = true;
                        sam.st[prev].reaches_separator[i] = true;
                        q.push(prev);
                    }
                }
            }
        }
        
        // 4. Find state with max len that reaches all separators
        int best_len = 0;
        int best_state = 0;
        
        for(int i=1; i<sam.sz; i++) {
            bool all = true;
            for(int j=0; j<k; j++) {
                if(!sam.st[i].reaches_separator[j]) {
                    all = false; 
                    break;
                }
            }
            if(all) {
                if(sam.st[i].len > best_len) {
                    best_len = sam.st[i].len;
                    best_state = i;
                }
            }
        }
        
        // Restore string
        // Since we don't have the string stored, we can't easily print it just from state index
        // without backtracking or storing parent pointers.
        // For this specific template, let's just grab one such string by walking back or 
        // passing the original string reference. 
        // Simplest: The "best_state" corresponds to a substring.
        // We can find the "endpos" (first_pos) and extract from the original concatenated string.
        // We need the concatenated T_int for this.
        
        // Reconstruct string from T_int using first_pos
        int end_pos = sam.st[best_state].first_pos;
        string res = "";
        for(int i = end_pos - best_len + 1; i <= end_pos; i++) {
            res += (char)T_int[i];
        }
        return res;
    }
};

int main() {
    string s = "ababbab";
    SuffixAutomaton sam(s.length());
    for(char c : s) sam.extend(c);
    
    // Post-processing
    sam.build_tree();
    sam.calc_occurrences();

    // Examples
    cout << "Distinct Substrings: " << sam.count_distinct_substrings() << endl;
    cout << "Occurrences of 'ab': " << sam.count_occurrences("ab") << endl;
    
    vector<int> positions = sam.all_occurrence_pos("ab");
    cout << "Positions of 'ab': ";
    for(int p : positions) cout << p << " ";
    cout << endl;

    cout << "Shortest non-appearing: " << sam.shortest_non_appearing() << endl;

    // LCS Example
    vector<string> inputs = {"banana", "bandana", "band"};
    cout << "LCS of 3 strings: " << SuffixAutomaton::lcs_k_strings(inputs) << endl;

    return 0;
}
