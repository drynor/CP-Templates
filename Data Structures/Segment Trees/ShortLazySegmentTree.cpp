struct lazyseg {
    vector<int> t, us;
    vector<bool> lz;
    int n, def = 0;
    lazyseg(int tn) {
        n = tn;
        t.resize(n * 4, def);
        lz.resize(n * 4, false);
        us.resize(n * 4, 0);
    }
    void apply(int i, int s, int e, int u){
        lz[i] = true;
        us[i] += u;
        t[i] += u * (e - s + 1);
    }
    void push(int i, int s, int e){
        if(lz[i]){
            int m = (s + e) / 2;
            apply(2 * i, s, m, us[i]); 
            apply(2 * i + 1, m + 1, e, us[i]);
            us[i] = lz[i] = 0;
        }
    }
    void upd(int s, int e, int i, int l, int r, int u) {
        if(s > r || e < l) return;
        if(s >= l && e <= r){
            apply(i, s, e, u); return;
        }
        push(i, s, e);
        int m = (s + e) / 2;
        upd(s, m, 2 * i, l, r, u);
        upd(m + 1, e, 2 * i + 1, l, r, u);
        t[i] = t[2 * i] + t[2 * i + 1];
    }
    int qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l)   return def;
        if (s >= l && e <= r) return t[i];
        push(i, s, e);
        int m = (s + e) / 2;
        return qry(s, m, 2 * i, l, r) + qry(m + 1, e, 2 * i + 1, l, r);
    }
};
