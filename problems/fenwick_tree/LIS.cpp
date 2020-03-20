/*

Longest Increasing Subsequence using BIT O(N log N )

Two approaches:
    - Creating a mapping via sorting pairs of elements and indices that preservers the LIS
    - Using coordinate compression ( no sorting needed )

References:
    - https://codeforces.com/blog/entry/8761
    - https://www.geeksforgeeks.org/longest-increasing-subsequence-using-bit/

*/


#include <bits/stdc++.h>
using namespace std;

int n;
int cnt;
vector<int> bit;
vector<int> bit2;

void update(int idx, int val)
{
    for(; idx < n+1; idx += idx & -idx) bit[idx] = max(bit[idx], val);
}

int query(int idx)
{
    int ans = 0;
    for(; idx > 0; idx -= idx & -idx) ans = max(ans, bit[idx]);
    return ans;
}

void update2(int idx, int val)
{
    for(; idx <= cnt; idx += idx & -idx) bit2[idx] = max(bit2[idx], val);
}

int query2(int idx)
{
    int ans = 0;
    for(; idx > 0; idx -= idx & -idx) ans = max(ans, bit2[idx]);
    return ans;
}

int lengthOfLIS(vector<int>& nums)
{
        bit.assign(n+1,0);
        vector< pair<int, int> > p(n);
        for (int i=0; i<n; i++) p[i] = make_pair(nums[i], -(i+1));
        sort(p.begin(), p.end());
        for (int i=0; i<n; i++) update(-p[i].second, query(-p[i].second) + 1);
        return query(n);
}

int lengthOfLIS2(vector<int>& nums)
{
        map<int, int> m;
        for( int i = 0; i < n; i++) m[nums[i]] = 1;
        for(map<int,int> :: iterator it = m.begin();it != m.end();++ it) m[it -> first] = ++cnt;
        bit2.assign(cnt+1,0);
        int ans = 0;
        for (int i=0; i<n; i++) 
        {
            int q = query2(m[nums[i]]-1) + 1;
            update2(m[nums[i]], q);
            ans = max(ans, q);
        }
        return ans;
}

int main()
{   
    cin >> n;
    vector<int> v;
    int a;
    for(int i = 0; i < n; i++) 
    {
        cin >> a;
        v.push_back(a);
    }
    cout << lengthOfLIS(v) << endl;
    cout << lengthOfLIS2(v) << endl;

    return 0;
}

