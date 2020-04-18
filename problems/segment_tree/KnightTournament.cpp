#include<bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
int st[4*MAXN];

int n, m;

void update( int v, int tl, int tr, int l, int r, int val )
{
    if ( st[v] != 0 || l > r) return;
    if (tl == l && tr == r ) st[v] = val;
    else 
    {
        int tm = tl + (tr - tl)/2 ;
        update(2*v, tl, tm, l, min(r, tm), val );
        update(2*v+1, tm+1, tr, max(tm+1, l), r, val );
    }
}

void solve(int v, int tl, int tr, int val)
{
    if (tl == tr)  printf("%d ", val) ;
    else
    {
        int tm = tl + ( tr - tl )/2;
        solve( 2*v , tl, tm ,  (st[2*v] == 0)?val:st[2*v]  );
        solve( 2*v + 1, tm + 1, tr, (st[2*v+1] == 0)?val:st[2*v+1] );
    }   
}

int main()
{
    scanf("%d %d", &n, &m);
    int l, r, x;
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &l, &r, &x);
        update(1, 1, n, l, x-1, x );
        update(1, 1, n, x+1, r, x );
    }
    solve(1,1,n,st[1]);
    return 0;
}