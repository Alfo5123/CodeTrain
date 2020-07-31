/*
    Problem:
    https://codeforces.com/problemset/problem/276/C

    Tutorial: https://www.youtube.com/watch?v=PqvxwtZ-AJ0

    Counter number of different elements in subarray [L R] queries
    Offline version.
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 30006;
const int Q = 200006;
const int MAXN = 1e6 + 5;
int n, q, start, finish, prefix, cur;
vector< pair<int,int> > queries[N];
int pre[MAXN];
int ans[Q];
vector<int> bit;  

int sum_query(int idx) 
{
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
}
int range_query(int l, int r) 
{
    return sum_query(r) - sum_query(l - 1);
}
void point_update(int idx, int delta) 
{
    for (; idx < n+1; idx += idx & -idx) bit[idx] += delta;
}

int main ()
{
    scanf("%d", &n);
    int a[n+1]; for(int i = 1; i <= n; i++)  scanf("%d", &a[i]);
    scanf("%d", &q);
    set<int> s;
    for(int i = 1; i <= q; i++)
    {
        scanf("%d %d", &start, &finish);
        s.insert(finish);
        queries[finish].push_back(make_pair(start, i));
    }

    memset(pre, -1, sizeof(pre));
    bit.assign(n+1, 0);
    cur = 0;

    for (set<int>::iterator it=s.begin(); it!=s.end(); ++it)
    {
        prefix = *it;

        // Update array
        for(int i = cur + 1; i <= prefix; i++)
        {
            if (pre[a[i]] != -1) point_update(pre[a[i]],-1); 
            pre[a[i]] = i; point_update(i,1);
        }

        cur = prefix;

        // Performn suffix queries
        for( int i = 0; i < queries[prefix].size(); i++)
            ans[queries[prefix][i].second] = range_query( queries[prefix][i].first,  prefix);    
    }

    for(int i = 1; i <= q; i++) 
        cout << ans[i] << endl;
        
    return 0;
}