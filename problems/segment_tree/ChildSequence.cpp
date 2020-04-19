/*
    Problem:
    https://codeforces.com/contest/438/problem/D
    
    Implement a segment tree to do range 
    maximum query and sum, to perform updates
     in single points and range updates for modulo.
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = 1LL<<56;

struct Node
{
    long long maxx, sum;
    Node(){};
    Node(long long a, long long b)
    {
        maxx = a;
        sum = b;
    }
} t[4*MAXN];

Node merge( Node a, Node b )
{
    Node result;
    result.maxx = max( a.maxx, b.maxx );
    result.sum = a.sum + b.sum ;
    return result;
}

long long a[MAXN];
int n, m;

void build( int v, int tl, int tr )
{
    if ( tl == tr )
    {
        t[v].maxx = a[tl];
        t[v].sum = a[tl];
    }
    else
    {
        int tm = tl + (tr-tl)/2;
        build(2*v, tl, tm);
        build(2*v + 1, tm+1, tr);
        t[v] = merge(t[2*v], t[2*v + 1]);
    } 
}

Node query( int v, int tl, int tr, int l, int r )
{
    if ( l > r ) return Node(-INF, 0LL);
    if ( tl == l && tr == r ) return t[v];
    int tm = tl + (tr-tl)/2;
    return merge(query(2*v, tl, tm, l, min(r, tm)), query(2*v+1, tm+1, tr, max(tm+1, l), r) );
}

void update_mod(int v, int tl, int tr, int l, int r, int val )
{
    if ( l > r ) return ;
    if ( tl == tr ) 
    {
        if ( t[v].maxx >= val )
        {
            t[v].maxx %= val;
            t[v].sum %= val;
        }
    }
    else
    {
        int tm = tl + (tr-tl)/2;
        if ( query(2*v, tl, tm, l, min(r, tm) ).maxx >= val ) 
            update_mod(2*v, tl, tm, l, min(r, tm), val);
        if ( query(2*v+1, tm+1, tr, max(l, tm+1), r).maxx >= val )
            update_mod(2*v+1, tm+1, tr, max(l, tm+1), r, val); 
        t[v] = merge(t[2*v], t[2*v+1]);
    }
}

void modify( int v, int tl, int tr, int pos, int val)
{
    if ( tl == tr )
    {
        t[v].maxx = val;
        t[v].sum = val;
        return;
    }
    else
    {
        int tm = tl + (tr-tl)/2;    
        if ( pos <= tm ) modify( 2*v, tl, tm, pos, val );
        else modify(2*v+1, tm+1, tr, pos, val);
        t[v] = merge(t[2*v], t[2*v+1] );
    }   
}

int main()
{   
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);

    int type, l, r, k, x;
    for(int i = 0; i < m; i++)
    {
        cin >> type;
        if ( type == 1 )
        {
            cin >> l >> r ;
            cout << query(1, 1, n, l, r).sum << endl;
        }
        else if ( type == 2 )
        {
            cin >> l >> r >> x ;
            update_mod(1, 1, n, l, r, x );
        }
        else 
        {
            cin >> k >> x;
            modify(1, 1, n, k, x );
        }
    }

    return 0;
}