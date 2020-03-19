/*
    Problem:
    https://codeforces.com/contest/341/problem/B

    Longest Increasing Subsequence using Binary Index Tree for O(Nlog(N))


    For the general case

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int bit[n+1] = {0};
        vector<pair<int, int>> p(n);
        for (int i=0; i<n; i++) p[i] = make_pair(nums[i], -(i+1));
        sort(p.begin(), p.end());
        for (int i=0; i<n; i++) update(bit, n, -p[i].second, query(bit, n, -p[i].second) + 1);
        return query(bit, n);
    }

    
*/


#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> bit;

void update(int idx, int val)
{
    for(; idx < n+1; idx += idx & -idx) bit[idx] = max(bit[idx], val);
}

int max_query(int idx)
{
    int ans = 0;
    for(; idx > 0; idx -= idx & -idx) ans = max(ans, bit[idx]);
    return ans;
}

int main()
{   
    cin >> n;
    bit.assign(n+1,0);
    int a;
    for(int i = 0; i < n; i++)
    {
        cin >> a;
        update(a, max_query(a)+1);
    } 
    cout << max_query(n) << endl;

    return 0;
}