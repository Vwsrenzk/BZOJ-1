#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#define INF 1e6
const int BUF = 12312313; char Buf[BUF], *buf = Buf;
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 102
struct E { E *n; int v, d; }; int S, T;
E *list[Max], poor[Max * Max * 2], *Ta = poor; 
bool is[Max / 5 + 1][Max], can[Max], visit[Max];
int d[Max][Max], dis[Max], f[Max];
int Spfa ()
{
    for (int i = 0; i <= T; ++ i) dis[i] = INF; 
    memset (visit, false, sizeof visit);
    std :: queue <int> Q; Q.push (S), visit[S] = true; E *e; dis[S] = 0;
    for (int n; !Q.empty (); Q.pop ())
    {
        n = Q.front (); visit[n] = false;
        for (e = list[n]; e; e = e->n)
            if (dis[e->v] > dis[n] + e->d && !can[e->v])
            {
                dis[e->v] = dis[n] + e->d;
                if (!visit[e->v]) visit[e->v] = true, Q.push (e->v);
            }
    } 
    return dis[T];
}
inline int min (int a, int b) { return a < b ? a : b; }
int Main ()
{
    fread (buf, 1, BUF, stdin); register int i, j, k, l; int x, y, z;
    int N, M, K, _E; read (N), read (M), read (K), read (_E);
    for (i = 1, S = 1, T = M; i <= _E; ++ i)
    {
        read (x), read (y), read (z);
        ++ Ta, Ta->v = y, Ta->n = list[x], Ta->d = z, list[x] = Ta;
        ++ Ta, Ta->v = x, Ta->n = list[y], Ta->d = z, list[y] = Ta;
    }
    for (read (_E), i = 1; i <= _E; ++ i)
    {
        read (x), read (y), read (z);
        for (j = y; j <= z; ++ j) is[x][j] = true;
    }
    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= N; ++ j)
        {
            memset (can, false, sizeof can);
            for (k = 1; k <= M; ++ k) 
                for (l = i; l <= j; ++ l) if (is[k][l]) { can[k] = true; break;}
            d[i][j] = Spfa ();  
        }
    for (i = 1; i <= N; ++ i)
    {
        f[i] = (long long)d[S][i] * i;
        for (j = 0; j < i; ++ j)
            f[i] = min (f[i], f[j] + d[j + 1][i] * (i - j) + K);
    }
    printf ("%d", f[N]);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
﻿
