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
    https://codeforces.com/contest/713/problem/D

    Explanation for 2D sparse table
    https://codeforces.com/blog/entry/45485

    Implement a 2D sparse table and find the maximum square of ones
    within a rectangle of 0s and 1s.

*/

const int MAXN = 1e5 + 5; 
const int K = 20; 

int st[MAXN][MAXN][K][K];
int LOG[MAXN+1];
int a[MAXN][MAXN];
int dp[MAXN+1][MAXN+1];

int n, m;

void max_preprocess()
{
    LOG[1] = 0; for (int i = 2; i <= MAXN; i++) LOG[i] = LOG[i/2] + 1;

    for(int i = 0; i < n; i++ )
    {
        for(int j = 0; j < m; j++)
        {
            if ( a[i][j] == 1 )
            {
                dp[i+1][j+1] = min( dp[i][j], min( dp[i+1][j], dp[i][j+1]) ) + 1;
                st[i+1][j+1][0][0] = dp[i+1][j+1];
            }
        }
    }
        
    for( int l = 0; l < m; l++)
        for (int j = 1; j <= K; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                st[l][i][j] = max(st[l][i][j-1] , st[l][i + (1 << (j - 1))][j - 1] );
}

int max_query(int l, int L, int R)
{
    if (L > R) return 0;
    int j = LOG[R - L + 1];
    return max(st[l][L][j], st[l][R - (1 << j) + 1][j]);
}

long long cost(int m, int L, int R)
{
    long long ans = 0;
    FOR(i,0,m) ans += max_query(i,L,R);
    return ans;
}

int binary_search(int start, int lo, int hi, int k, int m)
{
    int best = 0;
    while ( lo <= hi )
    {
        int mid = (hi-lo)/2 + lo;
        if ( cost(m, start, mid) <= k ) best = mid, lo = mid + 1;
        else hi = mid - 1;
    }
    return best;
}

int main()
{
    FIN;
    cin >> n >> m;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];

    

    max_preprocess();

    return 0;
}