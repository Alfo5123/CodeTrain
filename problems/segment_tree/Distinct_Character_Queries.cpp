/*
    Problem:
    https://codeforces.com/contest/1234/problem/D
    
    Implement a segment tree for each letter in the alphabet
                               
*/
#include <bits/stdc++.h>
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;

const int MAXN = 100005;
int t[26][4*MAXN];
string s;
int q, qt, x, y, pos;
char c;

int query(int v, int tl, int tr, int l, int r, int idx )
{
    if ( r < l ) return 0;
    if ( l == tl && r == tr ) return t[idx][v];
    int tm = tl + (tr - tl)/2;
    return query(2*v, tl, tm, l, min(r, tm), idx) + query(2*v+1, tm+1, tr, max(l, tm+1), r, idx);
}

void update( int v, int tl, int tr, int pos, int newval, int idx )
{
    if (tl == tr) t[idx][v] = newval;
    else
    {
        int tm = tl + (tr - tl)/2;
        if (pos <= tm) update(2*v, tl, tm, pos, newval, idx );
        else update(2*v+1, tm+1, tr, pos, newval, idx);
        t[idx][v] = t[idx][2*v] + t[idx][2*v+1];
    }
}

int main()
{
    FIN;
    cin >> s;
    int n = s.size();
    for( int i = 0; i < n; i++) 
        update( 1, 0, n-1, i, 1, (s[i] - 'a'));

    cin >> q;
    for(int i = 0; i < q; i++)
    {
        cin >> qt ;
        if ( qt == 1 )
        {
            cin >> pos >> c;
            update(1, 0, n-1, pos-1, 0, (s[pos-1] - 'a'));
            s[pos-1 ] = c;
            update(1, 0, n-1, pos-1, 1, (c - 'a'));
        }
        else
        {
            cin >> x >> y;
            int ans = 0;
            for(int j = 0; j < 26; j++)
                ans += ( query(1, 0, n-1, x-1, y-1, j)!=0 );
            cout << ans << endl;
        }
        
    }
    return 0;
}

