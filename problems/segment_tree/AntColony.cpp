/*
    Problem:
    https://codeforces.com/contest/474/problem/F
    
    Implement a segment tree to do range minimum queries
    and gcd queries.
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 2000000000;

int a[MAXN];

int GCD( int a, int b )
{
    if ( b == 0 ) return a;
    return GCD( b , a % b );
}

struct Node
{
    int gcd, minn, cnt;
    Node(){};
    Node(int a, int b, int c)
    {
        gcd = a;
        minn = b;
        cnt = c;
    }
}t[4*MAXN];

int n, q, l , r, x;

Node merge( Node a, Node b )
{
    Node result;

    if ( a.minn > b.minn )
    {
        result.minn = b.minn;
        result.cnt = b.cnt;
    }
    else if ( a.minn < b.minn )
    {
        result.minn = a.minn;
        result.cnt = a.cnt;
    }
    else
    {
        result.minn = a.minn;
        result.cnt = a.cnt + b.cnt ;
    }

    if ( a.gcd == -1 ) result.gcd = b.gcd;
    else if ( b.gcd == -1 ) result.gcd = a.gcd;
    else result.gcd = GCD( a.gcd, b.gcd );

    return result;
}

void build(int v, int tl, int tr)
{
    if ( tl == tr )
    {
        t[v].gcd = a[tl];
        t[v].minn = a[tl];
        t[v].cnt = 1;
    }
    else
    {
        int tm = tl + (tr-tl)/2;
        build(2*v, tl, tm );
        build(2*v + 1, tm + 1, tr);
        t[v] = merge(t[2*v], t[2*v + 1]);
    }
}


Node query ( int v, int tl, int tr, int l , int r )
{
    if ( l > r ) return Node(-1, INF, 0);
    if ( tl == l && tr == r ) return t[v];
    int tm = tl + (tr-tl)/2;
    return merge(query(2*v, tl, tm, l, min(tm, r) ) , query(2*v+1, tm+1, tr, max(tm+1,l), r));
} 


int main()
{
    scanf("%d", &n );
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);

    scanf("%d", &q );
    while(q--)
    {
        scanf("%d %d", &l, &r);
        Node ans = query(1, 1, n, l , r );
        if ( ans.gcd == ans.minn ) cout << r - l + 1 - ans.cnt << endl;
        else cout << r - l + 1 << endl; 
    }
    return 0;
}