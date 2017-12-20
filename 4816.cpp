#include <cstdio>
#include <iostream>
#define rg register
#define Max 1000050
#define mo 1000000007
inline int min (int a, int b) { return a < b ? a : b; }
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
typedef long long LL;
LL f[Max], invf[Max];

LL pow (LL x, LL y)
{
    LL res = 1;
    for (; y; y >>= 1, (x *= x) %= mo)
        if (y & 1) (res *= x) %= mo;
    return res;
}
inline void pls (LL &a, LL b) { a += b; if (a >= mo) a -= mo; }
int main (int argc, char *argv[])
{
    rg int i, j; LL inv; int N, M, T;
    f[1] = 1;
    for (i = 2; i < Max; ++ i) pls (f[i], f[i - 1] + f[i - 2]);
    for (i = 1; i < Max; ++ i)
    {
        inv = pow (f[i], mo - 2);
        for (j = i << 1; j < Max; j += i) (f[j] *= inv) %= mo;
    }
    for (f[0] = i = 1; i < Max; ++ i) (f[i] *= f[i - 1]) %= mo;
    for (i = 0; i < Max; ++ i) invf[i] = pow (f[i], mo - 2);

    read (T); LL Answer;
    for (; T; -- T)
    {
        read (N), read (M); Answer = 1;
        if (N > M) std :: swap (N, M);
        for (i = 1; i <= N; i = j + 1)
        {
            j = min (N / (N / i), M / (M / i));
            (Answer *= pow (pow (f[j] * invf[i - 1] % mo, (LL) N / i), (LL) M / i)) %= mo;
        }
        printf ("%lld\n", Answer);
    }    
    return 0;
}
