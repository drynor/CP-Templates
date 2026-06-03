/*
Algorithm: Matrix Exponentiation
When to use: Use for matrix exponentiation problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

using ll=long long;using Matrix=vector<vector<ll>>;Matrix mul(const Matrix&a,const Matrix&b,ll mod){int n=a.size(),m=b[0].size(),mid=b.size();Matrix c(n,vector<ll>(m));for(int i=0;i<n;i++)for(int k=0;k<mid;k++)if(a[i][k])for(int j=0;j<m;j++)c[i][j]=(c[i][j]+(__int128)a[i][k]*b[k][j])%mod;return c;}Matrix mpow(Matrix a,long long e,ll mod){int n=a.size();Matrix r(n,vector<ll>(n));for(int i=0;i<n;i++)r[i][i]=1%mod;while(e){if(e&1)r=mul(r,a,mod);a=mul(a,a,mod);e>>=1;}return r;}
