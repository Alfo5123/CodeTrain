#include<bits/stdc++.h>
using namespace std;
 
#define N 100000
#define M 5
#define S 32
const int inf = 2 * 1e9 + 1;
 
int n, m;
pair<int, int> w[N];
map< vector<int>, int> mp;
int freq[N*S];
int setsize = 0;
int v[N][M];
int subsets[N][S];
vector<int> subset;
 
inline int sign(int i)  { return __builtin_popcount(i) & 1 ? 1 : -1;}
 
int union_size(int idx)
{
	int unionsz = 0;
	for (int mask = 1; mask < (1 << m); mask++)
		unionsz += sign(mask) * freq[subsets[idx][mask]];
	return unionsz;
}
 
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	int cnt = 0;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++) cin >> v[i][j];
		sort(v[i],v[i]+m);
		
		for(int mask = 1; mask < 1<<m; mask++)
		{
		    subset.clear();
			for(int j = 0; j < m; j++)
				if ( (1<<j) & mask ) subset.push_back(v[i][j]);
			
			auto [it, success] = mp.try_emplace(subset, cnt+1);
			if (success) cnt++;
			subsets[i][mask] = it->second;
		}
		cin >> w[i].first; w[i].second = i;
	}
	
	sort(w, w + n);
	int sol = inf;
	for(int r = 0; r < n; r++)
	{
		if (w[r].first + w[0].first >= sol) break;
		
		if ( union_size(w[r].second) < setsize )
		{
			while (setsize > 0) 
			{
		        int l = setsize - 1;
				for ( int mask = 1; mask < (1<<m); mask++) 
					freq[subsets[w[l].second][mask]]--;
				setsize--;
		        
		        if (union_size(w[r].second) == setsize) 
		        {
		          sol = min(sol, w[l].first + w[r].first); break;
		        }
	        }
		}
		
		if ( sol == inf )
		{
			for ( int mask = 1; mask < (1<<m); mask++) 
				freq[subsets[w[r].second][mask]]++;
			setsize++;
		}
	}
	cout << (sol == inf ? -1 : sol) << endl;
	return 0;
}
