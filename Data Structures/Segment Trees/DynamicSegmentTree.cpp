struct Node {
    int value;
    Node *l;
    Node *r;

    Node() : value(0), l(nullptr), r(nullptr) {}
};
struct DST {
    DST(int tmn, int tmx) : root(new Node()), mn(tmn), mx(tmx) {}

    Node* root;
    int mn, mx;

    void upd(int ind, int v) {
        upd(root, mn, mx, ind, v);
    }
    void upd(Node* cn, int nl, int nr, int i, int v) {
        cn->value += v;
        if (nl == nr) return;

        int m = nl + (nr - nl) / 2;
        if (i <= m){
            if(!cn->l) cn->l = new Node();
            upd(cn->l, nl, m, i, v);
        }
        else{
            if(!cn->r) cn->r = new Node();
            upd(cn->r, m + 1, nr, i, v);
        }
    }
    int qry(int ql, int qr) {
        return qry(root, mn, mx, ql, qr);
    }
    int qry(Node* cn, int nl, int nr, int ql, int qr) {
        if (!cn || nr < ql || nl > qr) return 0;
        if(nl >= ql && nr <= qr) return cn->value;
        int m = nl + (nr - nl) / 2;
        return qry(cn->l, nl, m, ql, qr) + qry(cn->r, m + 1, nr, ql, qr);
    }
};
