#include <cstdio>
#include <iostream>
#define rg register
void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 300009
typedef double flo; typedef long long LL;
LL f[Max], s[Max]; int q[Max], N, L;
LL P (LL a) { return a * a; }
 
flo C (int j, int k)
{
    return (flo) (f[k] - f[j] + P (s[k] + L + 1) - P (s[j] + L + 1)) / (2.0 * (s[k] - s[j]));
}
int main (int argc, char *argv[])
{
    int l = 0, r = 0, x; read (N), read (L); rg int i, j;
    for (i = 1; i <= N; ++ i) read (x), s[i] = s[i - 1] + x;
    for (i = 1; i <= N; ++ i) s[i] += i;
    for (i = 1; i <= N; ++ i)
    {
        for (; l < r && C (q[l], q[l + 1]) <= s[i]; ++ l);
        int t = q[l]; f[i] = f[t] + P (s[i] - s[t] - L - 1);
        for (; l < r && C (q[r], i) < C (q[r - 1], q[r]); -- r);
        q[++ r] = i;
    }
    printf ("%lld", f[N]); return 0;
}
