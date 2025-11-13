struct SegTree2d {
    int n , m;
    vector<vector<int>> seg;

    int def() const {
        return 0;
    }

    int merge(int a, int b) const {
        return a + b;
    }

    SegTree2d(int tn, int tm){
        n = tn; m = tm;
        seg = vector<vector<int>>(2*n, vector<int>(2*m, def()));
    }

    int query(int x1, int y1, int x2, int y2) const {
        int ans = def();
        int y3 = y1 + m, y4 = y2 + m;
        for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2, --x2 /= 2){
            for(y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2, --y2 /= 2){
                if((x1&1) and (y1&1))  ans = merge(ans, seg[x1][y1]);
                if((x1&1) and !(y2&1)) ans = merge(ans, seg[x1][y2]);
                if(!(x2&1) and (y1&1)) ans = merge(ans, seg[x2][y1]);
                if(!(x2&1) and !(y2&1))ans = merge(ans, seg[x2][y2]);
            }
        }
        return ans;
    }

    void update(int x, int y, int val){
        int y2 = y += m;
        for(x += n; x; x >>= 1, y = y2){
            if(x >= n) seg[x][y] = val;
            else{
                seg[x][y] = merge(seg[2*x][y], seg[2*x+1][y]);
            }
            while(y >>= 1){
                seg[x][y] = merge(seg[x][2*y], seg[x][2*y+1]);
            }
        }
    }
};

template<typename Node, typename Update>
struct SegTree2D {
    vector<vector<Node>> tree;
    vector<vector<int>>& arr;
    int n, m;

    SegTree2D(vector<vector<int>> &a) : arr(a) {
        n = arr.size();
        m = arr[0].size();
        tree.resize(4 * n);
        for(int i = 0; i < 4 * n; i++){
            tree[i].resize(4 * m);
        }
        build_x(0, n - 1, 1);
    }

    void build_x(int start_x, int end_x, int index_x) {
        if (start_x == end_x) {
            build_y(start_x, 0, m - 1, index_x, 1);
            return;
        }
        int mid_x = (start_x + end_x) / 2;
        build_x(start_x, mid_x, 2 * index_x);
        build_x(mid_x + 1, end_x, 2 * index_x + 1);
        
        for (int i = 1; i < 4 * m; ++i) {
            tree[index_x][i].merge(tree[2 * index_x][i], tree[2 * index_x + 1][i]);
        }
    }

    void build_y(int current_x, int start_y, int end_y, int index_x, int index_y) {
        if (start_y == end_y) {
            tree[index_x][index_y] = Node(arr[current_x][start_y]);
            return;
        }
        int mid_y = (start_y + end_y) / 2;
        build_y(current_x, start_y, mid_y, index_x, 2 * index_y);
        build_y(current_x, mid_y + 1, end_y, index_x, 2 * index_y + 1);
        tree[index_x][index_y].merge(tree[index_x][2 * index_y], tree[index_x][2 * index_y + 1]);
    }

    void update_y_merge(int start_y, int end_y, int index_y, int index_x, int query_y) {
        tree[index_x][index_y].merge(tree[2 * index_x][index_y], tree[2 * index_x + 1][index_y]);
        if (start_y == end_y) {
            return;
        }
        int mid_y = (start_y + end_y) / 2;
        if (query_y <= mid_y) {
            update_y_merge(start_y, mid_y, 2 * index_y, index_x, query_y);
        } else {
            update_y_merge(mid_y + 1, end_y, 2 * index_y + 1, index_x, query_y);
        }
    }

    void update_x(int start_x, int end_x, int index_x, int query_x, int query_y, Update &u) {
        if (start_x == end_x) {
            update_y(0, m - 1, index_x, 1, query_y, u);
            return;
        }
        int mid_x = (start_x + end_x) / 2;
        if (query_x <= mid_x) {
            update_x(start_x, mid_x, 2 * index_x, query_x, query_y, u);
        } else {
            update_x(mid_x + 1, end_x, 2 * index_x + 1, query_x, query_y, u);
        }
        update_y_merge(0, m - 1, 1, index_x, query_y);
    }

    void update_y(int start_y, int end_y, int index_x, int index_y, int query_y, Update &u) {
        if (start_y == end_y) {
            u.apply(tree[index_x][index_y]);
            return;
        }
        int mid_y = (start_y + end_y) / 2;
        if (query_y <= mid_y) {
            update_y(start_y, mid_y, index_x, 2 * index_y, query_y, u);
        } else {
            update_y(mid_y + 1, end_y, index_x, 2 * index_y + 1, query_y, u);
        }
        tree[index_x][index_y].merge(tree[index_x][2 * index_y], tree[index_x][2 * index_y + 1]);
    }

    Node query_x(int start_x, int end_x, int index_x, int left_x, int right_x, int left_y, int right_y) {
        if (start_x > right_x || end_x < left_x) {
            return Node();
        }
        if (start_x >= left_x && end_x <= right_x) {
            return query_y(0, m - 1, index_x, 1, left_y, right_y);
        }
        int mid_x = (start_x + end_x) / 2;
        Node l = query_x(start_x, mid_x, 2 * index_x, left_x, right_x, left_y, right_y);
        Node r = query_x(mid_x + 1, end_x, 2 * index_x + 1, left_x, right_x, left_y, right_y);
        Node ans;
        ans.merge(l, r);
        return ans;
    }

    Node query_y(int start_y, int end_y, int index_x, int index_y, int left_y, int right_y) {
        if (start_y > right_y || end_y < left_y) {
            return Node();
        }
        if (start_y >= left_y && end_y <= right_y) {
            return tree[index_x][index_y];
        }
        int mid_y = (start_y + end_y) / 2;
        Node l = query_y(start_y, mid_y, index_x, 2 * index_y, left_y, right_y);
        Node r = query_y(mid_y + 1, end_y, index_x, 2 * index_y + 1, left_y, right_y);
        Node ans;
        ans.merge(l, r);
        return ans;
    }

    void make_update(int row, int col, int val) {
        Update new_update = Update(val);
        if (n > 0) {
            update_x(0, n - 1, 1, row, col, new_update);
        }
    }

    Node make_query(int r1, int c1, int r2, int c2) {
        if (n == 0) return Node();
        return query_x(0, n - 1, 1, r1, r2, c1, c2);
    }
};

struct Node1 {
    int sum;
    
    Node1() {
        sum = 0;
    }
    
    Node1(int val){
        sum = val;
    }
    
    void merge(const Node1 &l, const Node1 &r) {
        sum = l.sum + r.sum;
    }
};

struct Update1 {
    int nw;
    
    Update1(int x){
        nw = x;
    }
    
    void apply(Node1 &a) {
        a.sum = nw;
    }
};
