#include<bits/stdc++.h>
using namespace std;
 
int m, d;
string a, b;
 
int dp[2005][2005][2][2];
const int MOD = 1e9+7;
 
int solve( int pos, int rem, bool left, bool right)
{
	if ( pos == a.size()) return rem==0;
	
	if ( dp[pos][rem][left][right] != -1)
		return dp[pos][rem][left][right];
	
	int answer = 0;
	int left_limit = left==0? a[pos]-'0': 0;
	int right_limit = right==0? b[pos]-'0': 9;
	
	for(int i = left_limit; i <= right_limit; i++)
	{
		if ( (pos & 1) ^ (i == d) ) continue;
		answer += solve( pos + 1, (rem*10 + i)%m, left||(i>a[pos]-'0'), right||(i<b[pos]-'0'));
		answer %= MOD;
	}
	
	return dp[pos][rem][left][right] = answer;
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> m >> d;
	cin >> a >> b;
	memset(dp,-1,sizeof(dp));
	cout << solve(0, 0, 0, 0) << endl;
	return 0;
}
