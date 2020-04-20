/*
    Problem:
    https://codeforces.com/problemset/problem/558/E
    
    Implement a segment tree to keep track of 
    frequency of characters in string to perform
    count sorting on each query.
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int st[26][4*MAXN], lazy[26][4*MAXN];
int n, q;
string s;

void build( int v, int tl, int tr )
{
    for(int i = 0; i < 26; i++) lazy[i][v] = -1;
    if ( tl == tr ) st[(int)s[tl-1] - 'a'][v]++;
    else
    {
        int tm = tl + (tr - tl)/2;
        build( 2*v, tl, tm );
        build( 2*v + 1, tm + 1, tr );

        for(int i = 0; i < 26; i++)
            st[i][v] = st[i][2*v] + st[i][2*v+1]; 
    }
}

void push(int v, int letter)
{
    if ( lazy[letter][v] != -1 )
    {
        st[letter][2*v] = (lazy[letter][v]+1)/2;
        st[letter][2*v + 1] = lazy[letter][v]/2;
        lazy[letter][2*v] = (lazy[letter][v]+1)/2;
        lazy[letter][2*v+1] = lazy[letter][v]/2;
        lazy[letter][v] = -1;
    }
}

int query( int v, int tl, int tr, int l, int r, int letter )
{
    if ( l > r ) return 0;
    if ( l <= tl && tr <= r ) return st[letter][v];
    push(v, letter);
    int tm = tl + (tr - tl)/2;
    return query( 2*v, tl, tm, l, min(r, tm), letter) + query(2*v + 1, tm + 1 , tr, max(l, tm+1), r, letter);
}

void update( int v, int tl, int tr, int l, int r, int letter, int value )
{
    if ( l > r ) return;
    if ( l == tl && tr == r ) 
    {
        st[letter][v] = (tr - tl + 1) * value;
        lazy[letter][v] = (tr - tl + 1) * value;
    }
    else
    {
        push(v, letter);
        int tm = tl + (tr-tl)/2;
        update(2*v, tl, tm, l, min(r, tm), letter, value);
        update(2*v+1, tm+1, tr, max(l, tm+1), r, letter, value);
        st[letter][v] = st[letter][2*v] + st[letter][2*v+1]; 
    }
}

int main()
{
    cin >> n >> q;
    cin >> s;
    build(1, 1, n);
    int lq, rq, kq;
    
    for(int q_ = 1; q_ <= q; q_++)
    {
        cin >> lq >> rq >> kq;
        int cnt[26];
        for(int i = 0; i < 26; i++) cnt[i] = query(1, 1, n, lq, rq, i);

        int cur = kq?lq:rq;

        for ( int i = 0; i < 26; i++)
        { 
            if ( !cnt[i] ) continue;
            update(1, 1, n, lq, rq, i, 0);
            if (kq == 1 )
            {
                update(1, 1, n, cur, cur+cnt[i]-1, i, 1);
                cur += cnt[i];
            }
            else
            {
                update(1, 1, n, cur-cnt[i]+1, cur, i, 1);
                cur -= cnt[i];
            }
        }
    }

    string answer = "";
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 26; j++)
        {
            if ( query(1, 1, n, i+1, i+1, j) > 0 )
            {
                answer += char(j+'a');
            }
        }
    }
    cout << answer << endl;

    return 0;
}