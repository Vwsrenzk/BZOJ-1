#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#define rg register
#define Max 1505
struct E { E *n; int u, v, d; } poor[Max * 1000], *list[Max], *Ta = poor, *_list[Max];
const int BUF = 12312323; char Buf[BUF], *buf = Buf;
inline void read (int &n)
{
    for (n = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
}
int S1, T1, S2, T2, d[4][Max], a[Max], in[Max]; bool is[4][Max], has[Max][Max];
struct D 
{
    int id, d; D (int x, int y) : id (x), d (y) {} D () {}
    bool operator < (const D &A) const { return d > A.d; }
};
inline int min (int a, int b) { return a < b ? a : b; }
void Dijkstra (int S, register int t)
{
    std :: priority_queue <D> Q; Q.push (D (S, 0)), d[t][S] = 0; E *e; D n;
    for (int i, V; !Q.empty (); )
    {
        n = Q.top (); i = n.id; Q.pop (); if (is[t][i]) continue; 
        for (e = list[i], is[t][i] = true; e; e = e->n)
            if (d[t][(V = e->v)] > d[t][i] + e->d)
                d[t][V] = d[t][i] + e->d, Q.push (D (V, d[t][V]));
    }
}
inline void Insert (int u, int v, int d) 
{ ++ Ta, Ta->v = v, Ta->n = _list[u], _list[u] = Ta, Ta->d = d, ++ in[v]; }
inline void cmax (int &a, int b) { if (b > a) a = b; }
int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin); int N, M, x, y, z, Answer = 0; read (N), read (M); rg int i, j;
    read (S1), read (T1), read (S2), read (T2);
    for (i = 1; i <= M; ++ i) 
    {
        read (x), read (y), read (z);     
        ++ Ta, Ta->v = y, Ta->n = list[x], list[x] = Ta, Ta->d = z, Ta->u = x;
        ++ Ta, Ta->v = x, Ta->n = list[y], list[y] = Ta, Ta->d = z, Ta->u = y;
    }
    memset (d, 0x3f, sizeof d); E *e; int d1, d2, u, v, c, s = 0;
    Dijkstra (S1, 0); Dijkstra (T1, 1); Dijkstra (S2, 2); Dijkstra (T2, 3);
    for (i = 1; i <= N; ++ i)
        for (e = list[i]; e; e = e->n)
        {
            u = e->u, v = e->v, c = e->d; 
            if (has[u][v] || has[v][u]) continue; 
            has[u][v] = true, has[v][u] = true;
            d1 = min (d[0][u], d[0][v]) + min (d[1][u], d[1][v]) + c;
            d2 = min (d[2][u], d[2][v]) + min (d[3][u], d[3][v]) + c;
            if (d1 == d[0][T1] && d2 == d[2][T2]) 
                if (d[0][u] < d[0][v]) Insert (u, v, c); else Insert (v, u, c);
        }
    std :: queue <int> Q; for (i = 1; i <= N; ++ i) if (!in[i]) Q.push (i);
    for (int n; !Q.empty (); Q.pop ())
        for (n = Q.front (), e = _list[n]; e; e = e->n)
        {
            cmax (a[(v = e->v)], a[n] + e->d), cmax (s, a[v]), -- in[v];
            if (!in[v]) Q.push (v);
        }
    printf ("%d", s); return 0;
}
