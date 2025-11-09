struct PalindromicTree {
private:
    // Internal node structure for the tree
    struct node {
        int nxt[26]; // Transitions to other nodes
        int len;     // Length of the palindrome
        int st, en;  // Start and end index of *first* occurrence
        int link;    // Suffix link to the longest proper palindromic suffix
        int cnt;     // Number of palindromic suffixes for this node
        long long oc; // Total occurrences of this palindrome in the string
        node() : len(0), st(0), en(0), link(0), cnt(0), oc(0) {
            memset(nxt, 0, sizeof(nxt));
        }
    };

    string s;           // The input string
    vector<node> t;     // The tree nodes
    int sz;             // Number of nodes
    int last;           // The node corresponding to the longest palindromic suffix
    
    // --- Pre-computed results for the public API ---
    long long totalPalindromes;
    int longestLen;
    int longestStart;
    int mostFreqLen;
    long long mostFreqCount;
    vector<int> palindromicSuffixesPerPosition;

    /**
     * @brief Extends the tree with the character at s[pos].
     * Internal helper function.
     */
    void extend(int pos) {
        int cur = last, curlen = 0;
        int ch = s[pos] - 'a';
        while (1) {
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
            cur = t[cur].link;
        }
        if (t[cur].nxt[ch]) {
            last = t[cur].nxt[ch];
            t[last].oc++;
            return;
        }
        sz++;
        last = sz;
        t[sz].oc = 1;
        t[sz].len = t[cur].len + 2;
        t[cur].nxt[ch] = sz;
        t[sz].en = pos;
        t[sz].st = pos - t[sz].len + 1;
        if (t[sz].len == 1) {
            t[sz].link = 2;
            t[sz].cnt = 1;
            return;
        }
        while (1) {
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[sz].link = t[cur].nxt[ch];
                break;
            }
        }
        t[sz].cnt = 1 + t[t[sz].link].cnt;
    }

    /**
     * @brief Calculates total occurrences by summing up from suffixes.
     * Internal helper function.
     */
    void calc_occurrences() {
        for (int i = sz; i >= 3; i--) t[t[i].link].oc += t[i].oc;
    }

public:
    /**
     * @brief Constructs the Palindromic Tree and computes all properties.
     * @param _s The input string.
     */
    PalindromicTree(string _s) {
        s = _s;
        int n = s.size();
        t.clear();
        t.resize(n + 9);
        sz = 2, last = 2;
        t[1].len = -1, t[1].link = 1;
        t[2].len = 0, t[2].link = 1;

        // --- Initialize result variables ---
        totalPalindromes = 0;
        longestLen = 0;
        longestStart = 0;
        mostFreqLen = 0;
        mostFreqCount = 0;
        palindromicSuffixesPerPosition.resize(n);

        // --- 1. Build the tree ---
        for (int i = 0; i < n; i++) {
            extend(i);
            
            // Store count of palindromic suffixes ending at i
            palindromicSuffixesPerPosition[i] = t[last].cnt;

            // Update longest palindrome found *so far*
            if (t[last].len > longestLen) {
                longestLen = t[last].len;
                longestStart = t[last].st;
            }
        }

        // --- 2. Calculate occurrences for all nodes ---
        calc_occurrences();

        // --- 3. Post-process to find total and most frequent ---
        for (int i = 3; i <= sz; i++) {
            // Add to total palindromes
            totalPalindromes += t[i].oc;

            // Check for most frequent
            if (t[i].oc > mostFreqCount) {
                mostFreqCount = t[i].oc;
                mostFreqLen = t[i].len;
            } else if (t[i].oc == mostFreqCount) {
                // Tie-break with the longer palindrome
                mostFreqLen = max(mostFreqLen, t[i].len);
            }
        }
    }

    // --- Public API Methods (Getters) ---

    /**
     * @brief Gets the total number of all palindromic substrings.
     * Includes duplicates (e.g., "aaa" has "a", "a", "a", "aa", "aa", "aaa").
     * @return Total count of palindromic substrings.
     */
    long long getTotalPalindromes() {
        return totalPalindromes;
    }

    /**
     * @brief Gets the number of *distinct* palindromic substrings.
     * (e.g., "aaa" has "a", "aa", "aaa" -> 3 distinct).
     * @return Count of distinct palindromic substrings.
     */
    int getDistinctPalindromes() {
        return sz - 2; // Subtract the two special root nodes
    }

    /**
     * @brief Gets the length of the longest palindromic substring.
     * @return The length.
     */
    int getLongestPalindromeLength() {
        return longestLen;
    }

    /**
     * @brief Gets the string of the *first occurrence* of the longest
     * palindromic substring.
     * @return The string.
     */
    string getLongestPalindromeString() {
        if (longestLen == 0) return "";
        return s.substr(longestStart, longestLen);
    }

    /**
     * @brief Gets properties of the most frequent palindromic substring.
     * In case of a tie in frequency, returns the one with the *greatest length*.
     * @return A pair {length, count}.
     */
    pair<int, long long> getMostFrequentPalindrome() {
        return {mostFreqLen, mostFreqCount};
    }

    /**
     * @brief Gets a vector where v[i] is the number of palindromic
     * substrings that *end* at index i.
     * @return A vector<int> of size N.
     */
    vector<int> getPalindromicSuffixCounts() {
        return palindromicSuffixesPerPosition;
    }

    // --- NEW METHOD ---
    /**
     * @brief Retrieves all distinct palindromic substrings.
     * @return A vector of strings, each being a unique palindrome.
     * The order is not guaranteed.
     */
    vector<string> getDistinctPalindromeStrings() {
        vector<string> result;
        for (int i = 3; i <= sz; i++) {
            // Reconstruct the string from its first occurrence
            result.push_back(s.substr(t[i].st, t[i].len));
        }
        return result;
    }
};
