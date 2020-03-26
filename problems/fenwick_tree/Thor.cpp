/*
    Problem:
    https://codeforces.com/contest/704/problem/A                              
*/

#include <bits/stdc++.h>
using namespace std;
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

const int N = 3e5 + 13;
int n;
int bit[N];
vector< vector<int> > v(N);

void update(int idx, int val)
{
    for(;idx < N+1; idx += idx & -idx) bit[idx] += val;
}

int query(int idx)
{
    int res = 0;
    for(; idx > 0; idx -= idx & -idx) res += bit[idx];
    return res;
}

int main()
{
    FIN;
    cin >> n;
    int q; cin >> q;
    int type, t, x;
    int last = 0;
    t = 0;
    for(int i = 1; i <= q; i++)
    {
        cin >> type >> x;
        if (type == 1)
        {
            v[x].push_back(++t);
            update(t, 1);
        }
        else if ( type == 2)
        {
            for(int u = 0; u < v[x].size(); u++) 
                if ( v[x][u] > last ) update(v[x][u], -1);
            v[x].clear();
        }
        else
        {
            if (x > last)
            {
                update(1, - query(x) + query(last));
                last = x;
            }
        }

        cout << query(t) << endl;
        
    }
    return 0;
}
