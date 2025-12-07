const int N = 1e5 + 5;
class MEX {
    bitset<N> mex;
    vector<int> f;
    MEX() : f(N, 0){
        mex.set();
    }
    void add(int x){
        if (x >= N) {
            return;
        }
        f[x]++;
        if (f[x] == 1) {
            mex.reset(x);
        }
    }
    void rmv(int x){
        if (x >= N) {
            return;
        }
        f[x]--;
        if (f[x] == 0) {
            mex.set(x);
        }
    }
    int qry(){
        return mex._Find_first();
    }
};
