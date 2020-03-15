/*
    Prefix Sum

    Prefix Sum or Partial Sum is nothing but an array which stores the cumulative sum. 
    This allow us to perform  sum range queries in O(1). In addition we can sacrifice the 
    O(1) to O(n) in order to do range update queries by summing a constant value x to all 
    elements in [L,R] in O(1).

    It can also be used in 2D, by following the inclusion-exclusion principle to facilitate
    counting problems. 

    Based on blogs
    - https://www.geeksforgeeks.org/constant-time-range-add-operation-array/
    - https://codeforces.com/blog/entry/15729

*/

#include <bits/stdc++.h> 
using namespace std;

//  Method to add value val, to range [L, R] 
void add_query(int arr[], int N, int L, int R, int x) 
{ 
    arr[L] += x; 
    if (R != N - 1) arr[R + 1] -= x; 
} 

void updateArray(int arr[], int N) 
{ 
    //  convert array into prefix sum array 
    for (int i = 1; i < N; i++) 
        arr[i] += arr[i - 1]; 
} 
  
//  method to print final updated array 
void printArr(int arr[], int N) 
{ 
    updateArray(arr, N); 
    for (int i = 0; i < N; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
  
//  Driver code to test above methods 
int main() 
{ 
    int N = 6; 
    int arr[N] = {0}; 

    //  Range add Queries 
    add(arr, N, 0, 2, 100); 
    add(arr, N, 1, 5, 100); 
    add(arr, N, 2, 3, 100); 
  
    printArr(arr, N); 
    return 0; 
} 
