class MEX {
    const int N = 1e5 + 5;
    bitset<N> mex;
    vector<int> freq;
 
public:
    MEX() : freq(N, 0) {
        mex.set();
    }
 
    void add(int x) {
        if (x >= N) {
            return;
        }
        freq[x]++;
        if (freq[x] == 1) {
            mex.reset(x);
        }
    }
 
    void remove(int x) {
        if (x >= N) {
            return;
        }
        freq[x]--;
        if (freq[x] == 0) {
            mex.set(x);
        }
    }
 
    int get_mex() {
        return mex._Find_first();
    }
};
