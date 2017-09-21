#include <cstdio>
#define rg register
#define Max 12
typedef long long LL; LL f[Max][(1 << 15) + 2][Max * 3]; int c[(1 << 15) | 1], v[(1 << 15) | 1], N, C;
void Dfs (int n, int s, int p)
{
    if (p > N) { v[++ C] = n, C[c] = s; return ; }
    Dfs (n + (1 << p - 1), s + 1, p + 2);
    Dfs (n, s, p + 1);
}
int Main ()
{
    rg int i, j, k, l; int K; scanf ("%d%d", &N, &K);
    for (i = 1, Dfs (0, 0, 1); i <= C; ++ i) f[1][v[i]][c[i]] = 1LL;
    for (i = 2; i <= N; ++ i)
        for (j = 1; j <= C; ++ j)
            for (k = 1; k <= C; ++ k)
            {
                if (v[j] & v[k]) continue;
                if (((v[j] << 1) & v[k]) || ((v[j] >> 1) & v[k])) continue;
                for (l = K; l >= c[j]; -- l) f[i][v[j]][l] += f[i - 1][v[k]][l - c[j]];
            }
    LL Answer = 0; for (i = 1; i <= C; ++ i) Answer += f[N][v[i]][K];
    printf ("%lld", Answer);
    return 0;
}
int ZlycerQan = Main (); int main (int argc, char *argv[]) { return 0; }
