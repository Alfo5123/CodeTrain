/*

    BINARY EXPONENTIATION

    Implementation based on post
    https://cp-algorithms.com/algebra/binary-exp.html?fbclid=IwAR0E7iyqC34ndxMHKkkDGKXIePqrP6uiEW1jJtR5aG_OF3h_VQqnT7UlCao


    Note: if m is a prime, by Fermat's little theorem
    we can calculate x^(n mod (m-1)) instead of x^n

    Note 2: iot can be used to apply a permutaiton k times.
*/

long long binpow( long long a, long long b, long long m )
{
    a %= m;
    long long res = 1;
    while(b > 0)
    {
        if ( b & 1 ) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
