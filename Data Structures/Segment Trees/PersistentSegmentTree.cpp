struct PST {
    struct Node {
        int sum = 0;
        Node *left = nullptr, *right = nullptr;

        Node(int s){
            sum = s;
        }
        Node(Node* l, Node* r){
            left = l; right = r;
            if (l) sum += l->sum;
            if (r) sum += r->sum;
        }
    };
    int sz;
    vector<Node*> roots;

    PST(const vector<int>& a) {
        sz = a.size();
        roots.pb(build(a, 0, sz - 1));
    }
    Node* build(const vector<int>& a, int tl, int tr) {
        if(tl == tr) return new Node(a[tl]);

        int tm = tl + (tr - tl) / 2;
        return new Node(build(a, tl, tm), build(a, tm + 1, tr));
    }

    int upd(int version, int pos, int val) {
        Node* root = upd(roots[version], 0, sz - 1, pos, val);
        roots.pb(root);
        return roots.size() - 1;
    }
    Node* upd(Node* pn, int tl, int tr, int pos, int val) {
        if(tl == tr) return new Node(val);

        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            return new Node(upd(pn->left, tl, tm, pos, val), pn->right);
        } else {
            return new Node(pn->left, upd(pn->right, tm + 1, tr, pos, val));
        }
    }

    int qry(int version, int l, int r) {
        return qry(roots[version], 0, sz - 1, l, r);
    }
    int qry(Node* node, int tl, int tr, int l, int r) {
        if (tl > r || tr < l || !node) return 0;
        if (tl >= l && tr <= r)        return node->sum;
        
        int tm = tl + (tr - tl) / 2;
        return qry(node->left, tl, tm, l, r) + qry(node->right, tm + 1, tr, l, r);
    }
};
