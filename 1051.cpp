#include <cstdio>
#include <iostream>
#include <stack>
#define rg register
int N, M; const int BUF = 1231223; char Buf[BUF], *buf = Buf;
#define Max 123123
struct E { E *n; int v; } *list[Max], poor[Max * 12], *Ta = poor;
int dfn[Max], scc[Max], Scc, C, low[Max], in[Max]; std :: stack <int> S;
inline void read (int &n)
{
    for (n = 0; !isdigit (*buf); ++ buf); 
    for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
}
inline void cmin (int &a, int b) { if (b < a) a = b; }
void Dfs (int n)
{
    S.push (n); dfn[n] = low[n] = ++ C;
    for (E *e = list[n]; e; e = e->n)
        if (!dfn[e->v]) Dfs (e->v), cmin (low[n], low[e->v]);
        else if (!scc[e->v]) cmin (low[n], dfn[e->v]);
    if (low[n] == dfn[n])
    {
        int r = n + 1; ++ Scc;
        for (; r != n; S.pop ()) r = S.top (), scc[r] = Scc;
    }
}
int Main ()
{
    fread (buf, 1, BUF, stdin); read (N), read (M); rg int i, j; int x, y; E *e;
    for (i = 1; i <= M; ++ i)
    {
        read (x), read (y);
        ++ Ta, Ta->n = list[x], list[x] = Ta, Ta->v = y;
    }
    for (i = 1; i <= N; ++ i) if (!dfn[i]) Dfs (i);
    for (i = 1; i <= N; ++ i) 
        for (e = list[i]; e; e = e->n) if (scc[i] != scc[e->v]) ++ in[scc[i]];
    int r = 0, Answer = 0, t = 0;   
    for (i = 1; i <= Scc; ++ i) if (!in[i]) ++ t, r = i;
    if (t != 1) return printf ("0"), 0;
    for (i = 1; i <= N; ++ i) if (scc[i] == r) ++ Answer;
    printf ("%d", Answer); return 0;
}
int ZlycerQan = Main (); int main (int argc, char *argv[]) { return 0; }
