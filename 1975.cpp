#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>
#define flo double 
#define rg register
#define Max 5010
#define INF 1e9
struct E { E *n; int v; flo d; } *Zlist[Max], *Flist[Max], poor[Max * 80], *Ta = poor;
int N, M; flo dis[Max], P; bool is[Max];
struct D 
{
    flo g; int id;
    bool operator < (const D &rhs) const 
    { return g + dis[id] > rhs.g + dis[rhs.id]; }
};
std :: queue <int> Q; std :: priority_queue <D> H;
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
int main (int argc, char *argv[])
{
    read (N), read (M); scanf ("%lf", &P); rg int i, j; int x, y; flo z;
    for (i = 1; i <= M; ++ i) 
    {
        read (x), read (y); scanf ("%lf", &z);
        ++ Ta, Ta->n = Zlist[x], Zlist[x] = Ta, Ta->v = y, Ta->d = z;
        ++ Ta, Ta->n = Flist[y], Flist[y] = Ta, Ta->v = x, Ta->d = z;
    }
    int n; E *e; int V;for (i = 1; i <= N; ++ i) dis[i] = INF;
    for (dis[N] = 0, is[N] = true, Q.push (N); !Q.empty (); Q.pop ())
        for (n = Q.front (), is[n] = false, e = Flist[n]; e; e = e->n)
            if (dis[(V = e->v)] > dis[n] + e->d)
            {
                dis[V] = dis[n] + e->d;
                if (!is[V]) is[V] = true, Q.push (V);
            }
    D r, _t; r.id = 1, r.g = 0; flo T = 0; int C = 0;
    for (H.push (r); !H.empty (); )
    {
        r = H.top (); H.pop ();
        if (r.id == N) { ++ C, T += r.g; if (T > P) break; };
        for (e = Zlist[r.id]; e; e = e->n)
            _t = r, _t.id = e->v, _t.g = r.g + e->d, H.push (_t);
    }
    printf ("%d", C - 1); return 0;
}
