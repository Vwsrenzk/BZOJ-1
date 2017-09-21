#include <cstdio>
#include <iostream>
 
const int BUF = 12312312;
char Buf[BUF], *buf = Buf;
 
typedef long long LL;
using std :: min;
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
 
#define Max 200010
LL f[Max][Max / 10000], g[Max][Max / 10000];
LL deep[Max], d[Max];
int key[Max];
int v[Max];
 
int Main ()
{
    fread (buf, 1, BUF, stdin); 
    int N, z; read (N); register int i, j;
    for (i = 1; i <= N; ++ i)
        read (key[i]);
    for (i = 2, deep[1] = 1; i <= N; ++ i)
    {
        read (z), d[i] = d[i >> 1] + z;
        deep[i] = deep[i >> 1] + 1, v[i] = z;
    }
    LL l, r, y; register LL x; LL res;
    for (x = N; x; -- x)
        for (i = 0; i < deep[x]; ++ i)
        {
            l = x << 1, r = l | 1;
            y = (x >> (deep[x] - i - 1)) ^ 1;
            if (l > N) 
                f[x][i] = key[y] * (d[x] + d[y] - (d[y >> 1] << 1));
            else if (r > N)
                f[x][i] = key[l] * v[l] + f[l][i];
            else
                f[x][i] = min (key[l] * v[l] + f[r][i] + f[l][deep[x]], key[r] * v[r] + f[l][i] + f[r][deep[x]]);
        }
    for (x = N; x; -- x)
        for (i = 0; i <= deep[x]; ++ i)
        {
            l = x << 1, r = l | 1;
            y = x >> (deep[x] - i);
            if (l > N)
                g[x][i] = key[y] * (d[x] - d[y]);
            else if (r > N)
                g[x][i] = g[l][i] + key[l] * v[l];
            else
                g[x][i] = min (key[l] * v[l] + f[l][deep[l] - 1] + g[r][i], key[r] * v[r] + f[r][deep[r] - 1] + g[l][i]);
        }
    LL Answer = g[1][0]; LL pos;
    for (i = 2; i <= N; ++ i) 
    {
        res = g[i][deep[i] - 1], pos = i;
        for (; pos != 1; pos >>= 1)
        {
            y = pos ^ 1, z = pos >> 1;
            if (y > N) res += key[z >> 1] * v[z];
            else res += key[y] * v[y] + g[y][deep[z] - 1];
        }
        Answer = min (Answer, res);
    }
    printf ("%lld", Answer);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
