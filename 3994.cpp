#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

#define Max 50008
int mu[Max], p[Max], sm[Max], f[Max]; bool is[Max];

void Euler (int N)
{
    int C = 0; rg int i, j, k; mu[1] = 1;

    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) p[++ C] = i, mu[i] = -1;
        for (j = 1; j <= C; ++ j)
        {
            k = i * p[j];
            if (k > N) break;
            is[k] = true;
            if (i % p[j] == 0) { mu[k] = 0; break; }
            else mu[k] = -mu[i];
        }
    }
    for (i = 1; i <= N; ++ i) sm[i] = sm[i - 1] + mu[i];
}
inline int min (int a, int b) { return a < b ? a : b; }
int F (int N)
{
    int res = 0;
    for (rg int i = 1, j; i <= N; i = j + 1)
        j = N / (N / i), res += (N / i) * (j - i + 1);
    return res;
}
typedef long long LL;
#ifdef WIN32
#define PLL "%I64d"
#else
#define PLL "%lld"
#endif
int main (int argc, char *argv[])
{
    int T, N, M; read (T); rg int i, j; Euler (Max - 1);

    for (i = 1; i < Max; ++ i) f[i] = F (i);
    
    for (LL Answer; T; -- T)
    {
        read (N), read (M); Answer = 0;
        if (N > M) std :: swap (N, M);
            
        for (i = 1; i <= N; i = j + 1)
        {
            j = min (N / (N / i), M / (M / i));
            Answer += (LL) (sm[j] - sm[i - 1]) * f[N / i] * f[M / i];
        }
        printf (PLL"\n", Answer); 
    }
    return 0;
}
