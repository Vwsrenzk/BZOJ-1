#include <cstdio>
#include <iostream>
#define rg register
typedef long long LL;
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 10000069
int p[Max], mu[Max]; bool is[Max];


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

inline int min (int a, int b) { return a < b ? a : b; }
int main (int argc, char *argv[])
{
    int N; read (N); rg int i, j, pos; Euler (Max - 1);
    long long res = 0; int L;
    
    for (pos = 1; p[pos] <= N && p[pos]; ++ pos)
        for (i = 1, L = N / p[pos]; i <= L; i = j + 1)
            j = L / (L / i), res += (LL) (L / i) * (L / i) * (mu[j] - mu[i - 1]);
    
        
    std :: cout << res;
    return 0;
}
