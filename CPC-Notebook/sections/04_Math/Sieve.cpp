/*
Algorithm: Sieve
When to use: Use for sieve problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

vector<int> primes,lp;void linear_sieve(int n){lp.assign(n+1,0);primes.clear();for(int i=2;i<=n;i++){if(!lp[i])lp[i]=i,primes.push_back(i);for(int p:primes){if(p>lp[i]||1LL*i*p>n)break;lp[i*p]=p;}}}
