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
    https://codeforces.com/problemset/problem/630/I

*/

long long binpow( long long a, long long b)
{
    long long res = 1;
    while(b > 0)
    {
        if ( b & 1 ) res = res * a ;
        a = a * a ;
        b >>= 1;
    }
    return res;
}

int main()
{
    FIN;
    long long n;
    cin >> n;
    cout << 24LL*binpow(4,n-3) + 36*(n-3)*binpow(4,n-4) << endl;
    return 0;
}
