#include <cstdio>
#include <iostream>
#include <cmath>

#define rg register
#define Max 1000005
int p[Max], phi[Max];
bool is[Max];
typedef long long LL;
LL s[Max];
void Euler (int N)
{
    int C = 0; phi[1] = 1; rg int i, j;
    for (i = 2; i <= N; ++ i)
    {
        if (!is[i]) p[++ C] = i, phi[i] = i - 1;
        for (j = 1; j <= C && i * p[j] <= N; ++ j)
        {
            is[i * p[j]] = true;
            if (i % p[j] == 0) phi[i * p[j]] = phi[i] * p[j];
            else phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    for (i = 1; i <= N; ++ i) s[i] = s[i - 1] + phi[i];
}
inline int min (int a, int b) { return a < b ? a : b; }

int main (int argc, char *argv[])
{
    int N, M; scanf ("%d%d", &N, &M); rg int i, j; 
    if (N > M) std :: swap (N, M);
    Euler (N); 
    LL Answer = 0;
    for (i = 1; i <= N; i = j + 1)
    {
        j = min (N / (N / i), M / (M / i));
        Answer += (LL) (s[j] - s[i - 1]) * (N / i) * (M / i);
    }
    Answer = (LL) Answer * 2 - (LL) N * M;
    std :: cout << Answer;    
    return 0;
}
