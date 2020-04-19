/*
    Problem:
    https://codeforces.com/problemset/problem/610/E
    
    Implement a segment tree to keep track of 
    first and last elements of segment and count
    frequencies of adjacent letters in each node.
    Perform range assignment updates with lazy propagation.
                               
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int n, m, k;
string s;

int t[4*MAXN][10][10], first[4*MAXN], last[4*MAXN], lazy[4*MAXN];


void build( int v, int tl, int tr )
{
    lazy[v] = -1;
    if ( tl == tr )
    {
        first[v] = (int)s[tl-1] - 'a';
        last[v] = (int)s[tl-1] -'a';
    }
    else
    {
        int tm = tl + (tr-tl)/2;
        build(2*v, tl, tm);
        build(2*v+1, tm+1, tr );

        first[v] = first[2*v];
        last[v] = last[2*v+1];

        for(int i = 0; i < k ; i++)
            for(int j = 0; j < k; j++)
                t[v][i][j] = t[2*v][i][j] + t[2*v+1][i][j];

        t[v][last[2*v]][first[2*v+1]]++;
    }
}

void push(int v, int tl, int tr);

void update( int v, int tl, int tr, int l, int r, int new_val )
{
    if ( l > r ) return;
    if ( l == tl && r == tr )
    {
        first[v] = new_val;
        last[v] = new_val;
        lazy[v] = new_val;

        for(int i = 0; i < k; i++)
            for(int j = 0; j < k; j++)
                t[v][i][j] = 0;
        t[v][new_val][new_val] = r - l;
    }
    else
    {
        push(v, tl, tr);
        int tm = tl + (tr-tl)/2;
        update(2*v, tl, tm, l, min(tm, r), new_val );
        update(2*v + 1, tm + 1, tr, max(tm + 1, l), r, new_val );

        first[v] = first[2*v];
        last[v] = last[2*v + 1];

        for(int i = 0; i < k; i++)
            for(int j = 0; j < k; j++)
                t[v][i][j] = t[2*v][i][j] + t[2*v+1][i][j];
        
        t[v][last[2*v]][first[2*v+1]]++;
    }
}

void push( int v, int tl, int tr )
{
    if ( lazy[v] != -1 )
    {
        int tm = tl + (tr-tl)/2;
        update(2*v, tl, tm, tl, tm, lazy[v]);
        update(2*v+1, tm+1, tr, tm+1, tr, lazy[v]);
        lazy[v] = -1;
    }
}

int main()
{
    cin >> n >> m >> k;
    cin >> s;
    build(1, 1, n);

    int type, l, r;
    char c;
    while(m--)
    {
        cin >> type;
        if ( type == 1 )
        {
            cin >> l >> r >> c;
            int x = (int)c - 'a';
            update(1, 1, n, l, r, x);
        }
        else
        {
            string s;
            cin >> s;
            int answer = 0;
            for( int i = 0; i < k; i++)
            {
                for(int j = i; j >= 0; j--)
                {
                    int fi = (int)(s[i] - 'a');
					int se = (int)(s[j] - 'a');
					answer += t[1][fi][se];
                }
            }
            answer++;
            cout << answer << endl;
        }
    }
    return 0;
}