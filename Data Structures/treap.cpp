#include <bits/stdc++.h>
#define int long long
#define ALL(c) begin(c), end(c)
#define SORT(c) sort(begin(c), end(c))
#define rSORT(c) sort(rbegin(c), rend(c))
#define f first
#define s second
#define pb push_back
#define endl "\n"
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<int>(l, r)(rng)
 
void solve();
int32_t main() {
    #ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output1.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false);cin.tie(0);int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    #ifndef ONLINE_JUDGE
        cout << "(=== Code Execution Successful ===)";
    #endif
}
 
template<typename Node, typename Update>
struct ImplicitTreap {
    struct TreapNode {
        int priority;
        int size;
        bool reverse;
        
        Node data;      // User-defined node data payload
        Update lazy;    // User-defined lazy update payload
        TreapNode *l, *r;
 
        // Constructor initializes the node with a value.
        // The user's Node struct must have a constructor that takes a single value.
        template<typename ValueType>
        TreapNode(ValueType val) : 
            priority(rnd()), size(1), reverse(false),
            data(val), lazy(), l(nullptr), r(nullptr) {}
    };
 
    TreapNode* root = nullptr;
    static mt19937 rnd;
 
    int _size(TreapNode* t) { return t ? t->size : 0; }
 
    // Recalculates a node's data by calling the user-defined merge function.
    void pull(TreapNode* t) {
        if (!t) return;
        
        // The user's Node struct must have a `merge` method.
        // It merges data from left and right children into the current node.
        const Node* left_data = t->l ? &(t->l->data) : nullptr;
        const Node* right_data = t->r ? &(t->r->data) : nullptr;
        t->data.merge(left_data, right_data);
 
        t->size = 1 + _size(t->l) + _size(t->r);
    }
    
    // Applies a lazy update by calling the user-defined apply function.
    void apply(TreapNode* t, const Update& upd) {
        if (!t) return;
        // The user's Update struct must have an `apply` method.
        upd.apply(t->data, _size(t));
    }
 
    // Pushes lazy updates and reversals down to children.
    void push(TreapNode* t) {
        if (!t) return;
 
        if (t->reverse) {
            swap(t->l, t->r);
            if (t->l) t->l->reverse ^= true;
            if (t->r) t->r->reverse ^= true;
            t->reverse = false;
        }
 
        // The user's Update struct must have an `is_identity` method.
        if (!t->lazy.is_identity()) {
            if (t->l) {
                apply(t->l, t->lazy);
                // The user's Update struct must have a `combine` method.
                t->l->lazy.combine(t->lazy);
            }
            if (t->r) {
                apply(t->r, t->lazy);
                t->r->lazy.combine(t->lazy);
            }
            t->lazy = Update(); // Reset lazy update to identity
        }
    }
 
    // --- Core Treap Operations (Split and Merge) ---
    void split(TreapNode* t, int pos, TreapNode*& l, TreapNode*& r, int add = 0) {
        if (!t) { l = r = nullptr; return; }
        push(t);
        int current_pos = add + _size(t->l);
        if (pos <= current_pos) {
            split(t->l, pos, l, t->l, add);
            r = t;
        } else {
            split(t->r, pos, t->r, r, current_pos + 1);
            l = t;
        }
        pull(t);
    }
    
    void merge(TreapNode*& t, TreapNode* l, TreapNode* r) {
        push(l); push(r);
        if (!l || !r) { t = l ? l : r; }
        else if (l->priority > r->priority) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        pull(t);
    }
 
    // Helper to recursively delete nodes.
    void _erase_nodes(TreapNode* t) {
        if (!t) return;
        _erase_nodes(t->l);
        _erase_nodes(t->r);
        delete t;
    }
    
    ImplicitTreap() = default;
    ~ImplicitTreap() { clear(); }
    void clear() { _erase_nodes(root); root = nullptr; }
    int size() { return _size(root); }
 
    // --- Public API ---
 
    template<typename ValueType>
    void insert(int pos, ValueType val) {
        if (pos < 0 || pos > size()) return;
        TreapNode *l, *r;
        split(root, pos, l, r);
        merge(l, l, new TreapNode(val));
        merge(root, l, r);
    }
    
    void erase(int qL, int qR) {
        if (qL > qR || qL < 0 || qR >= size()) return;
        TreapNode *l, *r, *mid;
        split(root, qL, l, r);
        split(root, qR - qL + 1, mid, r);
        _erase_nodes(mid);
        merge(root, l, r);
    }
 
    void update(int qL, int qR, const Update& u) {
        if (qL > qR || qL < 0 || qR >= size()) return;
        TreapNode *l, *r, *mid;
        split(root, qL, l, r);
        split(r, qR - qL + 1, mid, r);
        apply(mid, u);
        if (mid) mid->lazy.combine(u);
        merge(r, mid, r);
        merge(root, l, r);
    }
 
    Node query(int qL, int qR) {
        if (qL > qR || qL < 0 || qR >= size()) return Node(); // Return default Node
        TreapNode *l, *r, *mid;
        split(root, qL, l, r);
        split(r, qR - qL + 1, mid, r);
        Node result = mid ? mid->data : Node();
        merge(r, mid, r);
        merge(root, l, r);
        return result;
    }
 
    void reverse(int qL, int qR) {
        if (qL >= qR || qL < 0 || qR >= size()) return;
        TreapNode *l, *r, *mid;
        split(root, qL, l, r);
        split(r, qR - qL + 1, mid, r);
        if (mid) mid->reverse ^= true;
        merge(r, mid, r);
        merge(root, l, r);
    }
 
    void sm(int ql, int qr){
        qr = qr - ql + 1;
        TreapNode *l, *m, *r;
        split(root, ql, l, m);
        split(m, qr, m, r);
 
        merge(r, r, m);
        merge(root, l, r);
    }
};
 
// Initialize the static random number generator for the template class.
template <typename Node, typename Update>
mt19937 ImplicitTreap<Node, Update>::rnd(chrono::steady_clock::now().time_since_epoch().count());
 
/**
 * The Node struct defines the data stored at each position.
 * It must provide:
 * 1. A default constructor `Node()`.
 * 2. A constructor from a value `Node(ValueType val)`.
 * 3. A `merge(const Node* left, const Node* right)` method to recalculate
 * itself based on its children's data.
 */
struct StringNode {
    char value;
 
    StringNode() : value('\0') {}
    StringNode(char val) : value(val) {}
 
    // No aggregation (like sum or min) is needed for this problem.
    // The node's own value is constant unless an update is applied.
    // Therefore, merge does nothing.
    void merge(const StringNode* left, const StringNode* right) {}
};
 
/**
 * The Update struct defines a lazy operation.
 * It must provide:
 * 1. A default constructor `Update()` for an identity (no-op) update.
 * 2. An `apply(Node& node, int size)` method that modifies a Node.
 * 3. A `combine(const Update& newer)` method to merge a new update into this one.
 * 4. An `is_identity()` method to check if it's a no-op.
 */
struct DummyUpdate {
    // This method is required by the template but does nothing.
    void apply(StringNode& node, int size) const {}
 
    // This method is required by the template but does nothing.
    void combine(const DummyUpdate& newer) {}
 
    // This method is required by the template. It always returns true
    // because this update is always a "do nothing" operation.
    bool is_identity() const { return true; }
};
 
void solve(){
    int n,q;cin >> n >> q;
    string a;cin >> a;
    ImplicitTreap<StringNode, DummyUpdate> t;
    for(int i = 0;i<n;i++){
        t.insert(i, a[i]);
    }
    
    while(q--){
        int ql, qr; cin >> ql >> qr; ql--; qr--;
        t.sm(ql, qr);
    }
 
    for(int i = 0;i<n;i++){
        cout << t.query(i,i).value;
    } cout << endl;
 
    
 
    
    // ImplicitTreap<SumMinNode, AddSetUpdate> t;
 
    // for(int i = 0; i < 10; i++) t.insert(i, i * 10);
    
    // t.update(2, 5, AddSetUpdate::make_add(1));
    // t.update(2, 5, AddSetUpdate::make_set(100));
    // t.reverse(2, 9);
    // t.update(2, 5, AddSetUpdate::make_set(200));
 
    // cout << "Sum of range [0, 7]: " << t.query(0, 7).sum << endl;
    // cout << "Min of range [0, 7]: " << t.query(0, 7).min_val << endl;
 
    // t.erase(2, 2);
 
    // // To print, you can query the whole range and access the values
    // SumMinNode final_node = t.query(0, t.size() - 1);
    // cout << "Final sum: " << final_node.sum << endl;
    // cout << "Final min: " << final_node.min_val << endl;
}
