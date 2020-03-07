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
    https://codeforces.com/problemset/problem/514/D?fbclid=IwAR1Jt9Vtx7FbVX5jWpGQKb2sHXJQAIj-KPiM-ETPXy8Y_x4ZFtN-oHCMYWs

    Get maximum over subintervals for different arrays 

*/

const int MAXN = 1e5 + 5; 
const int K = 20; 
const int M = 5;
int st[M][MAXN][K + 1];
int LOG[MAXN+1];
int a[MAXN][M];

void max_preprocess(int n, int m)
{
    for (int i = 0; i < n; i++) 
        for(int l = 0; l < m; l++) 
            st[l][i+1][0] = a[i][l];
        
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
    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];

    max_preprocess(n, m);
    LOG[1] = 0; for (int i = 2; i <= MAXN; i++) LOG[i] = LOG[i/2] + 1;

    int maxx = 0;
    int left_ans = -1;
    int right;

    FOR(i,1,n+1)
    {
        right = binary_search(i,i,n,k,m);

        if ( right == -1 ) continue;
        else
        {
            if (right - i + 1 > maxx)
            {
                maxx = right - i + 1;
                left_ans = i;
            }
        }
        
    }

    FOR(i,0,m)
        cout << max_query(i,left_ans,left_ans + maxx -1) << " ";
    
    return 0;
}