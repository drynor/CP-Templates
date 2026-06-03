/*
Algorithm: nCr / Factorials
When to use: Use for ncr / factorials problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

const int MOD=1000000007;long long mpow(long long a,long long e){long long r=1;while(e){if(e&1)r=r*a%MOD;a=a*a%MOD;e>>=1;}return r;}struct Comb{vector<long long>f,invf;Comb(int n):f(n+1),invf(n+1){f[0]=1;for(int i=1;i<=n;i++)f[i]=f[i-1]*i%MOD;invf[n]=mpow(f[n],MOD-2);for(int i=n;i;i--)invf[i-1]=invf[i]*i%MOD;}long long C(int n,int r)const{return r<0||r>n?0:f[n]*invf[r]%MOD*invf[n-r]%MOD;}};
