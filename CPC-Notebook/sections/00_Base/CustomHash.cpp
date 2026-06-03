/*
Algorithm: Custom Hash
When to use: Use for custom hash problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

struct custom_hash{ static uint64_t splitmix64(uint64_t x){ x+=0x9e3779b97f4a7c15ULL; x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL; x=(x^(x>>27))*0x94d049bb133111ebULL; return x^(x>>31); } size_t operator()(uint64_t x)const{ static const uint64_t R=chrono::steady_clock::now().time_since_epoch().count(); return splitmix64(x+R); } };
