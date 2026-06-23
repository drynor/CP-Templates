const int N = 2e6;
int c[N][2], cnt[N], ptr = 1; // c->-1 cnt->0
struct trie {
    int root = 0;

    void upd(int x){
        cnt[root]++;

        int tmp = root;
        for(int bit = 31;bit>=0;bit--){
            if(c[tmp][x >> bit & 1] == -1) c[tmp][x >> bit & 1] = ptr++;

            tmp = c[tmp][x >> bit & 1];
            cnt[tmp]++;
        }
    }

    int qry(int x){ //
        if(cnt[root] == 0) return -1;

        int tmp = root, xr = 0;
        for(int bit = 31;bit>=0;bit--){
            if(cnt[c[tmp][x >> bit & 1 ^ 1]] <= 0){
                tmp = c[tmp][x >> bit & 1];
                if(x >> bit & 1) xr |= 1 << bit;
            }
            else{
                tmp = c[tmp][(x >> bit & 1) ^ 1];
                if(x >> bit & 1 ^ 1) xr |= 1 << bit;
            }
        }
        return x ^ xr;
    }
};
