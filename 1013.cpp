#include <cstdio>
#include <iostream>
#include <cstring>
#define rg register
#define Max 50
typedef double flo; flo v[Max][Max], s[Max];
inline flo P (flo x) { return x * x; }
inline void swap (flo &a, flo &b) { flo c = a; a = b, b = c; }
int main (int argc, char *argv[])
{
    int N, p; scanf ("%d", &N); rg int i, j, k; flo x;
    for (i = 1; i <= N; ++ i) scanf ("%lf", &s[i]);
    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= N; ++ j)
            scanf ("%lf", &x), v[i][j] = (x - s[j]) * 2.0, v[i][N + 1] += P (x) - P (s[j]);
    memset (s, 0, sizeof s);
    for (i = 1; i <= N; ++ i)
    {
        for (p = i, j = i + 1; j <= N; ++ j) if (v[j][i] > v[p][i]) p = i;
        if (p != i) for (j = i; j <= N + 1; ++ j) swap (v[p][j], v[i][j]);
        for (j = i + 1; j <= N; ++ j)
            for (k = i + 1, x = v[i][i] / v[j][i]; k <= N + 1; ++ k)
                v[j][k] = v[i][k] - x * v[j][k];
    }
    for (i = N; i >= 1; -- i)
    {
        for (j = i + 1; j <= N; ++ j) v[i][N + 1] -= s[j] * v[i][j];
        s[i] = v[i][N + 1] / v[i][i];   
    }
    for (i = 1; i < N; ++ i) printf ("%.3lf ", s[i]); printf ("%.3lf", s[i]); return 0;
}
