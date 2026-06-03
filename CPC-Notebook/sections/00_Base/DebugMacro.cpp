/*
Algorithm: Debug Macro
When to use: Use for debug macro problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

#ifdef LOCAL
#include <bits/stdc++.h>
using namespace std;
template<class T> void _dbg(const char* n,const T& v){ cerr<<n<<" = "<<v<<"\n"; }
#define dbg(x) _dbg(#x,x)
#else
#define dbg(x) ((void)0)
#endif
