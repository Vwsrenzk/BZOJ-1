#include <cstdio>

#define rg register
#define Max 20
int f[Max][Max], d[Max];
inline int abs (int x) { return x < 0 ? -x : x; }
int Calc (int x)
{
    int c = 0, res = 0; rg int i, j, k;
    for (; x; d[++ c] = x % 10, x /= 10);
    for (i = 1; i < c; ++ i)
        for (j = 1; j <= 9; ++ j) res += f[i][j];
    for (i = c; i; -- i)
    {
        for (j = (i == c); j < d[i]; ++ j)
            if (i == c || abs (j - d[i + 1]) >= 2)
                res += f[i][j];
        if (i < c && abs (d[i + 1] - d[i]) < 2) break;
    }
    return res;
}
int main (int argc, char *argv[])
{
    rg int i, j, k;
    for (i = 0; i <= 9; ++ i) f[1][i] = 1;
    for (i = 1; i <= 10; ++ i)
        for (j = 0; j <= 9; ++ j)
        {
            for (k = 0; k <= j - 2; ++ k) f[i + 1][k] += f[i][j];
            for (k = j + 2; k <= 9; ++ k) f[i + 1][k] += f[i][j];
        }
    int N, M;
    scanf ("%d%d", &N, &M);
    printf ("%d", Calc (M + 1) - Calc (N));

    return 0;
}
