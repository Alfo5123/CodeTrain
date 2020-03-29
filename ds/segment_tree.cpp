/*
    Segment Tree (Simple Implementation)
    
    A Segment Tree is a flexible data structure that allows answering range queries over an array effectively, 
    while still being flexible enough to allow modifying the array. This includes finding the sum of consecutive 
    array elements a[l…r], or finding the minimum element in a such a range in O(logn) time. 
    
    Between answering such queries the Segment Tree allows modifying the array by replacing one element, or even
     change the elements of a whole subsegment (e.g. assigning all elements a[l…r] to any value, or adding a value 
     to all element in the subsegment).

    Notes:
        - The left child of a vertex at index i is stored at index 2i, and the right one at index 2i+1.
          Thus the total number of space is < 4n (when n is a power of 2)
        - By changing the combine operation as well as the state of each node, we can adapt to different problems.
        - Sum queries and point updates in O(logN)

    Blog:
        https://cp-algorithms.com/data_structures/segment_tree.html#advanced-versions-of-segment-trees
*/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int n;
int t[4*MAXN]; // at most 4*N vertices stored in memory, can be optimized to 2*n-1

// Construction of the segement tree takes O(N)
void build(int a[], int v, int tl, int tr) 
{
    if (tl == tr) t[v] = a[tl];
    else 
    {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

// Sum query O(logN)
int sum(int v, int tl, int tr, int l, int r)
{
    if (l > r) return 0;
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}

// Update query O(logN)
void update(int v, int tl, int tr, int pos, int new_val) 
{
    if (tl == tr) t[v] = new_val;
    else 
    {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v*2, tl, tm, pos, new_val);
        else update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}

int main()
{
    cin >> n;
    int a[n];
    for(int i = 0; i < n;  i++) cin >> a[i];
    build(a, 1, 0, n-1);
    cout << sum(1, 0, n-1, 0, 2) << endl;
    update(1, 0, n-1, 0, 4);
    cout << sum(1, 0, n-1, 0, 2) << endl;
}



