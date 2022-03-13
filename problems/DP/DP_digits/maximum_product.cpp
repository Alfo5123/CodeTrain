#include<bits/stdc++.h>
#define int long long int
using namespace std;
 
int a, b;
int val;
string sa, sb;
 
string tostring(int x)
{
	string answer = "";
	while(x>0)
	{
		answer = (char)('0' + x%10) + answer;
		x /= 10;
	}
	return answer;
}
 
void removeLeadingZeros(string str)
{
    const regex pattern("^0+(?!$)");
    str = regex_replace(str, pattern, "");
    cout << str << endl;
}
 
pair<int, string> dp[20][2][2];
 
pair<int, string> solve(int pos, int left, int right)
{
	if ( pos ==  sa.size() ) return {1, ""};
	if ( dp[pos][left][right].first != -1) return dp[pos][left][right];
	int left_limit = left == 0? sa[pos]-'0':0;
	int right_limit = right == 0? sb[pos]-'0':9;
	int answer = -1;
	string s = "";
	for(int i = left_limit; i <= right_limit; i++)
	{
		int val = i;
		pair<int, string> temp = solve(pos+1, left||i>sa[pos]-'0', right||i<sb[pos]-'0');
		if ( val * temp.first > answer )
		{
			answer = val * temp.first ;
			s = temp.second;
			s.push_back('0'+i);
		}
	}
	
	return dp[pos][left][right] = {answer, s};
}
 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> a >> b;
 
	sa = tostring(a);
	sb = tostring(b);
	
	if ( sa.size() < sb.size())
	{
		reverse(sa.begin(), sa.end());
		while(sa.size() < sb.size()) sa.push_back('0');
		reverse(sa.begin(), sa.end());
	}
	
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
					dp[i][j][k].first = -1;
        pair<int, string> answer = solve(0, 0, 0);
        reverse(answer.second.begin(), answer.second.end());
        removeLeadingZeros(answer.second);
	return 0;
}
