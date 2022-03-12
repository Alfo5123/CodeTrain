#include<bits/stdc++.h>
using namespace std;

vector<int> num;
long long a, b;
int k;
int dp[40][85][85][2];

int dp_call(int pos, int residue_sum, int residue_digit, int is_smaller)
{
	if (pos==num.size())
	{
		if (residue_sum == 0 && residue_digit == 0 ) return 1;
		else return 0;
	}
	
	if ( dp[pos][residue_sum][residue_digit][is_smaller] != -1) 
		return dp[pos][residue_sum][residue_digit][is_smaller] ;
	
	int answer = 0;
	int mx = is_smaller ? 9 : num[pos];
	for(int i = 0; i < mx; i++) 
		answer += dp_call(pos+1, (residue_sum*10+i)%k,(residue_digit+i)%k, 1);
		
	if (is_smaller) answer += dp_call(pos+1, (residue_sum*10+mx)%k,(residue_digit+mx)%k, 1);
	else answer += dp_call(pos+1, (residue_sum*10+mx)%k,(residue_digit+mx)%k, 0);
	
	return dp[pos][residue_sum][residue_digit][is_smaller] = answer;
}

int solve(long long x)
{
	num.clear();
	while(x>0){
        num.push_back(x%10);
        x/=10;
    }
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof(dp));
    return dp_call(0, 0, 0, 0);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin >> T;
	for(int x = 1; x <= T; x++)
	{
		cin >> a >> b >> k;
		if ( a > b ) swap(a,b);
		if (k == 1)
			cout << "Case " << x << ": " << b-a+1 << endl;
		else if (k > 81)
			cout << "Case " << x << ": " << 0 << endl;
		else
			cout << "Case " << x << ": " << solve(b)-solve(a-1) << endl;
	}
	return 0;
}
