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

const int MAXN = 1e3 + 1; 
const int K = 10; 

int st[MAXN][MAXN][K][K];
int LOG[MAXN+1];
int dp[MAXN+1][MAXN+1];

int n, m;

void max_preprocess()
{
    LOG[1] = 0; for (int i = 2; i <= MAXN; i++) LOG[i] = LOG[i/2] + 1;
    
    int aux;
    for(int i = 0; i < n; i++ )
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &aux);
            if ( aux == 1 )
            {
                dp[i+1][j+1] = min( dp[i][j], min( dp[i+1][j], dp[i][j+1]) ) + 1;
                st[i+1][j+1][0][0] = dp[i+1][j+1];
            }
        }
    }

    // Solve the 1D-RMQ instance for each row
    for(int i = 1; i <= n; i++)
        for ( int j = 1; j <= K ; j++)
            for (int k = 1; k + (1<<j) - 1 <= m; k++)
                st[i][k][0][j] = max(st[i][k][0][j-1] , st[i][k + (1 << (j - 1))][0][j-1] );
    
    // Complete the rest of the table
    for(int i = 1; i <= K; i++)
        for(int k = 1; k + (1<<i) - 1 <= n; k++)
            for (int j = 0; j <= K; j++)
                for(int l = 1; l + (1<<j) - 1 <= m; l++)
                    st[k][l][i][j] = max( st[k][l][i-1][j] , st[k + (1 << (i-1))][l][i-1][j] );
}

int max_query(int x1, int y1, int x2, int y2)
{
    if ( x2 < x1 || y2 < y1 ) return 0;
    int i = LOG[x2 - x1 + 1];
    int j = LOG[y2 - y1 + 1];
    return max( max(st[x1][y1][i][j], st[x2 - (1 << i) + 1][y1][i][j] ),
                max(st[x2 - (1 << i) + 1][y2 - (1<<j) + 1][i][j], st[x1][y2 - (1<<j) + 1][i][j]) 
            );
}
int main()
{
    scanf("%d%d",&n,&m);
    max_preprocess();

    int q; scanf("%d",&q);
    int x1, x2, y1, y2;
    for ( int t = 0; t < q; t++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        int lo = 0;
        int hi = max(n,m)+1;
        int best = 0;
        int mid;

        while(lo <= hi)
        {
            mid = (hi-lo)/2 + lo;
            if ( max_query(x1+mid-1, y1+mid-1, x2, y2) >= mid ) best = mid, lo = mid + 1;
            else hi = mid - 1;
        }

        printf("%d\n", best);
    }
    return 0;
}