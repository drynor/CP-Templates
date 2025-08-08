struct AC {
    // Member Variables
    int N;                      // The total number of nodes in the automaton.
    int P;                      // The total number of patterns added.
    const int A = 26;           // The size of the alphabet (e.g., 'a'-'z').

    // Automaton Data Structures
    vector<vector<int>> next;   // The transition table of the automaton (the "goto" function).
                                // next[u][c] gives the node reached from node u on character c.
                                // Initially, it represents trie edges, but after `compute()`,
                                // it becomes a complete DFA transition table.

    vector<int> link;           // The suffix link for each node. link[u] points to the node
                                // representing the longest proper suffix of the string at u
                                // that is also a prefix in the dictionary. The root's link is 0.

    // Note: Other common AC vectors like `out` (pattern IDs ending at a node) and 
    // `out_link` (link to the next node with an output) are omitted in this specific version
    // for simplicity but are essential for a full pattern-matching implementation.

    /**
     * @brief Constructor for the Aho-Corasick automaton.
     */
    AC() : N(0), P(0) {
        // The automaton is born with a single node: the root (node 0).
        node(); 
    }

    /**
     * @brief Creates a new, empty node for the automaton.
     * @return The integer ID of the newly created node.
     */
    int node() {
        // A new node needs transitions for every character in the alphabet.
        // Initially, all transitions are set to 0 (the root), which signifies no path.
        next.emplace_back(A, 0);

        // A new node needs a suffix link. It's initialized to 0. The correct
        // value will be calculated during the `compute()` phase.
        link.emplace_back(0);

        // Return the ID of this new node, which is its index `N`, and then increment N.
        return N++;
    }

    /**
     * @brief Adds a pattern string to the trie structure.
     * @param T The pattern string to add.
     * @return The ID assigned to this new pattern.
     */
    int add_pattern(const string& T) {
        int u = 0; // Start traversal from the root node.
        for (char ch : T) {
            int c = ch - 'a'; // Convert character to alphabet index.
            if (!next[u][c]) {
                // If a path for this character doesn't exist from the current node 'u',
                // create a new node 'v' and set the transition.
                int v = node();
                next[u][c] = v;
            }
            // Move to the next node in the path.
            u = next[u][c];
        }
        // The pattern `T` ends at node `u`. We increment the pattern count and return
        // the new pattern's ID. In a full implementation, you would store this
        // ID in an `out` vector: `out[u].push_back(P)`.
        return P++;
    }

    /**
     * @brief Finalizes the automaton by building suffix links and the complete DFA.
     * * This crucial function transforms the initial trie into a full-fledged
     * Aho-Corasick automaton. It uses a Breadth-First Search (BFS) to compute
     * suffix links for all nodes and, importantly, fills in all missing
     * transitions in the `next` table to create the DFA.
     */
    void compute() {
        queue<int> q;
        // Start the BFS from the root's direct children. For these nodes (depth 1),
        // the suffix link is always the root (0).
        for (int c = 0; c < A; ++c) {
            if (next[0][c]) {
                q.push(next[0][c]);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();

            // For each node 'u', iterate through all possible characters.
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) {
                    // If there is NO direct trie edge from 'u' on character 'c':
                    // This is the magic of the DFA optimization. We "fill in" the missing
                    // transition by making it point to the same place the parent's suffix
                    // link would go on the same character. This pre-computes the fail-path.
                    next[u][c] = next[link[u]][c];
                } else {
                    // If there IS a direct trie edge to node 'v':
                    // We must compute the suffix link for 'v'. We do this by following
                    // the parent's ('u') suffix link and taking the same transition 'c'.
                    // The root's children always link back to the root.
                    link[v] = (u ? next[link[u]][c] : 0);
                    // Add 'v' to the queue to process its children later.
                    q.push(v);
                }
            }
        }
    }

    /**
     * @brief Advances the automaton one step from a given state on a character.
     * @param u The current node ID.
     * @param ch The character to transition on.
     * @return The ID of the next node.
     */
    int advance(int u, char ch) {
        // Because the `compute()` function has already built a complete DFA,
        // transitioning is a simple and fast O(1) table lookup. We don't need
        // to manually follow suffix links here; that logic is already baked
        // into the `next` table.
        return next[u][ch - 'a'];
    }
};
