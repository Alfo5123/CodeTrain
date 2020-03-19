/*
    Problem:
    https://codeforces.com/contest/669/problem/E

    BIT for point updates, range queries
*/

#include <bits/stdc++.h> 
using namespace std;
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)


int n;
int tot;
map<int,int> vis;
map<int,map<int,int> > g;

void update(int time, int idx, int val )
{
    for(; idx < int(1e9+5); idx += idx & -idx ) g[time][idx] += val;
}

int query(int time, int idx)
{
    int res = 0;
    for(; idx > 0; idx -= idx & -idx ) res += g[time][idx];
    return res;
}

int main()
{
    FIN;
    int a, t, x;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> a >> t >> x;
        if ( a == 1 && !vis[x])
        {
            vis[x] = ++tot;
        }
        if ( a == 1 )
        {
            update(vis[x], t, +1);
        }
        if ( a == 2 )
        {
            update(vis[x], t, -1);
        }
        if ( a == 3 )
        {
            cout << query(vis[x], t) << endl;
        }
        
    }
    
    return 0;
}