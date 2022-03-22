#include<bits/stdc++.h>
using namespace std;

// Bracket Sequence Deletion
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t; cin >> t;
	while(t--)
	{
		int n; cin >> n;
		string s; cin >> s;
		int cnt = 0;
		int sz = 0;
		bool correct = true;
		int aux = 0;
		long long B = 27, MOD = 1000000007, POW = 1, hash1 = 0, hash2 = 0;
	
		for(int i = 0; i < n; i++)
		{
			if ( s[i] == '(' ) aux++;
			else aux--;
			if ( aux < 0) correct = false;
 
			sz++;
			hash1 = ( hash1 * B + s[i] - 'a' + 1) % MOD;
			hash2 = ( hash2 + (s[i] - 'a' + 1) * POW) % MOD;
			POW = (POW*B) % MOD;
			
			if ( (correct && aux==0) || (hash1==hash2 && sz>1 ) )
			{
				cnt++;
				sz = 0;
				aux = 0;
				correct = true;
				B = 27, POW = 1, hash1 = 0, hash2 = 0;
			}
		}
		cout << cnt << " " << sz << endl;
	}
	return 0;
}
