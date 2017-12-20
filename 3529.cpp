#include <cstdio>
#include <iostream>
#include <algorithm>

#define rg register

inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 100000

int t[Max + 9], p[Max + 9], mu[Max + 9]; bool is[Max + 9];
inline int min (int a, int b) { return a < b ? a : b; }

void Euler (int N)
{
    rg int i, j, k; int C = 0; mu[1] = 1;
    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) p[++ C] = i, mu[i] = -1;
        for (j = 1; j <= C; ++ j)
        {
            if ((k = i * p[j]) > N) break;
            is[k] = true;
            if (i % p[j] == 0) { mu[k] = 0; break; }
            else mu[k] = -mu[i];
        }
    }
}

struct Q 
{ 
    int x, y; Q (int a = 0, int b = 0) : x (a), y (b) { } 
    bool operator < (const Q &rhs) const
    { return x == rhs.x ? y < rhs.y : x < rhs.x; }
} f[Max + 9];

void F ()
{
    rg int i, j;
    for (i = 1; i <= Max; ++ i)
        for (j = i; j <= Max; j += i) f[j].x += i;
    for (i = 1; i <= Max; ++ i) f[i].y = i;
    std :: sort (f + 1, f + 1 + Max);
}

struct D 
{ 
    int n, m, a, id; 
    bool operator < (const D &rhs) const
    { return a < rhs.a; }
} q[Max + 9];
int Answer[Max + 9];

inline int Query (int x)
{
    int res = 0;
    for (rg int i = x; i; i -= i & (-i))
        res += t[i];
    return res;
}
void Change (int x, int k)
{ for (rg int i = x; i <= Max; i += i & (-i)) t[i] += k; }

int Ask (int N, int M)
{
    int res = 0, j; 
    if (N > M) std :: swap (N, M);

    for (rg int i = 1; i <= N; i = j + 1)
    {
        j = min (N / (N / i), M / (M / i));
        res += (N / i) * (M / i) * (Query (j) - Query (i - 1));
    }
    return res & 0x7fffffff;
}

int main (int argc, char *argv[])
{
    int N, M; rg int i, j, k;
    Euler (Max); F ();

    int T; read (T);
    for (i = 1; i <= T; ++ i)
        read (q[i].n), read (q[i].m), read (q[i].a), q[i].id = i;
    std :: sort (q + 1, q + 1 + T);

    for (i = 1, j = 1; i <= T; ++ i)
    {
        for (; j <= Max && f[j].x <= q[i].a; ++ j)
            for (k = f[j].y; k <= Max; k += f[j].y)
                Change (k, f[j].x * mu[k / f[j].y]);
        Answer[q[i].id] = Ask (q[i].n, q[i].m);    
    }

    for (i = 1; i <= T; ++ i)
        printf ("%d\n", Answer[i]);
    return 0;
}
