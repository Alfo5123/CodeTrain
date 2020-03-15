/*
    RANGE MAX QUERY 

    Given a big array f[ 0 N-1 ] , we get many queries of the form 
    getmax ( a , b ) that asks the maximum element between f[ a ] 
    and f[ b ] , inclusive. 

    The idea is always to get the max in some big ranges, so in the
    queries we may try to use these big ranges to compute fast. One
    simple algorithm is to break the n numbers into sqrt(n) regions, 
    each of size sqrt(n). Compute the best for each region and for 
    each query, we go from a to the nearest station, then go to the
    nearest station before b, and from here to b. 

*/

#include <bits/stdc++.h>
using namespace std;

int N ; 
int Q ; 

int f[ 100005 ] ; 
int m[ 100005 ][ 20 ] ; //  N and log(N) + 1 


// RMQ implementation
void construct()
{
    for ( int i = 0 ; i < N ; i++ ) m[ i ][ 0 ] = f[ i ] ; 

    for ( int i = 1 ; i < 20 ; i++ )
    {
        for ( int j = 0 ; ( j + ( 1 << i ) - 1 ) < N ; j += ( 1 << i ) )
        {
            m[ j ][ i ] = max ( m[ j ][ i - 1 ] , m[ j + ( 1 << ( i - 1 ) ) ][ i - 1 ] ) ;
        }
    }
}

// Query
int getmax ( int a , int b )
{
    if ( a > b ) return -1 ; 

    for ( int i = 19 ; i >= 0 ; i-- )
    {
        if ( ( a % ( 1 << i ) ) == 0  && ( a + ( 1 << i ) - 1 ) <= b )
        {
            return max ( m[ a ][ i ] , getmax ( a + ( 1 << i ) , b ) ) ; 
        }
    } 
}
