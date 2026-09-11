vector<vector<int>> adj;
vector<int> hashi;
map<vector<int>, int> id_map;
int next_id;

int go(int u, int p) {
    vector<int> chash;
    for (int v : adj[u]) {
        if (v != p) {
            chash.push_back(go(v, u));
        }
    }
    if (chash.empty()) {
        hashi[u] = 1;
        return 1;
    }
    
    sort(chash.begin(), chash.end());
    auto it = id_map.find(chash);
    int myhash;
    
    if (it == id_map.end()) {
        myhash = next_id;
        id_map[chash] = next_id;
        next_id++;
    } else {
        myhash = it->second;
    }
    hashi[u] = myhash;
    return myhash;
}
int Hash(int u) {
    return hashi[u];
}
// https://youkn0wwho.academy/topic-list/tree_isomorphism
void solve(){
    int n; cin >> n;
    
    adj.resize(n + 1);
    hashi.resize(n + 1);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    id_map.clear();
    next_id = 2;

    go(1, 0);
    
    int ans = 1;
    vector<bool> vis(n + 1, false);
    vector<int> sub; sub.pb(1);
    while(!sub.empty()){
        int u = sub.back(); sub.pop_back();
        vis[u] = true;
        map<int, vector<int>> mp;
        for(auto v : adj[u]){
            if(vis[v]) continue;
            int hsh = Hash(v);
            mp[hsh].pb(v);
        }

        for(auto i : mp){
            if(i.s.size() > 1) continue;
            ans++;
            sub.pb(i.s.back());
        }
    }
    cout << ans << endl;
}
 
/**
 * @brief Computes a canonical hash (ID) for a rooted subtree using the AHU algorithm.
 *
 * This function performs a post-order traversal (DFS) of the tree.
 * It assigns a unique integer ID to each unique subtree "shape".
 *
 * 1. All leaf nodes get the base ID (e.g., 1).
 * 2. For an internal node `u`:
 * a. Recursively get the hash IDs of all its children.
 * b. Collect these IDs into a vector.
 * c. Sort the vector. This makes the hash independent of the children's order.
 * d. Use this sorted vector as a key in a map (id_map).
 * e. If this key (shape) hasn't been seen, assign it a new, incrementing ID.
 * f. Return the ID corresponding to this shape.
 *
 * @param u The current node.
 * @param p The parent of the current node (to avoid traversing backward).
 * @param adj The adjacency list of the tree.
 * @param id_map A map from a sorted vector of child-hashes to a unique integer ID.
 * This map is shared between both trees in a test case.
 * @param next_id The next available unique ID to assign to a new subtree shape.
 * @return The canonical hash (integer ID) for the subtree rooted at `u`.
 */
int get_subtree_hash(int u, int p, const vector<vector<int>>& adj,
                     map<vector<int>, int>& id_map, int& next_id) {
    
    // 1. Collect hashes of all children
    vector<int> child_hashes;
    for (int v : adj[u]) {
        if (v != p) {
            child_hashes.push_back(get_subtree_hash(v, u, adj, id_map, next_id));
        }
    }
 
    // Base case: Leaf node
    if (child_hashes.empty()) {
        return 1; // Assign a constant hash (1) to all leaf nodes
    }
 
    // 2. Sort child hashes to make the representation canonical
    //    (independent of child order)
    sort(child_hashes.begin(), child_hashes.end());
 
    // 3. Find or create a unique ID for this subtree shape
    //    Use map::find to avoid inserting and then looking up
    auto it = id_map.find(child_hashes);
 
    if (it == id_map.end()) {
        // This is a new subtree shape we haven't seen before
        id_map[child_hashes] = next_id;
        return next_id++; // Return the new ID and increment the counter
    } else {
        // We have seen this shape before, return its existing ID
        return it->second;
    }
}
 
/**
 * @brief Solves a single test case for rooted tree isomorphism.
 */
void solve() {
    int n;
    cin >> n;
 
    // Adjacency lists for Tree 1 and Tree 2
    // We size them n+1 for 1-based indexing
    vector<vector<int>> adj1(n + 1);
    vector<vector<int>> adj2(n + 1);
 
    // Read edges for Tree 1
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
 
    // Read edges for Tree 2
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
 
    // These must be initialized *once per test case* and shared
    // between the two hash calculations.
    map<vector<int>, int> id_map;
    int next_id = 2; // 1 is reserved for leaf nodes
 
    // Calculate the canonical hash for the root of Tree 1
    // The parent of the root (node 1) is a dummy node (e.g., 0)
    int hash1 = get_subtree_hash(1, 0, adj1, id_map, next_id);
 
    // Calculate the canonical hash for the root of Tree 2
    // This call will *use and extend* the same id_map
    int hash2 = get_subtree_hash(1, 0, adj2, id_map, next_id);
 
    // If the hashes are identical, the rooted trees are isomorphic
    if (hash1 == hash2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
 
/**
 * @brief Main function: sets up fast I/O and handles multiple test cases.
 */
int main() {
    // Optimize C++ streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
