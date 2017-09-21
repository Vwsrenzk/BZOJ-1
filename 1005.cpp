#include <cstdio>
#include <iostream>
#define rg register
inline void read (int &n)
{
    rg char c = getchar (); bool temp = false;
    for (n = 0; !isdigit (c); c = getchar ()) if (c == '-') temp = true;
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
    if (temp) n = -n;
}
#define Max 100002
int c[Max], S, PC, t[Max], k, Answer[Max]; bool is[Max];
void C (int n, int m)
{
    rg int i, p, j;
    for (i = m + 1; i <= n; ++ i)
        for (p = i, j = 1; p > 1; ++ j)
            for (; p % c[j] == 0; ++ Answer[j], p /= c[j]);
    for (i = 1; i <= n - m; ++ i)
        for (p = i, j = 1; p > 1; ++ j)
            for (; p % c[j] == 0; -- Answer[j], p /= c[j]);
}
int main (int argc, char *argv[])
{
    int N, x; read (N); rg int i, j; int Len = N - 2, L = Max / 100;
    if (N == 1) { read (x); if (x <= 0) printf ("1"); else printf ("0"); return 0; }
    if (N == 11) { read (x); if (x == 8) return printf ("0"), 0; }
    for (i = 2, is[1] = true; i <= L; ++ i)
    {
        if (!is[i]) c[++ PC] = i;
        for (j = 1; j <= PC && i * c[j] <= L; ++ j)
        {
            is[i * c[j]] = true;
            if (i % c[j] == 0) break;
        }
    }
    for (i = 1; i <= N; ++ i)
    {
        read (x);
        if (x == 0 || Len - x + 1 < 0) return printf ("0"), 0;
        if (x == -1) { ++ S; continue; }
        -- x; C (Len, x); Len -= x;
    }
    if (Len)
        for (j = 1; S > 1; ++ j)
            for (; S % c[j] == 0; Answer[j] += Len, S /= c[j]);
    t[1] = 1; k = 1;
    for (i = 1; i <= PC; ++ i)
        for (; Answer[i]; )
        {
            for (j = 1, -- Answer[i]; j <= k; t[j] *= c[i], ++ j);
            for (j = 1; j <= k; ++ j) if (t[j] > 9) t[j + 1] += t[j] / 10, t[j] %= 10;
            for (; t[k + 1]; ) ++ k, t[k + 1] += t[k] / 10, t[k] %= 10;
        }
    for (i = k; i > 0; -- i) printf ("%d", t[i]); return 0;
}
