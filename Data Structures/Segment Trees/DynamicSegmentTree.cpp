struct node {
    int val;
    node *l, *r;
    node() : val(0), l(nullptr), r(nullptr) {}
};
struct seg {
    seg(int tmn, int tmx) : root(new node()), mn(tmn), mx(tmx) {}

    node* root;
    int mn, mx;

    void upd(int ind, int v) {
        upd(root, mn, mx, ind, v);
    }
    void upd(node* cn, int nl, int nr, int i, int v) {
        cn->val += v;
        if (nl == nr) return;

        int m = nl + (nr - nl) / 2;
        if (i <= m){
            if(!cn->l) cn->l = new node();
            upd(cn->l, nl, m, i, v);
        }
        else{
            if(!cn->r) cn->r = new node();
            upd(cn->r, m + 1, nr, i, v);
        }
    }
    int qry(int ql, int qr) {
        return qry(root, mn, mx, ql, qr);
    }
    int qry(node* cn, int nl, int nr, int ql, int qr) {
        if (!cn || nr < ql || nl > qr) return 0;
        if(nl >= ql && nr <= qr) return cn->val;
        int m = nl + (nr - nl) / 2;
        return qry(cn->l, nl, m, ql, qr) + qry(cn->r, m + 1, nr, ql, qr);
    }
};
