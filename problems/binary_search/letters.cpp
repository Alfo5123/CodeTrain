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
    https://codeforces.com/problemset/problem/978/C
    
    Finding lowerbound

*/
ll n, m ;

int main()
{
    FIN;
    cin >> n >> m;
    ll a[n]; FOR(i,0,n) cin >> a[i];
    FOR(i,1,n) a[i] += a[i-1];
    ll b[m]; FOR(i,0,m) cin >> b[i];

    FOR(i,0,m)
    {
        ll lo = 0;
        ll hi = n-1;
        ll ans = -1;
        ll mid;

        while (lo <= hi)
        {
            mid = (hi-lo)/2 + lo;
            if ( a[mid] >= b[i] ) // Check lowerbound ( first value that satisfies the property )
            {
                ans = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        
        cout << ans+1 << " " << b[i] - (ans == 0? 0 : a[ans-1]) << "\n";
    }
    
    return 0;
}
