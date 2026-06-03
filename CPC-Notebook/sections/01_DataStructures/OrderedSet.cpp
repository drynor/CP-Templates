/*
Algorithm: Ordered Set
When to use: Use GNU PBDS for kth element and count of elements smaller than x.
Indexing: 0-indexed unless noted
Complexity: See code and notes.
Common bugs: For duplicates store pair<value,id>.
*/

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void myErase(ordered_set<int> &t, int v){
    int rank = t.order_of_key(v);
    ordered_set<int>::iterator it = t.find_by_order(rank);
    t.erase(it);
}
