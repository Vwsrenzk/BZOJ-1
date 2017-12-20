#include <cstdio>
#include <iostream>
#include <cmath>
#define rg register
#define Max 10000010
typedef long long LL;
LL phi[Max], p[Max]; bool is[Max];
void Euler (int N)
{
    int C = 0; rg LL i, j, k; phi[1] = 1;
    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) p[++ C] = i, phi[i] = i - 1;
        for (j = 1; j <= C; ++ j)
        {
            if ((k = p[j] * i) > N) break;
            is[k] = true;
            if (i % p[j] == 0) { phi[k] = phi[i] * p[j]; break; }    
            else phi[k] = phi[i] * (p[j] - 1);
        }
    }
}
LL get (LL N)
{
    rg LL i, s = N;
    for (i = 2; i * i <= N; ++ i)
        if (N % i == 0)
            for (s -= s / i, N /= i; N % i == 0; N /= i);
    if (N > 1) s -= s / N;
    return s;
}
int main (int argc, char *argv[])
{
    LL N; std :: cin >> N; rg LL i;
    LL Answer = 0; Euler (sqrt (N) + 2);
    for (i = 1; i * i <= N; ++ i)
        if (N % i == 0)
        {
            if (i * i != N)
                Answer += phi[i] * (N / i);
            Answer += i * get (N / i);
        }
    std :: cout << Answer;    
    return 0;
}
