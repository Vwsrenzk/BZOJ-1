#include <cstdio>
#include <iostream>
 
const int BUF = 12312312;
char Buf[BUF], *buf = Buf;
 
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 200004
inline int min (int a, int b) { return a < b ? a : b; }
int N, M, Mod, Stack[Max], top;
struct E { E *n; int v; };
E *list[Max], *_list[Max], poor[Max * 22], *Ta = poor;bool is[Max];
int low[Max], dfn[Max], scc[Max], Scc, C;
int key[Max];
inline int max (int a, int b) { return a > b ? a :  b; }
void Tarjan_ (int n)
{
    dfn[n] = low[n] = ++ C; E *e;
    Stack[++ top] = n;  
    for (E *e = list[n]; e; e = e->n)
        if (!dfn[e->v])
            Tarjan_ (e->v), low[n] = min (low[n], low[e->v]);
        else if (!scc[e->v])
            low[n] = min (low[n], dfn[e->v]);    
    if (dfn[n] == low[n])
    {
        ++ Scc; int res;
        do { res = Stack[top --], scc[res] = Scc; } while (res != n);
    }
}
int f[Max], g[Max];
void Dp (int n)
{
    if (is[n]) return ; is[n] = true; E *e; f[n] = key[n];
    for (e = _list[n]; e; e = e->n)
        Dp (e->v), f[n] = max (f[n], f[e->v] + key[n]);
    for (e = _list[n]; e; e = e->n)
        if (f[n] == f[e->v] + key[n]) g[n] = (g[n] + g[e->v]) % Mod;
    if (g[n] == 0) g[n] = 1;
}
 
int Main ()
{
    fread (buf, 1, BUF, stdin); read (N), read (M), read (Mod);
    register int i; int x, y; E *e, *c; int Answer = 0;
    for (i = 1; i <= M; ++ i)
    {
        read (x), read (y);
        ++ Ta, Ta->v = y, Ta->n = list[x], list[x] = Ta;
    }
    for (i = 1; i <= N; ++ i) if (!dfn[i]) Tarjan_ (i);
    for (int n = 1; n <= N; ++ n)
    {
        ++ key[scc[n]];
        for (e = list[n]; e; e = e->n)
            if (scc[n] != scc[e->v])
            {
                for (c = _list[scc[n]]; c; c = c->n)
                    if (c->v == scc[e->v]) goto Fuck;
                ++ Ta, Ta->v = scc[e->v], Ta->n = _list[scc[n]], _list[scc[n]] = Ta;
                Fuck : continue;
            }
    }
    for (i = 1; i <= Scc; ++ i) if (!is[i]) Dp (i);
    for (i = 1; i <= Scc; ++ i) Answer = max (Answer, f[i]);
    int res = 0;
    for (i = 1; i <= Scc; ++ i) if (Answer == f[i]) res = (res + g[i]) % Mod;
    printf ("%d\n%d", Answer, res);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
