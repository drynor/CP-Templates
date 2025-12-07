const int lg = 30;
struct basis {
    long long b[lg + 1] , cnt = 0;
    basis(){
        memset(b, 0,  sizeof(b));
    }
    basis &operator=(const basis &o){
        for(int i = 0;i <= lg;i++){
            b[i] = o.b[i];
        }
        cnt = o.cnt;
        return *this;
    }
    void clear(){
        memset(b , 0 , sizeof(b));
        cnt = 0;  
    }
    int reduce(int x){
        if(x == 0) return 0;
        for(int i = lg ; i >= 0 ; i--) {
            if((x & (1ll << i)) != 0) {
                x ^= b[i];
            }
        }
        return x;
    }
    bool add(int x){
        x = reduce(x);
        if(x == 0) return false;
        b[31 - __builtin_clz(x)] = x;
        cnt++;  
        return true;
    }
    void combine(basis &b2){
        if(cnt == lg + 1) return;
        for(int i = lg ; i >= 0 ; i--) {
            this->add(b2.b[i]);
        }
    }
    int max_xor(){
        int ret = 0;
        for(int i = lg ; i >= 0 ; i--){
            if((ret >> i) & 1) continue;
            ret ^= b[i];
        }
        return ret;
    }
    int countlarger(int x){
        if(this->reduce(x) != 0) assert(0);
        int ans = 0, left = cnt;
        int cur = 0;
        for(int i = lg ; i >= 0 ; i--) if(b[i] != 0) {
            int bit = ((x >> i)&1);
            int curbit = ((cur >> i)&1);
            if(bit == 0) {
                ans += (1ll << (left - 1));
            }
            if(bit != curbit)
                cur ^= b[i];
            left--;
        }
        return ans;
    }
    int getkth(int k) {
        assert(k < (1ll << cnt));
        int larger = (1ll << cnt) - k - 1;
        int cur = 0, curlarger = 0, left = cnt;
        for(int i = lg ; i >= 0 ; i--) if(b[i] != 0) {
            int bit = (cur >> i)&1;
            if(curlarger + (1ll << (left - 1)) <= larger) {
                curlarger += (1ll << (left - 1));
                if(bit == 1) cur ^= b[i];
            } else {
              if(bit == 0) cur ^= b[i];
            }
            left--;
        }
        return cur;
    }
};
