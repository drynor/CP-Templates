/*
Algorithm: Extended GCD
When to use: Use for extended gcd problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

long long ext_gcd(long long a,long long b,long long&x,long long&y){if(!b){x=a>=0?1:-1;y=0;return llabs(a);}long long x1,y1,g=ext_gcd(b,a%b,x1,y1);x=y1;y=x1-y1*(a/b);return g;}
