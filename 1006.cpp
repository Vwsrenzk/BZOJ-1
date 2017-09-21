#include <cstdio>
#include <iostream>
const int BUF = 12312323; char Buf[BUF], *buf = Buf;
#define rg register
#define Max 10009
inline void read (int &n)
{
    for (n = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
}
inline void cmax (int &a, int b) { if (b > a) a = b; }
struct E { E *n; int v; } *list[Max], poor[Max * 300], *Ta = poor;
bool is[Max]; int d[Max], q[Max], k[Max], c[Max];
int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin); E *e; int x, y, Answer = 0;
    int N, M, p, n; read (N), read (M); rg int i, j; 
    for (i = 1, d[0] = -1; i <= M; ++ i) 
    {
        read (x), read (y);
        ++ Ta, Ta->v = y, Ta->n = list[x], list[x] = Ta;
        ++ Ta, Ta->v = x, Ta->n = list[y], list[y] = Ta;
    }
    for (i = N; i >= 1; -- i)
    {
        for (j = 1, n = 0; j <= N; ++ j)
            if (!is[j] && d[j] > d[n]) n = j;
        for (is[n] = true, q[i] = n, e = list[n]; e; ++ d[e->v], e = e->n);
    }   
    for (i = N; i >= 1; -- i)
    {
        for (e = list[q[i]]; e; k[c[e->v]] = i, e = e->n);
        for (j = 1; k[j] == i; ++ j); c[q[i]] = j; cmax (Answer, j);
    }
    printf ("%d", Answer);
    return 0;
}
