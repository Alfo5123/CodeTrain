/*
    Problem 1 IOI - 94:
    https://ioinformatics.org/files/ioi1994problem1.pdf
                               
*/
#include <bits/stdc++.h>
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;

const int N = 105;
long long a[N][N];
int n;

int main()
{
    FIN;
    cin >> n;
    long long ans = -1;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            cin >> a[i][j];

            if ( i > 1 )
            {
                if ( j == i ) a[i][j] += a[i-1][j-1];
                else if ( j == 1 ) a[i][j] += a[i-1][j];
                else a[i][j] += max( a[i-1][j-1], a[i-1][j] );
            }

            ans = max( ans, a[i][j]);
        }   
    }

    cout << ans << endl;

    return 0;
}

