/*
Algorithm: Modular Arithmetic / ModInt
When to use: Use for modular arithmetic / modint problems when this standard CPC tool matches the constraints.
Indexing: 0-indexed unless noted
Complexity: See standard bounds.
Common bugs: Check indexing before paste.
*/

template<int MOD> struct ModInt{int v;ModInt(long long x=0){x%=MOD;if(x<0)x+=MOD;v=x;}ModInt&operator+=(ModInt o){v+=o.v;if(v>=MOD)v-=MOD;return *this;}ModInt&operator-=(ModInt o){v-=o.v;if(v<0)v+=MOD;return *this;}ModInt&operator*=(ModInt o){v=(long long)v*o.v%MOD;return *this;}static ModInt pow(ModInt a,long long e){ModInt r=1;while(e){if(e&1)r*=a;a*=a;e>>=1;}return r;}ModInt inv()const{return pow(*this,MOD-2);} };using mint=ModInt<1000000007>;
