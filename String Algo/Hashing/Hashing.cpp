mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<int>(l, r)(rng)

int ms[] = {1000000007, 1000000009, 1000000021, 1000000033,1000000087, 1000000093,
            1000000097, 1000000103, 1000000123, 1000000181, 1000000207, 1000000223};
int b1 = getrand(200, 1e9), b2 = getrand(200, 1e9), mod = ms[getrand(0 , 11)];

inline int add(int x,int y){return(x+=y)>=mod?x-mod:x;}
inline int sub(int x,int y){return(x-=y)<0?x+mod:x;}
inline int mul(int x,int y){return(long long)x*y%mod;}

struct Hash{
    int sz;
    vector<pair<int,int>> pw, h;
    string s;
 
    Hash(string ts) : s(ts), sz(ts.size()), pw(sz+1, {1, 1}), h(sz+1,{0, 0}) {
        for(int i = 0; i < sz; i++){
            h[i+1] = {
                add(s[i] - 'a' + 1, mul(h[i].f, b1)),
                add(s[i] - 'a' + 1, mul(h[i].s, b2))
            };
            pw[i+1] = {
                mul(pw[i].f, b1),
                mul(pw[i].s, b2)
            };
        }
    }
 
    pair<int,int> get(int l, int r){
        return {
            sub(h[r].f, mul(h[l-1].f, pw[r-l+1].f)),
            sub(h[r].s, mul(h[l-1].s, pw[r-l+1].s))
        };
    }
 
    bool equal(Hash&o,int l1,int r1,int l2,int r2){
        return r1 - l1 == r2 - l2 and get(l1,r1) == o.get(l2,r2);
    }

    bool less(Hash &o,int l1,int r1,int l2,int r2){
        int l = 0, r = min(r2 - l2, r1 - l1), ans = -1, m;
        
        while(r >= l){
            m = l + r >> 1;
            if(get(l1 , l1 + m) == o.get(l2 , l2 + m)) l = m + 1;
            else ans = m , r = m - 1;
        }
        return ans == -1 ? r1-l1 < r2-l2 : s[l1+ans-1] < o.s[l2+ans-1];
    }
};
