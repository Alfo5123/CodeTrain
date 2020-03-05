/*

    GCD and LCM 
    Using Euclid recursive algorithm

    Built-in __gcd() method for C++14

    Implementation based on post
    https://cp-algorithms.com/algebra/euclid-algorithm.html
*/

int gcd (int a, int b) 
{
    if (b == 0) return a;
    return gcd (b, a % b);
}

int lcm (int a, int b) 
{
    return a / gcd(a, b) * b;
}