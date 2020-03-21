/*

Problem https://codeforces.com/contest/597/problem/C

Given an integer array with n elements, find the number
of increasing subsequences with k+1 elements

Let dp[i][j] be the number of increasing sequences ending in i with j elements
then dp[i][1] = 1
dp[i][j] = sum( dp[i_][j-1] if a[i] > a[i_] for i_ in [0, i-1])

*/


#include <bits/stdc++.h>
using namespace std;

int n, k;
long long BIT[11][100005];

void update(int kidx, int idx, long long val)
{
    for(; idx < n+1; idx += idx & -idx) BIT[kidx][idx] += val;
}

long long sum_query(int kidx, int idx)
{
    long long res = 0;
    for(;idx > 0; idx -= idx & -idx) res += BIT[kidx][idx] ;
    return res;
}

int main()
{   
    cin >> n >> k;
    int a;
    for(int i = 0; i < n; i++)
    {
        cin >> a;
        update(0, a, 1);
        for(int j = 1; j <= k; j++)
            update(j, a, sum_query(j-1, a-1));
    }
    cout << sum_query(k, n) << "\n";
   
    return 0;
}

