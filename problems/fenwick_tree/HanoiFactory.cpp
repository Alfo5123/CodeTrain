/*
    Problem:
    https://codeforces.com/contest/777/problem/E
    
*/


#include <bits/stdc++.h>
using namespace std;

int n;
int cnt;
vector<long long> bit;
map<int,int> m;
vector< pair< pair<int,int>, int> > v;


void update(int idx, long long val)
{
    for(; idx <= cnt; idx += idx & -idx) bit[idx] = max(bit[idx], val); 
}

long long point_query(int idx)
{
    long long res = 0;
    for(; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
    return res;
}


int main()
{
    cin >> n;
    int a, b, h;
    for(int i = 0; i < n; i++)
    {
        cin >> a >> b >> h;
        v.push_back(make_pair(make_pair(b, a), h));
        m[b] = 1; m[a] = 1;
    }

    // Sorting based on increasing outer radious
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    // Coordinate compression
    for(map<int,int> :: iterator it = m.begin();it != m.end();++ it) m[it -> first] = ++cnt;

    bit.assign(cnt+1, 0);
    // Longest Increasing Subsequence
    long long ans = 0;
    for ( int i = 0; i < n; i++)
    {
        long long q = point_query(m[v[i].first.first]-1);
        q += v[i].second;
        update(m[v[i].first.second], q);
        ans = max(ans, q);
    }
    cout << ans << endl;

    return 0;
}