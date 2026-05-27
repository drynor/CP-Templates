// range DSU merge
const int LOG = 20;
void solve(){
    int n, m; cin >> n >> m;
    vector<dsu> ds(LOG, dsu(n + 1));
    while(m--){
        int i1, j1, i2, j2, len;
        cin >> i1 >> j1 >> i2 >> j2;
        // cut the range into powers of 2 Lazy
        len = j1 - i1 + 1;
        for(int bit = LOG - 1;bit>=0;bit--){
            if((len >> bit) & 1){
                ds[bit].unite(i1, i2);
                i1 += (1 << bit);
                i2 += (1 << bit);
            }
        }
    }

    //propegate the edges/unites down by power of 2
    for(int bit = LOG - 1;bit>=1;bit--){
        for(int i = 1;i<=n;i++){
            int leader = ds[bit].get(i);
            if(i == leader) continue;
            
            ds[bit-1].unite(leader, i);
            ds[bit-1].unite(leader + (1 << (bit - 1)), i + (1 << (bit - 1)));
        }
    }
    //count the number of components
    int ans = 0; for(int i = 1;i<=n;i++) ans += (i == ds[0].get(i)); cout << ans << endl;
}
