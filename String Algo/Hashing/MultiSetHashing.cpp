/*
You are given two (multi)sets A = {a_1, ...., a_n} and B = {b_1, ..., b_n}.
n <= 10^5 and each element is in the interval [0, MOD).
Determine if they are the same.

random integer r from the interval [0, MOD),
and compute the hash (r+a_1)(r+a_2)...(r+a_n).
This is a polynomial of r of degree n, so again from Schwartz-Zippel lemma,
the collision probability is at most n/MOD.
*/
void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n + 1), b(n + 1), pa(n + 1, 1), pb(n + 1, 1);
    for(int i = 1;i<=n;i++){
        cin >> a[i]; pa[i] = mul(pa[i-1], (r + a[i]));
    }
    for(int i = 1;i<=n;i++){
        cin >> b[i]; pb[i] = mul(pb[i-1], (r + b[i]));
    }
    while(q--){
        int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        if(divide(pa[r1], pa[l1 - 1]) == divide(pb[r2], pb[l2 - 1])){
            cout << "Yes" << Endl;
        }
        else cout << "No" << Endl;
    }
}
