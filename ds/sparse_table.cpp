/*
    SPARSE TABLE

    Sparse Table is a data structure, that allows answering  most range queries 
    in O(log(n)). Particularly, range minimum queries (or equivalent range maximum queries), 
    can be answered in O(1) with this data structure (indempotent operators).

    Note: it only works with immutable arrays!

    The main idea behind Sparse Tables is to precompute all answers for range queries with 
    power of two length. Afterwards a different range query can be answered by splitting the 
    range into ranges with power of two lengths, looking up the precomputed answers, and 
    combining them to receive a complete answer.

    Based on blog 
    https://cp-algorithms.com/data_structures/sparse-table.html

*/

const int MAXN = 1e5 + 5; // Maximum size of array
const int K = 25; // K >= ⌊log_2(MAXN)⌋+1 . In practice for MAXN <= 1e7, K = 25 is fine.

int st[MAXN][K + 1]; //  st[i][j] will store the answer for the range [i,i+2^j−1] of length 2^j.

/*
void preprocess(int N, int array, function f)
{
    Pre-computation Routine using Dynamic Programming

    The time complexity of the precomputation is O(NlogN).

    The function f will depend on the type of query. 
    For range sum queries it will compute the sum, for range minimum queries it will compute the minimum.
    

    for (int i = 0; i < N; i++)
        st[i][0] = f(array[i]);

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)

            Because the range [i,i+2^j−1] of length 2^j splits nicely into the ranges [i,i+2^j−1−1] and [i+2^j−1,i+2^j−1]
            st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]); 
}
*/

void sum_preprocess(int N, int array[])
{
    // Pre-computing the 
    for (int i = 0; i < N; i++) st[i][0] = array[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j - 1];
}

long long sum_query(int L, int R)
{
    // Returns the sum between [L, R] by greedily taking
    // intervals of size powers of two.

    long long sum = 0;
    for (int j = K; j >= 0; j--) 
    {
        if ((1 << j) <= R - L + 1) 
        {
            sum += st[L][j];
            L += 1 << j;
        }
    }
}

void min_preprocess(int N, int array[])
{
    // Pre-computing the array via DP
    for (int i = 0; i < N; i++) st[i][0] = array[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = min(st[i][j-1] , st[i + (1 << (j - 1))][j - 1] );
}

// Pre-compute logarithms
int log[MAXN+1];
log[1] = 0; for (int i = 2; i <= MAXN; i++) log[i] = log[i/2] + 1;

long long min_query(int L, int R)
{
    // Obtain the minimum of two intervals with maximum size of 2^j possible
    int j = log[R - L + 1];
    return min(st[L][j], st[R - (1 << j) + 1][j]);
}