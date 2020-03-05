#include <bits/stdc++.h>
#define fst first
#define snd second
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii; 

/*
    Problem:
    https://codeforces.com/contest/1288/problem/C

*/

int MOD = 1e9 + 7;
ll fac[100005];
 
long long binpow( long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while(b > 0)
    {
        if ( b & 1 ) res = res * a % m ;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
ll C( ll a , ll b )
{
	// Using the fact N!^-1 % MOD = (N! % MOD)^(MOD-2) % MOD
	return fac[a] * binpow(fac[b], MOD-2, MOD) % MOD * binpow(fac[a-b], MOD-2, MOD) % MOD;
}
 
int main()
{
    FIN;
    int n, m; cin >> n >> m;
    fac[0] = 1; for (int i = 1; i < 100005; i++) fac[i] = fac[i-1] * i % MOD;
    cout << C( 2*m + n - 1, n - 1) << endl;
    return 0;
}