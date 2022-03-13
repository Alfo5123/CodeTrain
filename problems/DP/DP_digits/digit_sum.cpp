#include<bits/stdc++.h>
using namespace std;

string sa, sb;
long long a, b;
long long dp[20][200][2][2];

string tostring(long long x)
{
	string answer = "";
	while(x>0)
	{
		answer = (char)('0' + x%10) + answer;
		x /= 10;
	}
	return answer;
}

long long solve(int pos, int sum, int left, int right)
{
	if ( pos == sa.size() ) return sum;
	if( dp[pos][sum][left][right] != -1) return dp[pos][sum][left][right];
	int left_limit = left == 0?sa[pos]-'0':0;
	int right_limit = right == 0?sb[pos]-'0':9;
	long long answer = 0;
	for(int i = left_limit; i <= right_limit; i++)
		answer += solve(pos+1, sum+i, left||i>sa[pos]-'0', right||i<sb[pos]-'0');
	return dp[pos][sum][left][right] = answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while(t--)
	{
		cin >> a >> b;
		sa = tostring(a);
		sb = tostring(b);
		
		if ( sa.size() < sb.size())
		{
			reverse(sa.begin(), sa.end());
			while(sa.size() < sb.size()) sa.push_back('0');
			reverse(sa.begin(), sa.end());
		}
		memset(dp, -1, sizeof(dp));
		cout << solve(0, 0 , 0, 0) << endl;
	}
	
	return 0;
}
