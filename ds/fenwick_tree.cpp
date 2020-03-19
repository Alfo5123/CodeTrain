/*
    Fenwick Tree ( Binary Indexed Tree )

    Let, f be some reversible(!) function and A be an array of integers of length N.

    Fenwick tree is a data structure which:

    calculates the value of function f in the given range [l,r] (i.e. f(Al,Al+1,…,Ar)) in O(logn) time;
    updates the value of an element of A in O(logn) time;
    requires O(N) memory, or in other words, exactly the same memory required for A;
    is easy to use and code, especially, in the case of multidimensional arrays.

    Observations: 
        - its behavior ranges between a prefix sum and an array.
        - it can be extended for range updates and range queries

    Based on blogs
    - https://cp-algorithms.com/data_structures/fenwick.html
    - https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/

*/

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