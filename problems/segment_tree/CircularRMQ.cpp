/*
    Problem:
    https://codeforces.com/problemset/problem/52/C
    
    Implement a segment tree to do range minimum queries
    in a circular array 
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200005 ;
const long long INF = 1LL<<56;

long long t[4*MAXN], lazy[4*MAXN], a[MAXN];
int n, m, x;

void build( int v, int tl, int tr )
{
    if ( tl == tr )  t[v] = a[tl]; 
    else
    {
        int tm = tl + (tr - tl)/2;
        build(2*v, tl, tm );
        build(2*v + 1, tm + 1, tr );
        t[v] = min( t[2*v], t[2*v + 1] );
    }
}   

void push( int v )
{
    t[2*v] += lazy[v];
    lazy[2*v] += lazy[v];
    t[2*v+1] += lazy[v];
    lazy[2*v+1] += lazy[v];
    lazy[v] = 0;
}

void update( int v, int tl, int tr, int l, int r, long long x )
{
    if ( l > r ) return ;
    if ( l == tl && r == tr ) 
    {
        t[v] += x;
        lazy[v] += x;
    }
    else
    {
        push(v);
        int tm = tl + (tr-tl)/2;
        update( 2*v, tl, tm, l, min(r, tm), x );
        update( 2*v+1, tm+1, tr, max(l, tm+1), r, x );
        t[v] = min( t[2*v], t[2*v+1]);
    }
}

long long query( int v, int tl, int tr, int l, int r )
{
    if ( l > r ) return INF;
    if ( tl == l && tr == r ) return t[v];
    int tm = tl + (tr - tl)/2;
    push(v);
    return min( query(2*v, tl, tm, l, min(r, tm) ), query(2*v+1, tm+1, tr, max(tm+1, l), r) );

}

int main()
{
    scanf("%d", &n );
    for(int i = 1; i <= n; i++) cin >> a[i] ;

    build(1, 1, n);

    scanf("%d", &m );
    int l, r, var;
    string str;
    
    while(m >= 0)
    {
        m--;
        getline(cin, str);
		stringstream ss(str);
        
        vector<int> v;
		while (ss >> var)
			v.push_back(var);
		
		if (v.size() == 0) continue;
        
        if ( v.size() == 2 ) 
        {
            l = v[0] + 1;
            r = v[1] + 1;
            if ( l <= r ) cout << query(1, 1, n, l, r) << endl;
            else cout << min( query(1, 1, n, l, n ) , query(1, 1, n, 1 , r) ) << endl;
        }
        else if ( v.size() == 3 )
        {
            l = v[0] + 1;
            r = v[1] + 1;
            if (l <= r ) update(1, 1, n, l, r, v[2] );
            else { update(1, 1, n, l, n, v[2]); update(1, 1, n, 1, r, v[2]); }
        }
    
    }

    return 0;
}