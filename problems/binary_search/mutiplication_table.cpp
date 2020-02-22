#include <bits/stdc++.h>
#define fst first
#define snd second
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii; 

/*
    Problem:
    https://codeforces.com/contest/448/problem/D

    Find the k-smallest number in a mutiplicative table of size n x m
    
*/
ll n, m , k;

bool fun( ll x )
{
    // Count the number of values less or equal than x
    ll ans = 0;
    FOR(i,1,n+1) ans += min(x/i, m);
    return ans >= k;
}
int main()
{
    FIN;
    cin >> n >> m >> k;
    ll lo = 1;
    ll hi = n*m;
    ll ans = -1;
    ll mid;

    while (lo <= hi)
    {
        mid = (hi-lo)/2 + lo;
        if ( fun(mid) ) // Check lowerbound ( first value that satisfies the property )
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
        
    }
    cout << ans << "\n";
    return 0;
}
