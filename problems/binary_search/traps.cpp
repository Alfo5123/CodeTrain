#include <bits/stdc++.h>
#define fst first
#define snd second
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii; 

/*
    Problem:
    https://codeforces.com/problemset/problem/1260/D
    
    Finding maximum value that satifies a property
*/


int m, n, k, t;
vector<int> l, r, d, a;

bool can(int x)
{
	int minn = int(1e9);
    FOR(i,0,x) minn = min(minn, a[i]);

	vector<ii> segm;
	FOR(i,0,k)
		if (d[i] > minn)
			segm.push_back(make_pair(l[i], r[i]));

	int req_time = 0;
	sort(segm.begin(), segm.end());
    ii s;
	int lastr = 0;
	for (int i = 0; i < segm.size(); i++)
	{
        s = segm[i];
		if (s.fst <= lastr)
		{
			req_time += max(0, s.snd - lastr);
			lastr = max(s.snd, lastr);
		}
		else
		{
			req_time += s.snd - s.fst + 1;
			lastr = s.snd;
		}
	}
	req_time = 2 * req_time + n + 1;
	return req_time <= t;
}


int main()
{
    FIN;
    cin >> m >> n >> k >> t;
    a.resize(m);
	FOR(i,0,m) cin >> a[i];
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());

	l.resize(k); r.resize(k); d.resize(k);
	FOR(i,0,k) cin >> l[i] >> r[i] >> d[i];

    int lo = 0;
    int hi = m;
    int ans = -1;
    int mid;

    while(lo <= hi)
    {
        mid = (hi-lo)/2 + lo;
        if ( can(mid) )  // Find the maximum element that satisfies the property
        {
            lo = mid + 1;
            ans = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }

    cout << ans << endl;
    return 0;
}