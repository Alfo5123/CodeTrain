#include<bits/stdc++.h>
using namespace std;
 
const int N = 200005;
int n;
int q;
const int INF = 1e9+7;
int t[N << 2];
 
void update(int v, int tl, int tr, int pos, int new_val) 
{
    if (tl == tr) {
        t[v] = min(t[v], new_val);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = min(t[v*2], t[v*2+1]);
    }
}
 
int get(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return INF;
    if (l == tl && r == tr) 
        return t[v];
    int tm = (tl + tr) / 2;
    return min(get(v*2, tl, tm, l, min(r, tm)), 
                   get(v*2+1, tm+1, tr, max(l, tm+1), r));
}
 
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
 
    cin >> n >> q;
    memset(t, 0x3f, sizeof t);
    set<int> sick;
    for(int i=0; i<=n+1; i++) sick.insert(i);
    
    int l, r, t, ix, x;
    for(int i = 0; i < q; i++)
    {
    	cin >> t;
    	if ( t == 0 )
    	{
    		cin >> l >> r >> x ;
    		if (x) update(1, 1, n, l, r);
    		else sick.erase(sick.lower_bound(l),sick.upper_bound(r));
    	}
    	else
    	{
    		cin >> ix;
            if ( sick.find(ix) == sick.end() ) puts("NO");
            else
            {
                auto it = sick.find(ix);
                if(get(1,1,n,(*prev(it))+1,(*it))<(*next(it))) puts("YES");
                else puts("N/A");
            }
    	}
    }
	  return 0;
}
