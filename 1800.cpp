#include <cstdio>
#include <iostream>
#define rg register
inline void read (int &n)
{
    rg int c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 1000001
int c[Max]; bool is[Max];
int main (int argc, char *argv[])
{
    int N, x, s = 0, Answer = 0; rg int i, j; read (N);
    for (i = 1; i <= N; ++ i) 
        read (x), is[s] = true, c[i] = s, s += x;
    for (i = 1; i <= N; ++ i)
        for (j = i + 1; j <= N; ++ j) 
            if (is[c[j] + (s - 2 * (c[j] - c[i])) / 2] && is[c[j] + (s - 2 * (c[j] - c[i])) / 2 + c[j] - c[i]]) ++ Answer;
    printf ("%d", Answer); return 0;
}
