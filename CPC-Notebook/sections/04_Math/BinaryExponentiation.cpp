/*
Algorithm: Binary Exponentiation
When to use: Use for binary exponentiation problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

long long binpow(long long a,long long e,long long mod){long long r=1%mod;a%=mod;while(e){if(e&1)r=(__int128)r*a%mod;a=(__int128)a*a%mod;e>>=1;}return r;}
