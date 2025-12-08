struct DAC {
    vector<string> li[20];
    AC ac[20]; 
    
    void clear() {
        for(int i = 0; i < 20; i++) {
            li[i].clear();
            ac[i].clear();
        }
    }
    
    DAC() {
        clear();
    }
 
    void add(string s) {
        int pos = 0;
        for(int l = 0; l < 20; l++) {
            if(li[l].empty()) {
                pos = l;
                break;
            }
        }
        
        li[pos].pb(s);
        ac[pos].add(s);
        
        for(int bef = 0; bef < pos; bef++) {
            for(const string& s2 : li[bef]) {
                li[pos].pb(s2);
                ac[pos].add(s2);
            }
            li[bef].clear();
            ac[bef].clear();
        }
        ac[pos].compute();
    }
    
    int qry(const string& s) {
        int ans = 0;
        for(int l = 0; l < 20; l++) {
            if (!li[l].empty()) {
                ans += ac[l].qry(s);
            }
        }
        return ans;
    }
};
