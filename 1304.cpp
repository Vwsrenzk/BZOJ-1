#include <cstdio>
#include <iostream>
 
const int BUF = 12312323;
char Buf[BUF], *buf = Buf;
#define INF 1e9
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 100001
struct E { E *n; int v; }; int c[Max], dp[Max][2], N, M;
E *list[Max], poor[Max << 2], *Ta = poor;
inline int min (int a, int b) { return a < b ? a : b; }
void Dp (int n, int F)
{
    dp[n][0] = dp[n][1] = 1;
    if (n <= M) dp[n][c[n] ^ 1] = INF;
    for (E *e = list[n]; e; e = e->n)
        if (e->v != F) 
        {
            Dp (e->v, n);
            dp[n][0] += min (dp[e->v][0] - 1, dp[e->v][1]);
            dp[n][1] += min (dp[e->v][1] - 1, dp[e->v][0]);
        }
}
int Main ()
{
    fread (buf, 1, BUF, stdin);
    int x, y; read (N), read (M); register int i, j;
    for (i = 1; i <= M; ++ i) read (c[i]);
    for (i = 1; i < N; ++ i)
    {
        read (x), read (y);
        ++ Ta, Ta->v = y, Ta->n = list[x], list[x] = Ta;
        ++ Ta, Ta->v = x, Ta->n = list[y], list[y] = Ta;
    }
    Dp (M + 1, 0); printf ("%d", min (dp[M + 1][0], dp[M + 1][1]));
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
