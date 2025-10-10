struct Node {
    int value;
    Node *l;
    Node *r;

    Node() : value(0), l(nullptr), r(nullptr) {}
};

struct DST {
    DST(int mn_, int mx_) : root(new Node()), mn(mn_), mx(mx_) {}


    void update(int ind, int v) {
        update(root, mn, mx, ind, v);
    }

    int query(int ql, int qr) {
        return query(root, mn, mx, ql, qr);
    }

    Node* root;
    int mn;
    int mx;

    void update(Node* cn, int nl, int nr, int ind, int v) {
        cn->value += v;

        if (nl == nr) return;

        int m = nl + (nr - nl) / 2;
        if (ind <= m){
            if(!cn->l) cn->l = new Node();
            update(cn->l, nl, m, ind, v);
        }
        else{
            if(!cn->r) cn->r = new Node();
            update(cn->r, m + 1, nr, ind, v);
        }
    }

    int query(Node* cn, int nl, int nr, int ql, int qr) {
        if (!cn || nr < ql || nl > qr) return 0;
        if(nl >= ql && nr <= qr) return cn->value;

        int m = nl + (nr - nl) / 2;
        int lsum = query(cn->l, nl, m, ql, qr);
        int rsum = query(cn->r, m + 1, nr, ql, qr);

        return lsum + rsum;
    }
};
