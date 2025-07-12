int base1 = 26, base2 = 27, mod = 1e9 + 7;

inline int add(int x,int y){x += y;if(x >= mod) x -= mod;return x;}
inline int sub(int x,int y){x -= y;if(x < 0) x += mod;return x;}
inline int mul(int x,int y){return (long long)x * y % mod;}

struct Hash{
    vector< pair<int,int> > pow , hashes ;
    string s;
 
    void hash (string s){
        this->s = s;
        pow.assign( s.size() + 1 , {1,1} ) ;
        hashes.assign( s.size() + 1, {0,0} ) ;
        for(int i = 0 ; i < s.size() ; i ++ ){
            hashes[i+1].f = add( ( s[i] - 'a' + 1 ), mul( hashes[i].f , base1 )) ;
            hashes[i+1].s = add( ( s[i] - 'a' + 1 ) , mul( hashes[i].s , base2 )) ;
            pow[i+1].f = mul( pow[i].f , base1 ) ;
            pow[i+1].s = mul( pow[i].s , base2 ) ;
        }
 
    }
 
    pair<int,int> get(int l, int r){
        int hash1 , hash2 ;
 
        hash1 = sub(hashes[r].f , mul(hashes[l-1].f , pow[r-l+1].f )) ;
        hash2 = sub(hashes[r].s , mul(hashes[l-1].s , pow[r-l+1].s ) ) ;
 
        return { hash1 , hash2 } ;
    }

    bool equal(Hash &other, int l1,int r1,int l2,int r2){
        if(r1 - l1 != r2 - l2) return false;
        return get(l1 , r1) == other.get(l2 , r2);
    }

    bool less(Hash &other,int l1,int r1,int l2,int r2){
        int low = 0 , high = min(r2 - l2, r1 - l1) , res = -1 , mid;

        while(high >= low){
            mid = ((low + high) >> 1);
            if(get(l1 , l1 + mid) == other.get(l2 , l2 + mid))
                low = mid + 1;
            else 
                res = mid , high = mid - 1;
        }
        if(res == -1){
            return (r1 - l1) < (r2 - l2);
        }
        return s[l1 + res - 1] < other.s[l2 + res - 1];
    }
};
