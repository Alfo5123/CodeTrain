/*

    UNION FIND SET BY RANK WITH COMPRESSION

    Efficient implementation of a data structure that initially 
    starts with a collection of N objects on its own. From time
    to time we perform the following operations:

    FIND ( x ) -> asks which set x belongs to
    UNION ( x , y ) -> combine to sets containing x and y together

    Path Compression: every time we find a root r of x, we make all
    the nodes in path from x to r , to be direct children of r.

    Union by rank : every time we want to combine to roots we make
    sure the smaller rank set becomes the child of the largest one.
*/


#include <bits/stdc++.h>

using namespace std;

int N ; 

int P[ 30005 ] ; // Parent
int R[ 30005 ] ; // Rank
int C[ 30005 ] ; // Count

void INIT()
{
    for ( int i = 0 ; i < N ; i++ )
    {
        P[ i ] = i ; 
        C[ i ] = 1 ; 
        R[ i ] = 0 ; 
    }
} 

int FIND ( int x )
{
    int a = x ; 
    while ( P[ a ] != a ) a = P[ a ] ; 
    int b = x , c ; 
    while ( P[ b ] != a ) // Commpression 
    {
        c = P[ b ] ; 
        P[ b ] = a ; 
        b = c ; 
    }
    return a ; 

}

void UNION ( int x , int y )
{
    int x_ = FIND ( x ) ; 
    int y_ = FIND ( y ) ; 
    if ( x_ == y_ ) return ; 
    if ( R[ y_ ] > R[ x_ ] ) swap ( x_ , y_ ) ;  // Ranking 
    if ( R[ y_ ] == R[ x_ ] ) R[ x_ ]++;
    P[ y_ ] = x_ ; 
    C[ x_ ] += C[ y_ ] ;   
}
