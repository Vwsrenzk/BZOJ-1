#include <cstdio>
#define rg register
typedef long long LL;
int main (int argc, char *argv[])
{
    int N; scanf ("%d", &N); rg int i; LL s = 0;
    for (i = 1; i <= N; ++ i) s += N / i;
    printf ("%lld", s); return 0;
}
