struct seg {
    struct node {
        int sum = 0;
        node *left = nullptr, *right = nullptr;

        node(int s){
            sum = s;
        }
        node(node* l, node* r){
            left = l; right = r;
            if (l) sum += l->sum;
            if (r) sum += r->sum;
        }
    };
    int sz;
    vector<node*> roots;

    seg(const vector<int>& a) {
        sz = a.size();
        roots.pb(build(a, 0, sz - 1));
    }
    node* build(const vector<int>& a, int tl, int tr) {
        if(tl == tr) return new node(a[tl]);

        int tm = tl + (tr - tl) / 2;
        return new node(build(a, tl, tm), build(a, tm + 1, tr));
    }

    int upd(int ver, int pos, int val) {
        node* root = upd(roots[ver], 0, sz - 1, pos, val);
        roots.pb(root);
        return roots.size() - 1;
    }
    node* upd(node* pn, int tl, int tr, int pos, int val) {
        if(tl == tr) return new node(val);

        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            return new node(upd(pn->left, tl, tm, pos, val), pn->right);
        } else {
            return new node(pn->left, upd(pn->right, tm + 1, tr, pos, val));
        }
    }

    int qry(int ver, int l, int r) {
        return qry(roots[ver], 0, sz - 1, l, r);
    }
    int qry(node* cn, int tl, int tr, int l, int r) {
        if (tl > r || tr < l || !cn) return 0;
        if (tl >= l && tr <= r)        return cn->sum;
        
        int tm = tl + (tr - tl) / 2;
        return qry(cn->left, tl, tm, l, r) + qry(cn->right, tm + 1, tr, l, r);
    }
};
