// struct
template<typename node, typename update>
struct lazyseg {
    vector<node> t;
    vector<bool> lazy;
    vector<update> us;
    int n;
    lazyseg(int tn) {
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

// no struct
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

//old
template<typename Node, typename Update>
struct LazySGT {
    vector<Node> tree;
    vector<bool> lazy;
    vector<Update> updates;
    vector<int> arr;
    int n;
    int s;
    LazySGT(int a_len, vector<int> &a) {
        arr = a;
        n = a_len;
        s = 1;
        while(s < 2 * n){
            s = s << 1;
        }
        tree.resize(s); fill(ALL(tree), Node());
        lazy.resize(s); fill(ALL(lazy), false);
        updates.resize(s); fill(ALL(updates), Update());
        build(0, n - 1, 1);
    }
    void build(int start, int end, int index) {
        if (start == end)   {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    void pushdown(int index, int start, int end){
        if(lazy[index]){
            int mid = (start + end) / 2;
            apply(2 * index, start, mid, updates[index]); 
            apply(2 * index + 1, mid + 1, end, updates[index]);
            updates[index] = Update();
            lazy[index] = 0;
        }
    }
    void apply(int index, int start, int end, Update& u){
        if(start != end){
            lazy[index] = 1;
            updates[index].combine(u, start, end);
        }
        u.apply(tree[index], start, end);
 
    }
    void update(int start, int end, int index, int left, int right, Update& u) {
        if(start > right || end < left)
            return;
        if(start >= left && end <= right){
            apply(index, start, end, u);
            return;
        }
        pushdown(index, start, end);
        int mid = (start + end) / 2;
        update(start, mid, 2 * index, left, right, u);
        update(mid + 1, end, 2 * index + 1, left, right, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    Node query(int start, int end, int index, int left, int right) {
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right){
            return tree[index];
        }
        pushdown(index, start, end);
        int mid = (start + end) / 2;
        Node l, r, ans;
        l = query(start, mid, 2 * index, left, right);
        r = query(mid + 1, end, 2 * index + 1, left, right);
        ans.merge(l, r);
        return ans;
    }
    void make_update(int left, int right, int val) {
        Update new_update = Update(val);
        update(0, n - 1, 1, left, right, new_update);
    }
    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right);
    }
};
 
struct Node1 {
    int fsum;
    Node1() {
        fsum = 0;
    }
    Node1(int p1) {
        fsum = p1;
    }
    void merge(Node1 &l, Node1 &r) {
        fsum = l.fsum + r.fsum;
    }
};
 
 
struct Update1 {
    int val;
    Update1(){
        val = 0;
    }
    Update1(int val1) {
        val = val1;
    }
    void apply(Node1 &a, int start, int end) {
        a.fsum = val * (end - start + 1);
    }
    void combine(Update1& new_update, int start, int end){
        val = new_update.val;
    }
};
