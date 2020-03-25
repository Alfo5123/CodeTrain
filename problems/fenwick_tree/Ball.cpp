/*
    Problem:
    https://codeforces.com/contest/12/problem/D

    Longest Increasing Subsequence for triplets

    Order by first coordinate, do sorted coordinate compression 
    for the second coordinate and then check that in the order 
    of the second coordinate, the third coordinate only finds
    increasing sequence                                 
*/
#include <bits/stdc++.h>
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;

int n;
int cnt;
int a, b, c ;
vector<int> bit;

void update(int idx, int val)
{
    for(; idx < n+1; idx += idx & -idx ) bit[idx] = max(val, bit[idx] );
}

int query(int idx)
{
    int res = 0;
    for(; idx > 0; idx -= idx & -idx ) res = max(bit[idx], res);
    return res;
}

map< int, int > m;

typedef struct tipo {
    int a, b, c;    
} ball;
 
ball v[500005];

bool comp (ball x, ball y) 
{
    if (x.a != y.a) return x.a > y.a;
    return x.b > y.b;
}

bool comp2( ball x, ball y)
{
    return x.b > y.b ;
}

int main()
{   
    FIN;
    cin >> n;
    int b[n];
    for(int i = 0; i < n; i++) cin >> v[i].a;
    for(int i = 0; i < n; i++) cin >> v[i].b;
    for(int i = 0; i < n; i++) cin >> v[i].c;

    // Coordinate compression in order of decreasing second coordinate 
    sort (v, v + n, comp2);
    for (int j = 0; j < n; j++) {
        if (m.find (v[j].b) == m.end ()) m[v[j].b] = ++cnt;
        v[j].b = m[v[j].b];
    } 
        
    // Sort array based on first two coordinates (decreasing order)
    sort(v, v+n, comp);

    bit.assign(n+1,0);
    int ans = 0;
    for ( int i = 0; i < n; i++)
    {
        if ( query(v[i].b-1) > v[i].c ) ans++;
        update(v[i].b, v[i].c);
    }
    cout << ans << endl;

    return 0;
}

