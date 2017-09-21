#include <cstdio>
#include <iostream>
#define Max 100005
#define rg register
typedef double flo; flo m[Max], s[Max];
int main (int argc, char *argv[]) 
{
    int N; flo A, Answer = 0; scanf ("%d%lf", &N, &A); rg int i, j, k;
    for (i = 1; i <= N; ++ i)
    {
        j = (int) (A * i + 1e-8);
        scanf ("%lf", &m[i]); Answer = 0;
        if (i <= 500) for (k = 1; k <= j; ++ k) Answer += m[k] * m[i] / (i - k);
        else Answer = s[j] * m[i] / (i - j / 2);
        printf ("%f\n", Answer); s[i] = s[i - 1] + m[i];
    }
    return 0;
}
