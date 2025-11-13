/**
 * @brief 0-Indexed (Interface) / 1-Indexed (Storage) PURQ Fenwick Tree.
 * * This is the 0-indexed version of BIT2, using 1-indexed storage.
 * - update(idx, val): Adds val to the element at 0-indexed position idx.
 * - query(l, r): Returns the sum of the 0-indexed range [l, r].
 */
template <class T> struct BIT {
    int n;
    vector<T> bit;

    BIT(int sz) {
        n = sz + 1;
        bit.assign(n, 0);
    }
    
    T query(int r) {
        T v = 0;
        for (int i = r + 1; i > 0; i -= (i & -i)) v += bit[i];
        return v;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    void update(int j, T v) {
        for (int i = j + 1; i < n; i += (i & -i)) bit[i] += v;
    }
};
/**
 * @brief 0-Indexed (Interface) / 1-Indexed (Storage) RUPQ Fenwick Tree.
 * * This is the 0-indexed version of BIT1, using 1-indexed storage.
 * - update(l, r, val): Adds val to all elements in the 0-indexed range [l, r].
 * - query(idx): Returns the value of the element at 0-indexed position idx.
 */
template <class T> struct BIT {
    int n;
    vector<T> bit;

    BIT(int sz) {
        n = sz + 1;
        bit.assign(n, 0);
    }
    T query(int j) {
        T v = 0;
        for (int i = j + 1; i > 0; i -= (i & -i)) v += bit[i];
        return v;
    }
    void update(int j, T v) {
        for (int i = j + 1; i < n; i += (i & -i)) bit[i] += v;
    }
    void update(int l, int r, T v) {
        if (l > r) return;
        update(l, v);
        update(r + 1, -v);
    }
};
