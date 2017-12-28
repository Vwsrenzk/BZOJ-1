#include <cstdio>
#include <iostream>
#define rg register
#include <algorithm>

inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

#define Max 200006
int N;
int Calc (int *a, int *b)
{
    rg int l1 = 1, l2 = 1, r1 = N, r2 = N;
    int res = 0;
    for (; l1 <= r1 && l2 <= r2; )
    {
        if (a[l1] > b[l2]) ++ l1, ++ l2, ++++ res;
        else if (a[r1] > b[r2]) ++++ res, -- r1, -- r2;
        else res += (a[l1] == b[r2]), ++ l1, -- r2;
    }    
    return res;
}
int a[Max], b[Max];

int main (int argc, char *argv[])
{
    read (N); rg int i;
    for (i = 1; i <= N; ++ i) read (a[i]);

    for (i = 1; i <= N; ++ i) read (b[i]);
    
    std :: sort (a + 1, a + 1 + N);    
    std :: sort (b + 1, b + 1 + N);

    printf ("%d %d", Calc (a, b), 2 * N - Calc (b, a));

    return 0;
}
