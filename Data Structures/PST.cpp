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
        roots.push_back(build(a, 0, sz - 1));
    }

    Node* build(const vector<int>& a, int tl, int tr) {
        if(tl == tr) return new Node(a[tl]);

        int tm = tl + (tr - tl) / 2;
        return new Node(build(a, tl, tm), build(a, tm + 1, tr));
    }

    int update(int version, int pos, int val) {
        Node* root = update(roots[version], 0, sz - 1, pos, val);
        roots.push_back(root);
        return roots.size() - 1;
    }

    Node* update(Node* pn, int tl, int tr, int pos, int val) {
        if(tl == tr) return new Node(val);

        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) {
            return new Node(update(pn->left, tl, tm, pos, val), pn->right);
        } else {
            return new Node(pn->left, update(pn->right, tm + 1, tr, pos, val));
        }
    }

    int query(int version, int l, int r) {
        return query(roots[version], 0, sz - 1, l, r);
    }

    int query(Node* node, int tl, int tr, int l, int r) {
        if (tl > r || tr < l || !node) return 0;
        if (tl >= l && tr <= r)        return node->sum;
        
        int tm = tl + (tr - tl) / 2;
        return query(node->left, tl, tm, l, r) + query(node->right, tm + 1, tr, l, r);
    }
};
