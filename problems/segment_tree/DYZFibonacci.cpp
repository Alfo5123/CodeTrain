/*
    Problem:
    https://codeforces.com/contest/446/problem/C
    
    Implement a segment tree with lazy propagation to 
    do range sum updates and queries
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MOD = 1000000009;
const int MAXN = 300005;

int st[4*MAXN], lazy1[4*MAXN], lazy2[4*MAXN], Fib[MAXN], left_[4*MAXN], right_[4*MAXN];
int n, m;

inline int fib(int i)
{
	if (i >= 0) return Fib[i];
	else if (i & 1) return Fib[-i];
	else return (MOD - Fib[-i]) % MOD;
}

inline int fs(int l, int r) 
{
	return (fib(r + 2) - fib(l + 1) + MOD) % MOD;
}

void P(int i, int x, int y) 
{
	st[i] = (st[i] + ( (long long)x * fs(left_[i], right_[i]) % MOD )+ ( (long long)y * fs(left_[i] - 1, right_[i] - 1) ) % MOD ) % MOD;
	lazy1[i] = (lazy1[i] + x) % MOD;
    lazy2[i] = (lazy2[i] + y) % MOD;
}

void build(int v, int l, int r) 
{
	left_[v] = l, right_[v] = r;
	if (l == r) return void(scanf("%d", &st[v]));
    int tm = (l + r)/2;
	build(2*v, l, tm);
	build(2*v+1, tm + 1, r);
	st[v] = (st[2*v] + st[2*v + 1]) % MOD;
}

void push(int v) 
{
    if ( lazy1[v] || lazy2[v] )
    {
        P(2*v, lazy1[v], lazy2[v] );
        P(2*v + 1, lazy1[v], lazy2[v] );
        lazy1[v] = 0;
        lazy2[v] = 0;
    }
}

void update(int v, int a, int b) 
{
    if (right_[v] < a || b < left_[v]) return;
	if (a <= left_[v] && right_[v] <= b) return P(v, fib(2 - a), fib(1 - a));
	push(v);
    update(2*v, a, b);
    update(2*v + 1, a, b);
    st[v] = ( st[2*v] + st[2*v + 1] ) % MOD;
}

int query(int v, int tl, int tr, int l, int r) 
{
    if (l > r) return  0;
    if (tl >= l && r >= tr) return st[v];
    push(v);
    int tm = tl + (tr - tl)/2;
    return (query(v*2, tl, tm, l, min(r, tm)) % MOD + query(v*2 + 1, tm+1, tr, max(tm+1, l), r) % MOD ) % MOD;
}

int main()
{
    cin >> n >> m;
    build(1, 1, n);
    Fib[0] = 0, Fib[1] = 1;
	for (int i = 2; i <= n + 2; ++i) Fib[i] = (Fib[i - 1] + Fib[i - 2]) % MOD;

    int type, l, r;
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &type, &l, &r);
        if ( type == 1 ) update(1, l, r);
        else cout << query(1, 1, n, l, r) << endl;
    }

    return 0;
}