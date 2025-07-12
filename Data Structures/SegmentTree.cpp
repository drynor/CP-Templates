template<typename Node, typename Update>
struct SegTree {
    vector<Node> tree;
    vector<int> arr;
    int n;
    
    SegTree(int a_len, vector<int> &a) {
        arr = a;
        n = a_len;
        tree.resize(4 * n);
        build(0, n - 1, 1);
    }
    
    void build(int start, int end, int index) {
        if (start == end) {
            tree[index] = Node(arr[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(start, mid, 2 * index);
        build(mid + 1, end, 2 * index + 1);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    
    void update(int start, int end, int index, int query_index, Update &u) {
        if (start == end) {
            u.apply(tree[index]);
            return;
        }
        int mid = (start + end) / 2;
        if (query_index <= mid)
            update(start, mid, 2 * index, query_index, u);
        else
            update(mid + 1, end, 2 * index + 1, query_index, u);
        tree[index].merge(tree[2 * index], tree[2 * index + 1]);
    }
    
    Node query(int start, int end, int index, int left, int right) {
        if (start > right || end < left)
            return Node();
        if (start >= left && end <= right)
            return tree[index];
        int mid = (start + end) / 2;
        Node l = query(start, mid, 2 * index, left, right);
        Node r = query(mid + 1, end, 2 * index + 1, left, right);
        Node ans;
        ans.merge(l, r);
        return ans;
    }
    
    void make_update(int arrIndex, int val) {
        Update new_update = Update(val);
        update(0, n - 1, 1, arrIndex, new_update);
    }
    
    Node make_query(int left, int right) {
        return query(0, n - 1, 1, left, right);
    }
};

struct Node1 {
    int mx;
    
    Node1() {
        mx = 0;
    }
    
    Node1(int val) {
        mx = val;
    }
    
    void merge(Node1 &l, Node1 &r) {
        mx = max(l.mx, r.mx);
    }
};
 
struct Update1 {
    int nw;
    
    Update1(int x) {
        nw = x;
    }
    
    void apply(Node1 &a) {
        a.mx = max(a.mx, nw);
    }
};
