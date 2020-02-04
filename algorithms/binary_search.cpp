/*

    BINARY SEARCH

    It is very easy to implement binary search with misatkes, 
    therefore, despite its apparent simplicity, we include it 
    in algorithms recipes.

    Builtin methods: 
    Semantics follow those of std::lower_bound and std::upper_bound

    Implementation based on the video
    https://www.youtube.com/watch?v=GU7DpgHINWQ

*/

int find_target(int A[], int n, int target) 
{
    int l = 0;
    int r = n-1;
    int mid;
    while (l <= r) 
    {
        mid = (r - l)/2 + l;  // prevents integer overflow

        if (A[mid] == target) return mid;
        if( A[mid] < target ) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int lowerbound(int A[], int n, int target)
{
    /*
    Find the first value in ordered array A
    such that is greater or equal than target 
    */
    int l = 0;
    int r = n-1;
    int ans = -1; // if no element in the array satisfies the condition
    int mid;
    while (l <= r)
    {
        mid = (r - l)/2 + l;  // prevents integer overflow

        if (A[mid] >= target)  // this can be generalized to any condition f(mid) to be satisfied
        {
            ans = mid; // if you want the actual, you can keep A[mid]
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}

 