#include <cstdio>
#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#define Max 100005
#define rg register
int N, M, a[Max], c[Max], b[Max]; bool s[Max];
std :: bitset <Max> A, B; const int BUF = 12312312; char Buf[BUF], *buf = Buf;
struct QD
{
    int l, r, id, v, t, x;
    bool operator < (const QD &rhs) const
    { return b[l] == b[rhs.l] ? r < rhs.r : b[l] < b[rhs.l]; }
} q[Max];
inline void read (int &n)
{
    for (n = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
}
bool Get (int x)
{
    if (q[x].t == 1) return (A & (A >> q[x].x)).any ();
    if (q[x].t == 2) return (A & (B >> (Max - 5 - q[x].x))).any ();
    rg int d = q[x].x, i; if (!d) return c[0];
    for (i = 1; i * i <= q[x].x; ++ i) if (!(d % i) && c[i] && c[d / i]) return true;
    return false;
}
inline void Updata (int x, bool t)
{
    x = a[x];
    if (t) ++ c[x], A[x] = 1, B[Max - 5 - x] = 1;
    else { -- c[x]; if (!c[x]) A[x] = 0, B[Max - 5 - x] = 0; }
}
int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin); read (N), read (M); int K = sqrt (N); rg int i;
    for (i = 1; i <= N; ++ i) read (a[i]), b[i] = (i + 1) / K;
    for (i = 1; i <= M; ++ i)
        read (q[i].t), read (q[i].l), read (q[i].r), read (q[i].x), q[i].id = i;
    std :: sort (q + 1, q + M + 1); int l = 1, r = 0;
    for (i = 1; i <= M; ++ i)
    {
        for (; r < q[i].r; Updata (++ r, true));
        for (; r > q[i].r; Updata (r --, false));
        for (; l < q[i].l; Updata (l ++, false));
        for (; l > q[i].l; Updata (-- l, true));
        s[q[i].id] = Get (i);
    }
    for (i = 1; i <= M; ++ i) puts (s[i] ? "yuno" : "yumi"); return 0;
}
