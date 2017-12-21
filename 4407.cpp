#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

#define mo 1000000007
#define Max 5000009
inline int min (int a, int b) { return a < b ? a : b; }
int f[Max], g[Max], F[Max], p[Max]; bool is[Max];
inline int pow (int x, int y)
{
    int res = 1;
    for (; y; y >>= 1, x = 1LL * x * x % mo)
        if (y & 1) res = 1LL * res * x % mo;
    return res;
}

void Euler (int N, int K)
{
    rg int i, j, k; int C = 0; F[1] = 1;
    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) 
            f[i] = pow (i, K), g[i] = i, F[i] = f[i] - 1, p[++ C] = i;
        for (j = 1; j <= C; ++ j)
        {
            if ((k = i * p[j]) > N) break;
            is[k] = true;
            if (i % p[j] == 0) 
            { 
                g[k] = g[i] * p[j];
                F[k] = g[i] != i ? 1LL * F[i / g[i]] * F[g[i] * p[j]] % mo : 1LL * F[i] * f[p[j]] % mo;
                break; 
            }
            else g[k] = p[j], F[k] = 1LL * F[i] * F[p[j]] % mo;
        }
    }
    for (i = 2; i < N; ++ i) F[i] = (F[i - 1] + F[i]) % mo;
}

int main (int argc, char *argv[])
{
    int T, K, N, M, res;
       read (T), read (K); rg int i, j; Euler (Max - 1, K);
    for (; T; -- T)
    {
        read (N), read (M), res = 0;
        if (N > M) std :: swap (N, M);
        for (i = 1; i <= N; i = j + 1)
        {
            j = min (N / (N / i), M / (M / i));
            res = (1LL * (F[j] - F[i - 1] + mo) * (N / i) % mo * (M / i) + res) % mo;
        }
        printf ("%d\n", res);
    }
    return 0;
}
