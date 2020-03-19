/*
    Problem:
    https://codeforces.com/problemset/problem/276/C

    Queries to update range 
*/

#include <bits/stdc++.h> 
using namespace std;
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)


int n, q;
int l, r;
vector<long long> bit;


void point_update(int idx, long long x)
{
    for(; idx < n+1; idx += idx & -idx) bit[idx] += x;
}

void range_update(int l, int r, int x)
{
    point_update(l, x);
    point_update(r+1, -x);
}

int point_query(int idx)
{
    long long ret = 0;
    for(; idx > 0; idx -= idx & -idx ) ret += bit[idx];
    return ret;
}


int main()
{
    FIN;
    cin >> n >> q;
    long long a[n]; for(int i = 0; i < n; i++) cin >> a[i];
    bit.assign(n+1, 0);
    for(int i = 0; i < q; i++) 
    {
        cin >> l >> r;
        range_update(l, r, 1);
    }

    long long b[n]; for( int i = 0; i < n; i++) b[i] = point_query(i+1);

    sort(a, a+n);
    sort(b, b+n);

    long long answer = 0;
    for( int i = 0; i < n; i++) answer += a[i] * b[i] ;
    cout << answer << endl;

    return 0;
}