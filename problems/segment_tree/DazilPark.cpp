/*
    Problem:
    https://codeforces.com/contest/515/problem/E
    
    Rephrase the problem from circle to line and apply
    RMQ using two segment trees for dividing the objective
    function.
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const long long INF=1LL<<56;

struct Node
{
    long long val, v0, v1;
    Node(){}
    Node(long long a, long long b, long long c)
    {
        val=a;
        v0=b;
        v1=c;
    }
}t[4*MAXN];

Node merge( Node a , Node b )
{
    Node result;
    result.val = max( max( a.val, b.val ), a.v0 + b.v1 );
    result.v0 = max( a.v0, b.v0 );
    result.v1 = max( a.v1, b.v1 );
    return result;
}

long long L[2*MAXN], R[2*MAXN], d[2*MAXN], h[2*MAXN];
int n, m;

void build(int v, int tl, int tr )
{
    if ( tl == tr )
    {
        t[v].val = -INF;
        t[v].v0 =  L[tl];
        t[v].v1 = R[tl];
    }
    else
    {
        int tm = tl + (tr - tl)/2;
        build(2*v, tl, tm);
        build(2*v + 1, tm + 1, tr);
        t[v] = merge( t[2*v], t[2*v + 1] );
    }
}


Node query( int v, int tl, int tr, int l, int r )
{
    if ( l > r ) return Node(-INF, -INF, -INF);
    if ( l == tl && r == tr ) return t[v];
    int tm = tl + (tr - tl)/2;
    return merge( query(2*v, tl, tm, l, min(r, tm)), query(2*v + 1, tm + 1, tr, max(l, tm+1), r) );
}

int main()
{
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= n; i++)  { scanf("%lld", &d[i]); d[i+n] = d[i]; }
    for(int i = 1; i <= n; i++)  { scanf("%lld", &h[i]); h[i+n] = h[i]; }
    for(int i = 1; i <= n; i++ ) d[i] += d[i-1];
    for(int i = 1; i <= n; i++ ) d[i+n] = d[i] + d[n];

    for(int i = 1; i <= 2*n; i++) L[i] = 2*h[i] - d[i-1];
    for(int i = 1; i <= 2*n; i++) R[i] = d[i-1] + 2*h[i];

    build(1, 1, 2*n);
    
    int a, b;
    long long ans;
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        if ( a <= b ) a += n;
        ans = query(1, 1, 2*n, b + 1, a - 1).val;
        cout << ans << endl;
    }
    
    return 0;
}