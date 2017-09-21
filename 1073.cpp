#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdlib>

const int BUF = 12313123;
char Buf[BUF], *buf = Buf;
#define Max 120
#define Vec std :: vector
int dis[Max], N, M, S, T, K;
struct D
{
    Vec <int> r; bool is[Max]; int u, d;
    bool operator < (const D A) const
    {
        return this->d + dis[this->u] > A.d + dis[A.u];
    }
};
bool visit[Max];
struct E { E *n; int v, d; };
E *Z_list[Max], *F_list[Max], poor[(Max * Max) << 1], *Ta = poor;
inline int read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
void Spfa ()
{
    std :: queue <int> Q; memset (dis, 0x3f, sizeof dis); int n; E *e;
    for (Q.push (T), dis[T] = 0, visit[T] = true; !Q.empty (); Q.pop ())
    {
        n = Q.front (); visit[n] = false;
        for (e = F_list[n]; e; e = e->n)
            if (dis[e->v] > dis[n] + e->d)
            {
                dis[e->v] = dis[n] + e->d;
                if (!visit[e->v]) visit[e->v] = true, Q.push (e->v);
            }
    }
}    
Vec <D> Answer; int C;
inline int min (int a, int b) { return a < b ? a : b; }
bool Comp (D A, D B)
{
    if (A.d != B.d) return A.d < B.d;
    int L = min (A.r.size (), B.r.size ());
    for (register int i = 0; i < L; ++ i)
        if (A.r[i] != B.r[i]) return A.r[i] < B.r[i];
    return A.r.size () < B.r.size ();
}
void A_star ()
{
    std :: priority_queue <D> H; D n, res; n.u = S, n.d = 0;
    n.r.push_back (S); E *e; n.is[S] = true; H.push (n); 
    for (; !H.empty (); )
    {
        n = H.top (); H.pop ();
        if (n.u == T)
        {
            if ((++ C) > K && n.d > Answer[K - 1].d) break;
            Answer.push_back (n);
        }
        for (e = Z_list[n.u]; e; e = e->n)
            if (!n.is[e->v])
            {
                res = n; res.u = e->v; res.r.push_back (e->v);
                res.d = e->d + n.d, res.is[e->v] = true, H.push (res); 
            }
    }
    if (Answer.size () < K) { printf ("No\n"); exit (0); }
    std :: sort (Answer.begin (), Answer.end (), Comp);
}

int Main ()
{
    fread (buf, 1, BUF, stdin); read (N), read (M), read (K);
    read (S), read (T); register int i; int x, y, z, Size;
    for (i = 1; i <= M; ++ i)
    {
        read (x), read (y), read (z);
        ++ Ta, Ta->v = y, Ta->d = z, Ta->n = Z_list[x], Z_list[x] = Ta;
        ++ Ta, Ta->v = x, Ta->d = z, Ta->n = F_list[y], F_list[y] = Ta;
    }
    for (Spfa (), A_star (), i = 0, Size = Answer[K - 1].r.size () - 1; i < Size; ++ i)
        printf ("%d-", Answer[K - 1].r[i]);
    printf ("%d", Answer[K - 1].r[i]);
    return 0;
}
int ZlycerQan = Main (); int main (int argc, char *argv[]) {;}
