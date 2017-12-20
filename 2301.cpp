#include <cstdio>
#include <iostream>

#define rg register
#define Max 50007
int p[Max], mu[Max], sm[Max]; bool is[Max];
typedef long long LL;
inline LL min (LL a, LL b) { return a < b ? a : b; }
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

void Euler (int N)
{
    rg int i, j, k; int C = 0; mu[1] = 1;
    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) p[++ C] = i, mu[i] = -1;
        for (j = 1; j <= C; ++ j)
        {
            if ((k = i * p[j]) > N) break;
            is[k] = true;
            if (i % p[j] == 0) { mu[k] = 0; break; }
            else mu[k] = -mu[i];
        }
    }
    for (i = 1; i <= N; ++ i) mu[i] += mu[i - 1];
}
LL Z (LL N, LL M)
{
    LL res = 0; rg LL i, j;
    if (N > M) std :: swap (N, M);
    for (i = 1; i <= N; i = j + 1)
    {
        j = min (N / (N / i), M / (M / i));
        res += (LL) (mu[j] - mu[i - 1]) * (N / i) * (M / i);
    }
    return res;
}
int main (int argc, char *argv[])
{
    int T, A, B, C, D, K; read (T); rg int i;
    Euler (Max - 1); LL Answer = 0;
    for (; T; -- T)
    {
        read (A), read (B), read (C), read (D), read (K);
        A = (A - 1) / K, C = (C - 1) / K, B /= K, D /= K;
        Answer = Z (B, D) - Z (A, D) - Z (C, B) + Z (A, C);
        printf ("%lld\n", Answer);
    }
    return 0;
}
