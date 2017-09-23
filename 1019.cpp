#include <cstdio>
#define rg register
#define Max 35
typedef long long LL;
int g[3][Max], l[Max], q[Max]; LL f[3][Max];
int main (int argc, char *argv[])
{
    int N; char t[5]; scanf ("%d", &N); rg int i, j; int x, y;
    for (i = 0; i < 6; ++ i)
        scanf ("%s", t), l[i] = t[0] - 'A', q[i] = t[1] - 'A';
    f[0][1] = f[1][1] = f[2][1] = 1;
    for (i = 0; i < 3; ++ i)
        for (j = 0; j < 6; ++ j)
            if (l[j] == i) { g[i][1] = q[j]; break; }
    for (i = 2; i <= N; ++ i)
        for (j = 0; j < 3; ++ j)
        {
            x = g[j][i - 1], y = 3 - j - x;
            if (g[x][i - 1] == y) f[j][i] = f[j][i - 1] + 1 + f[x][i - 1], g[j][i] = y;
            else f[j][i] = f[j][i - 1] + 2 + f[x][i - 1] + f[j][i - 1], g[j][i] = x;
        }
    printf ("%lld", f[0][N]); return 0;
}
