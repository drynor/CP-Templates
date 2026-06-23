template<typename node, typename update>
struct seg {
    vector<node> t;
    vector<bool> lazy;
    vector<update> us;
    int n;
    seg(int tn) {
        n = tn;
        t.resize(n * 4);
        lazy.resize(n * 4, false);
        us.resize(n * 4);
    }
    void apply(int i, int s, int e, update& u){
        if(s != e){
            lazy[i] = 1;
            us[i].combine(u, s, e);
        }
        u.apply(t[i], s, e);
    }
    void push(int i, int s, int e){
        if(lazy[i]){
            int m = (s + e) / 2;
            apply(2 * i, s, m, us[i]); 
            apply(2 * i + 1, m + 1, e, us[i]);
            us[i] = update();
            lazy[i] = 0;
        }
    }
    void upd(int s, int e, int i, int l, int r, update& u) {
        if(s > r || e < l) return;
        if(s >= l && e <= r){
            apply(i, s, e, u); return;
        }
        push(i, s, e);
        int m = (s + e) / 2;
        upd(s, m, 2 * i, l, r, u);
        upd(m + 1, e, 2 * i + 1, l, r, u);
        t[i].merge(t[2 * i], t[2 * i + 1]);
    }
    node qry(int s, int e, int i, int l, int r) {
        if (s > r || e < l)   return node();
        if (s >= l && e <= r) return t[i];
        push(i, s, e);
        int m = (s + e) / 2;
        node ln, rn, ans;
        ln = qry(s, m, 2 * i, l, r);
        rn = qry(m + 1, e, 2 * i + 1, l, r);
        ans.merge(ln, rn);
        return ans;
    }
    void upd(int l, int r, int val) {
        update nw = update(val);
        upd(0, n - 1, 1, l, r, nw);
    }
    node qry(int l, int r) {
        return qry(0, n - 1, 1, l, r);
    }
};
struct node1 {
    int sum = 0;
    void merge(node1 &l, node1 &r) {
        sum = l.sum + r.sum;
    }
};
struct upd1 {
    int val;
    upd1(int val1 = 0){
        val = val1;
    }
    void apply(node1 &a, int s, int e) {
        a.sum += val * (e - s + 1);
    }
    void combine(upd1& nw, int s, int e){
        val += nw.val;
    }
};
