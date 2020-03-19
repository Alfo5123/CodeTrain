#include <bits/stdc++.h> 
using namespace std;

vector<int> bit;  // binary indexed tree
int N = 10 ; // N 

/* 

########    Point Update & Range Query

int sum_query(int idx) 
{
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
}

int range_query(int l, int r) 
{
    return sum_query(r) - sum_query(l - 1);
}

void point_update(int idx, int delta) 
{
    for (; idx < N+1; idx += idx & -idx) bit[idx] += delta;
}

########    Range Update & Point Query */

int point_query(int idx) 
{
    int ret = 0;
    for (; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
}

void point_update(int idx, int delta) 
{
    for (; idx < N+1; idx += idx & -idx) bit[idx] += delta;
}

void range_update(int l, int r, int val) 
{
    point_update(l, val);
    point_update(r + 1, -val);
}

/*
########    Range Update & Range Query

def add(b, idx, x):
    while idx <= N:
        b[idx] += x
        idx += idx & -idx

def range_add(l,r,x):
    add(B1, l, x)
    add(B1, r+1, -x)
    add(B2, l, x*(l-1))
    add(B2, r+1, -x*r)

def sum(b, idx):
    total = 0
    while idx > 0:
        total += b[idx]
        idx -= idx & -idx
    return total

def prefix_sum(idx):
    return sum(B1, idx)*idx -  sum(B2, idx)

def range_sum(l, r):
    return prefix_sum(r) - prefix_sum(l-1)

########    Range Update & Point Query */


int main()
{
    vector<int> v; for(int i = 0; i < N; i++) v.push_back(i+1);
    for (int i = 0; i<N; i++) cout << v[i] << " \n"[i==N-1];
    
    // Initialize bit
    bit.assign(N+1, 0);
    for (size_t i = 0; i < v.size(); i++) range_update(i+1, i+1, v[i]);

    // Make range queries
    cout << point_query(10) << endl;
    cout << point_query(9) << endl;

    // Make update queries
    range_update(9,10, -10);

    // Make range queries
    cout << point_query(10) << endl;
    cout << point_query(9) << endl;

    return 0;
}