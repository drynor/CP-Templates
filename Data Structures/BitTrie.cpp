struct node {
    int t[2]{-1, -1}, cnt = 0;
};
struct bitrie {
    const int LOG = 30;
    vector<node> trie;

    bitrie() : trie(1) {}
    void clear() { trie = {{}}; }

    void add(int val) {
        int x = 0;
        for (int i = LOG; ~i; i--) {
            trie[x].cnt++;
            int b = (val >> i) & 1;
            if (trie[x].t[b] == -1) {
                trie[x].t[b] = trie.size();
                trie.emplace_back();
            }
            x = trie[x].t[b];
        }
        trie[x].cnt++;
    }

    void rem(int val) {
        int x = 0;
        for (int i = LOG; ~i; i--) {
            trie[x].cnt--;
            x = trie[x].t[(val >> i) & 1];
        }
        trie[x].cnt--;
    }

    int max_xor(int val) { return _query(val, 1); }
    int min_xor(int val) { return _query(val, 0); }

    int _query(int val, bool type) {
        int x = 0, res = 0;
        for (int i = LOG; ~i; i--) {
            if (x == -1) {
                if (type) break;
                else return 2000000007;
            }
            int vbit = (val >> i) & 1;
            int pbit = vbit ^ type;

            if (trie[x].t[pbit] == -1 or !trie[trie[x].t[pbit]].cnt) {
                pbit ^= 1;
            }
            
            if ((pbit ^ vbit) == 1) {
                res |= (1 << i);
            }
            x = trie[x].t[pbit];
        }
        return res;
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
const int N = 2e6;
int ptr[N][2];
int cnt[N];

int pcnt = 1;

struct bitTrie {
    int root = 0;

    void add(int x){
        cnt[root]++;

        int tmp = root;
        for(int bit = 31;bit>=0;bit--){
            if(ptr[tmp][(x >> bit) & 1] == -1){
                ptr[tmp][(x >> bit) & 1] = pcnt++;
            }
            tmp = ptr[tmp][(x >> bit) & 1];
            cnt[tmp]++;
        }
    }

    int qry(int x){
        if(cnt[root] == 0) return -1;

        int tmp = root;
        int xr = 0;
        for(int bit = 31;bit>=0;bit--){
            if(cnt[ptr[tmp][((x >> bit) & 1) ^ 1]] <= 0){
                tmp = ptr[tmp][(x >> bit) & 1];
                if((x >> bit) & 1) xr |= (1 << bit);
            }
            else{
                tmp = ptr[tmp][((x >> bit) & 1) ^ 1];
                if(((x >> bit) & 1) ^ 1) xr |= (1 << bit);
            }
        }

        return x ^ xr;
    }

} bt;
