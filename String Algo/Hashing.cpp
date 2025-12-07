int ms[] = {1073741987 , 1073743327 , 1073743427};
int bs[] = {43, 47, 53, 59, 61};

int b1 = bs[getrand(0 , 1)], b2 = bs[getrand(2, 4)], mod = ms[getrand(0 , 2)];

inline int add(int x,int y){x += y;if(x >= mod) x -= mod;return x;}
inline int sub(int x,int y){x -= y;if(x < 0) x += mod;return x;}
inline int mul(int x,int y){return (long long)x * y % mod;}

struct Hash{
    vector<pair<int,int>> pw, h;
    string s;
 
    void hash(string ts){
        s = ts;
        pw.assign(s.size() + 1, {1,1});
        h.assign(s.size() + 1, {0,0});
        for(int i = 0 ; i < s.size() ; i ++ ){
            h[i+1].f = add((s[i] - 'a' + 1), mul(h[i].f, b1));
            h[i+1].s = add((s[i] - 'a' + 1), mul(h[i].s, b2));
            pw[i+1].f = mul(pw[i].f, b1);
            pw[i+1].s = mul(pw[i].s, b2);
        }
    }
 
    pair<int,int> get(int l, int r){
        int h1, h2;
        h1 = sub(h[r].f, mul(h[l-1].f, pw[r-l+1].f));
        h2 = sub(h[r].s, mul(h[l-1].s, pw[r-l+1].s));
        return {h1, h2};
    }
 
    bool equal(Hash &o, int l1,int r1,int l2,int r2){
        if(r1 - l1 != r2 - l2) return false;
        return get(l1 , r1) == o.get(l2 , r2);
    }

    bool less(Hash &o,int l1,int r1,int l2,int r2){
        int l = 0, r = min(r2 - l2, r1 - l1), ans = -1, m;
 
        while(r >= l){
            m = ((l + r) >> 1);
            if(get(l1 , l1 + m) == o.get(l2 , l2 + m)) l = m + 1;
            else ans = m , r = m - 1;
        }
        if(ans == -1){
            return (r1 - l1) < (r2 - l2);
        }
        return s[l1 + ans - 1] < o.s[l2 + ans - 1];
    }
};
