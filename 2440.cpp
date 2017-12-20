#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

#define Max 1000006
int mu[Max], p[Max]; bool is[Max];

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
}

#define INF 2e9
typedef long long LL;
LL Calc (LL N)
{
    LL res = 0;
    for (rg int i = 1; i * i <= N; ++ i)
        res += N / (i * i) * mu[i];
    return res;
}
int main (int argc, char *argv[])
{
    int T, K; read (T); rg LL l, r, m, res;
    Euler (Max - 1);
    for (; T; -- T)
    {
        read (K);
        l = K, r = INF;
        for (; l <= r; )
        {
            m = l + r >> 1;
            if (Calc (m) >= K) r = m - 1, res = m;
            else l = m + 1;
        }
        printf ("%lld\n", res);
    }
    return 0;
}
