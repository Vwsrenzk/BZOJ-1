#include <cstdio>
#include <iostream>
#include <algorithm>
#define rg register
#define Mod 31011
#define Max 1009
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
struct E 
{ 
    int u, v, d;
    bool operator < (const E &rhs) const { return d < rhs.d; }
} e[Max]; int f[Max / 10 + 3], C, T, p;
struct D { int v, s, l, r; } g[Max];
int Find (int x) { return f[x] == x ? x : Find (f[x]); }
void Dfs (int n, int t, int i)
{
    if (n == g[i].r + 1) { if (t == g[i].s) ++ p; return ; }
    Dfs (n + 1, t, i); int x = Find (e[n].u), y = Find (e[n].v);
    if (x != y) f[x] = y, Dfs (n + 1, t + 1, i), f[x] = x;
}
int main (int argc, char *argv[])
{
    int N, M, x, y, r, s = 1; read (N), read (M); rg int i, j;
    for (i = 1; i <= M; ++ i) read (e[i].u), read (e[i].v), read (e[i].d);
    std :: sort (e + 1, e + 1 + M); for (i = 1; i <= N; f[i] = i, ++ i);
    for (i = 1; i <= M; ++ i)
    {
        if (e[i].d != g[C].v) g[C].r = i - 1, g[++ C].l = i, g[C].v = e[i].d;
        x = Find (e[i].u), y = Find (e[i].v);
        if (x != y) f[x] = f[y], ++ T, ++ g[C].s;
        if (T == N - 1) { r = i; break; }
    }
    if (T != N - 1) return printf ("0"), 0;
    for (i = r + 1; i <= M; ++ i) if (e[i].d == g[C].v) r = i;
    for (g[C].r = r, i = 1; i <= N; f[i] = i, ++ i);
    for (i = 1; i <= C; ++ i)
    {
        if (g[i].s == 0) continue;
        p = 0, Dfs (g[i].l, 0, i), s = s * p % Mod;
        for (j = g[i].l; j <= g[i].r; ++ j)
        {
            x = Find (e[j].u), y = Find (e[j].v);
            if (x != y) f[x] = y;
        }
    }
    printf ("%d", s); return 0;
}
