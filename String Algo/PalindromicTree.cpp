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


struct eertree {
    // ============================================================
    //  Node Meaning
    // ============================================================
    //
    // node 0 = EVEN root, length 0
    // node 1 = ODD root,  length -1
    // real palindrome nodes start from 2
    //
    // len[v]       = length of palindrome represented by node v
    // link[v]      = suffix link of v
    // par[v]       = parent after removing first and last chars
    // to[v][c]     = transition by adding char c to both ends
    //
    // last         = node of longest palindromic suffix of current string
    // sz           = number of nodes currently used
    // n            = current string length, 1-indexed inside arr
    //

    vector<array<int, 26>> to;
    vector<int> len, link, par, arr;

    // dp[v] = number of palindromic suffixes in suffix-link chain of v
    vector<int> dp;

    // firstStart[v] = first starting position of palindrome v in str
    vector<int> firstStart;

    // endOcc[v] = how many times v appeared as longest suffix while building
    // occ[v]    = total occurrences after finalize()
    vector<long long> endOcc, occ;

    string str;

    int n = 0;
    int sz = 2;
    int last = 0;

    bool finalized = false;

    // ============================================================
    //  Extra maintained answers
    // ============================================================

    long long totalPalindromes = 0; // all palindromic substrings, with duplicates

    int longestLen = 0;
    int longestStart = 0;

    vector<int> palSuffixCnt; // palindromic substrings ending at each position
    vector<int> longestEndAt; // longest palindrome ending at each position

    // ============================================================
    //  Constructor
    // ============================================================

    eertree(int N) :
        to(N + 2),
        len(N + 2),
        link(N + 2),
        par(N + 2),
        arr(N + 1, -1),
        dp(N + 2),
        firstStart(N + 2),
        endOcc(N + 2),
        occ(N + 2) {

        for(auto &x : to) x.fill(0);

        len[0] = 0;    // EVEN root
        len[1] = -1;   // ODD root

        link[0] = 1;
        link[1] = 1;
    }

    // ============================================================
    //  Internal helper
    // ============================================================
    //
    // Finds the largest suffix palindrome of current string
    // that can be extended by character c.
    //

    int getlink(int v, int c) {
        while(arr[n - len[v] - 1] != c)
            v = link[v];
        return v;
    }

    // ============================================================
    //  Add one character
    // ============================================================
    //
    // Returns the node representing the longest palindromic suffix
    // after adding ch.
    //

    int add(char ch) {
        finalized = false;

        int c = ch - 'a';

        str += ch;
        arr[++n] = c;

        int v = getlink(last, c);

        if(!to[v][c]) {
            int u = sz++;

            len[u] = len[v] + 2;
            par[u] = v;

            if(len[u] == 1)
                link[u] = 0;
            else
                link[u] = to[getlink(link[v], c)][c];

            dp[u] = 1 + dp[link[u]];
            firstStart[u] = n - len[u];

            to[v][c] = u;
        }

        last = to[v][c];

        endOcc[last]++;

        totalPalindromes += dp[last];
        palSuffixCnt.push_back(dp[last]);
        longestEndAt.push_back(len[last]);

        if(len[last] > longestLen) {
            longestLen = len[last];
            longestStart = n - len[last];
        }

        return last;
    }

    // ============================================================
    //  Build from full string
    // ============================================================

    void build(const string &s) {
        for(char c : s)
            add(c);
    }

    // ============================================================
    //  Finalize occurrence counts
    // ============================================================
    //
    // Needed before asking frequency-related questions.
    //
    // After this:
    // occ[v] = number of occurrences of palindrome node v in the string.
    //

    void finalize() {
        if(finalized) return;
        finalized = true;

        occ = endOcc;

        for(int v = sz - 1; v >= 2; v--)
            occ[link[v]] += occ[v];
    }

    // ============================================================
    //  Node ID helper
    // ============================================================
    //
    // Useful for problems that want:
    // EVEN = 0
    // ODD  = -1
    // real palindromes = 1, 2, 3, ...
    //

    int id(int v) {
        if(v == 0) return 0;
        if(v == 1) return -1;
        return v - 1;
    }

    // ============================================================
    //  Basic getters
    // ============================================================

    int getDistinctPalindromes() {
        return sz - 2;
    }

    long long getTotalPalindromes() {
        return totalPalindromes;
    }

    int getLongestPalindromeLength() {
        return longestLen;
    }

    string getLongestPalindromeString() {
        if(longestLen == 0) return "";
        return str.substr(longestStart, longestLen);
    }

    int getLongestSuffixPalindromeLength() {
        return len[last];
    }

    int getLongestSuffixPalindromeNode() {
        return last;
    }

    // ============================================================
    //  Per-position getters
    // ============================================================

    vector<int> getPalindromicSuffixCounts() {
        return palSuffixCnt;
    }

    vector<int> getLongestPalindromeLengthAtEachPosition() {
        return longestEndAt;
    }

    // ============================================================
    //  Frequency getters
    // ============================================================
    //
    // These call finalize() automatically.
    //

    long long getOccurrence(int v) {
        finalize();
        return occ[v];
    }

    pair<int, long long> getMostFrequentPalindrome() {
        finalize();

        int bestLen = 0;
        long long bestCnt = 0;

        for(int v = 2; v < sz; v++) {
            if(occ[v] > bestCnt || (occ[v] == bestCnt && len[v] > bestLen)) {
                bestCnt = occ[v];
                bestLen = len[v];
            }
        }

        return {bestLen, bestCnt};
    }

    // ============================================================
    //  String reconstruction getters
    // ============================================================

    string getNodeString(int v) {
        return str.substr(firstStart[v], len[v]);
    }

    vector<string> getDistinctPalindromeStrings() {
        vector<string> res;

        for(int v = 2; v < sz; v++)
            res.push_back(getNodeString(v));

        return res;
    }

    // ============================================================
    //  Raw node property getters
    // ============================================================

    int getParent(int v) {
        return par[v];
    }

    int getSuffixLink(int v) {
        return link[v];
    }

    int getLength(int v) {
        return len[v];
    }
};
