/*
    Problem:
    https://codeforces.com/contest/1313/problem/C2
    
    Implement a segment tree to do RMQ to return index
    and apply it to a problem recursively. 
                               
*/

#include<bits/stdc++.h>
using namespace std;

long long ar[500005] , res[500005] ;
int st[4*500005] , n;
 
void build(int v, int tl, int tr )
{
    if (tl == tr) st[v] = tl;
    else
    {
        int tm = tl + (tr - tl)/2;
        build(2*v, tl, tm);
        build(2*v + 1, tm + 1, tr);
        int x = st[2*v];
        int y = st[2*v+1];
        if ( ar[x] <= ar[y] ) st[v] = x;
        else st[v] = y;
    }
}
 
int getmin( int v, int tl, int tr, int l, int r)
{
    if ( r < l ) return 0;
    if ( l == tl && r == tr ) return st[v];
    int tm = tl + (tr - tl)/2;
    int x = getmin(v*2, tl, tm, l, min(r, tm) ) ;
    int y = getmin(v*2+1, tm+1, tr, max(l, tm+1), r) ;
    if ( ar[x] <= ar[y] ) return x;
    return y;
}
 
long long getAns(int L , int R)
{
	if(L > R) return 0;
	if(L == R) return res[L] = ar[L];
	
	int idx = getmin(1, 1, n, L, R);
	res[idx] = ar[idx];

	long long x = (idx - L + 1) * ar[idx] + getAns(idx + 1 , R);
	long long y = (R - idx + 1) * ar[idx] + getAns(L , idx - 1);
	
	if(x >= y) for(int i = L; i <= idx; i++) res[i] = ar[idx];
	else	   for(int i = idx; i <= R; i++) res[i] = ar[idx];
	return max(x , y);
}
 
int main()
{
	cin >> n;
    ar[0] = INT_MAX;
    for(int i = 1; i <= n; i++) cin >> ar[i];
    build(1, 1, n);
    getAns(1, n);
    for( int i = 1; i <= n; i++) cout << res[i] <<  " ";
    cout << endl;
    return 0;
}