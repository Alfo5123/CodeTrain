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
    https://codeforces.com/contest/475/problem/D

    Queries to count the number of pairs l,r such that gcd(a_l, a_l+1, ..., a_r) = x

*/

const int MAXN = 1e5 + 5; 
const int K = 25; 
int st[MAXN][K + 1];
int LOG[MAXN+1];

int gcd (int a, int b) 
{
    if (b == 0) return a;
    return gcd (b, a % b);
}

void gcd_preprocess(int N, int array[])
{
    for (int i = 0; i < N; i++) st[i+1][0] = array[i];

    for (int j = 1; j <= K; j++)
        for (int i = 1; i + (1 << j) - 1 <= N; i++)
            st[i][j] = gcd(st[i][j-1] , st[i + (1 << (j - 1))][j - 1] );
}

int gcd_query(int L, int R)
{
    // Obtain the gcd of two intervals with maximum size of 2^j possible
    if (L > R) return 0;
    int j = LOG[R - L + 1];
    return gcd(st[L][j], st[R - (1 << j) + 1][j]);
}

int binary_search(int start, int l, int r, int num)
{
    // Return the latest index idx in the range L-R such that 
    // the GCD(a_start, a_start+1, ... a_idx) is equal to num

    int best = -1;
    while ( l <= r )
    {
        int mid = (r-l)/2 + l;
        if ( gcd_query(start,mid) == num ) best = mid, l = mid + 1;
        else r = mid - 1;
    }
    return best;
}

map<int,long long> ans;

int main()
{
    FIN;
    int n; cin >> n;
    int a[n]; FOR(i,0,n) cin >> a[i];
    gcd_preprocess(n, a);
    LOG[1] = 0; for (int i = 2; i <= MAXN; i++) LOG[i] = LOG[i/2] + 1;

    FOR(i,1,n+1)
    {
        int start = i;
    
        while ( binary_search(i, start, n, gcd_query(i,start)) != -1)
        {
            int to = binary_search(i, start, n, gcd_query(i,start));
            ans[gcd_query(i,to)] += 1LL * (to-start+1);
            start = to + 1;
        }
    }

    int q, x;
    cin >> q;
    cout << "Solution" << endl;
    FOR(i,0,q)
    {
        cin >> x;
        cout << ans[x] << endl;
    }
    return 0;
}