/*
Algorithm: Chinese Remainder Theorem
When to use: Use for chinese remainder theorem problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

// Requires ext_gcd. Returns {remainder, lcm} or {0,-1}.
pair<long long,long long> crt(long long r1,long long m1,long long r2,long long m2){long long x,y;long long g=ext_gcd(m1,m2,x,y);if((r2-r1)%g)return {0,-1};long long l=m1/g*m2;__int128 add=(__int128)(r2-r1)/g*x;long long ans=(r1+(long long)(add%(m2/g))*m1)%l;if(ans<0)ans+=l;return {ans,l};}
