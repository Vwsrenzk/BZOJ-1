#include <cstdio>
#include <iostream>
#include <algorithm>

typedef long long LL;
#define mo 1004535809
#define rg register
#define Max 17000
LL G, p[Max], a[Max], b[Max], f[Max], g[Max];
int T, rd[Max], is[Max];
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
inline LL pls (LL a, LL b) { a += b; return a >= mo ? a - mo : a; }
inline LL dec (LL a, LL b) { a -= b; return a < 0 ? a + mo : a; }
inline LL pow (LL x, LL y, LL p)
{
    LL res = 1;
    for (; y; y >>= 1, (x *= x) %= p)
        if (y & 1) (res *= x) %= p;
    return res;
}
int Calc (int x)
{
    if (x == 2) return 1; bool F;
    for (rg int i = 2, j; i; ++ i)
    {
        F = true;
        for (j = 2; j * j < x; ++ j)
            if (pow (i, (x - 1) / j, x) == 1)
            { F = false; break; }
        if (F) return i;
    }
}

LL inv;
void NTT (LL *a, int N, int f = 1)
{
    rg int i, j, k; LL wn, w, x, y;
    for (i = 0; i < N; ++ i) if (rd[i] > i) std :: swap (a[i], a[rd[i]]);
    for (k = 1; k < N; k <<= 1)
    {
        wn = pow (3, (mo - 1) / (k << 1), mo);
        for (j = 0; j < N; j += k << 1)
            for (w = 1, i = 0; i < k; ++ i, (w *= wn) %= mo)
                x = a[i + j], y = a[i + j + k] * w % mo, a[i + j] = pls (x, y), a[i + j + k] = dec (x, y);
    }
    if (f == -1) std :: reverse (a + 1, a + N);
}
void mul (LL *g, LL *f, int N, int M)
{
    rg int i;
    for (i = 0; i < N; ++ i) a[i] = g[i] % mo, b[i] = f[i] % mo;

    NTT (a, N), NTT (b, N);
    for (i = 0; i < N; ++ i) (a[i] *= b[i]) %= mo;
    NTT (a, N, -1);
    for (i = 0; i < N; ++ i) (a[i] *= inv) %= mo;
    for (i = 0; i < M - 1; ++ i)
        g[i] = (a[i] + a[i + M - 1]) % mo;
}
int main (int argc, char *argv[])
{
    int N, M, X, S, P, C, x; rg int i, j;
    scanf ("%d%d%d%d", &C, &M, &X, &S); G = Calc (M);
    for (i = 1; i <= S; ++ i)
        read (x), is[x] = 1;
    int pos = -1, L = 0;
    for (i = 0, j = 1; i < M - 1; ++ i, (j *= G) %= M)
    {
        if (is[j]) f[i] = 1;
        if (j == X) pos = i;
    }
        
    P = (M - 1) << 1;
    for (N = 1; N <= P; N <<= 1, ++ L);
    for (i = 0; i < N; ++ i)
        rd[i] = (rd[i >> 1] >> 1) | ((i & 1) << (L - 1));
    inv = pow (N, mo - 2, mo);
    for (g[0] = 1; C; C >>= 1, mul (f, f, N, M))
        if (C & 1) mul (g, f, N, M);

    if (pos != -1) std :: cout << g[pos] % mo;
    else puts ("0");

    return 0;
}
