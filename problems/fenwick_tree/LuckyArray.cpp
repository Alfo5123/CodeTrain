/*
    Problem:
    https://codeforces.com/problemset/problem/121/E

    Queries to update ranges by summing a constant
     and count the number of lucky numbers in a range.
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> bit; 
bool lucky[100010]; 
int N, M;

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

 bool islucky(int n)
 {
	while(n > 0)
    {
		if(n%10 != 4 && n%10 != 7)  
			return false;
		n /= 10;
	}
	return true;
}

int main()
{

    scanf("%d %d", &N, &M);
    bit.assign(N+1, 0);

    for (int i = 1; i <= 100010; i++)
        lucky[i] = islucky(i);

    int a[N+1];
    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &a[i]);
        if ( lucky[a[i]] ) point_update(i, 1);
    }
    char s[10];
    int l, r;
    while(M--)
    {
        scanf("%s%d%d",s,&l,&r);
        if ( s[0] == 'c') printf("%d\n",point_query(r)-point_query(l-1));
        else
        {
            int add;
            scanf("%d", &add);
            for(int i = l; i <= r; i++)
            {
					bool cur = lucky[a[i]];
					bool next = lucky[a[i]+=add];
					if(!cur && next) point_update(i,1);
					if(cur && !next) point_update(i,-1);
			}
        }
        
    }

    return 0;
}