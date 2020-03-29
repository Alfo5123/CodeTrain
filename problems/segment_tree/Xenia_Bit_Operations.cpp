/*
    Problem:
    https://codeforces.com/contest/339/problem/D

    Implementation of Segment tree, with alternating merge operation 
    at each level.
                               
*/
#include <bits/stdc++.h>
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;


const int MAXN = (1<<17) + 5;
int t[4*MAXN];
int n, m, p, q;
bool xorOp[4*MAXN];

void build(int a[], int v, int tl, int tr)
{
    if ( tl == tr ) t[v] = a[tl];
    else
    {
        int tm = tl + (tr - tl)/2;
        build(a, 2*v, tl, tm);
        build(a, 2*v+1, tm+1, tr);
        if ( xorOp[v] ) t[v] = t[2*v] ^ t[2*v+1];
        else t[v] = t[2*v] | t[2*v+1];
    }
}

void update( int v, int tl, int tr, int pos, int val)
{
    if ( tl == tr ) t[v] = val;
    else
    {
        int tm = tl + (tr - tl)/2;
        if ( pos <= tm) update(2*v, tl, tm, pos, val);
        else update(2*v + 1, tm + 1, tr, pos, val);
        if ( xorOp[v] ) t[v] = t[2*v] ^ t[2*v+1];
        else t[v] = t[2*v] | t[2*v+1];
    }
}

int query( int v, int tl, int tr, int l, int r)
{
    if ( l > r ) return 0;
    if ( l == tl && r == tr ) return t[v];
    int tm = tl + (tr - tl)/2;
    int x1 = query(2*v, tl, tm, l, min(r, tm));
    int x2 = query(2*v+1, tm+1, tr, max(l, tm+1), r);
    if ( xorOp[v] ) return  x1 ^ x2 ;
    return x1 | x2;
}

int main()
{
    FIN;
    cin >> n >> m;
    int a[(1<<n) + 1];
    for(int i = 1; i <= 1<<n; i++ ) cin >> a[i];

    if(n%2==0) xorOp[1] = 1;
    else xorOp[1] = 0;

    for(long long i = 1; i <= (1<< (n+1)); i++)
    {
        if(xorOp[i]==1)
        {
            xorOp[i*2] = 0;
            xorOp[i*2+1] = 0;
        }
        else
        {
            xorOp[i*2] = 1;
            xorOp[i*2+1] = 1;
        }
    }
    n = 1<<n;
    build(a, 1, 1, n);
    for(int i = 0; i < m; i++)
    {
        cin >> p >> q; 
        update(1, 1, n, p, q);
        cout << query(1, 1, n, 1, n) << endl;
        
    }
    return 0;
}

