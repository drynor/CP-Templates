/*
Algorithm: Coordinate Compression
When to use: Use for coordinate compression problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

template<class T> struct Compressor{ vector<T> xs; void add(const T& x){xs.push_back(x);} void build(){ sort(xs.begin(),xs.end()); xs.erase(unique(xs.begin(),xs.end()),xs.end()); } int get(const T& x)const{ return lower_bound(xs.begin(),xs.end(),x)-xs.begin(); } T value(int i)const{return xs[i];} int size()const{return xs.size();} };
