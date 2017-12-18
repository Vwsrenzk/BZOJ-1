#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstring>
#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 1000
#define INF 1e8
int N, M, p[Max]; 
using std :: swap;
typedef double flo; flo a[Max], mn, s[Max], avg;
inline flo Pow (flo x) { return x * x; }
void BackFire ()
{
    memset (s, 0, sizeof s); flo r = 0, T; rg int i;
    for (i = 1; i <= N; ++ i) p[i] = rand () % M + 1, s[p[i]] += a[i];
    flo k; int x, y;
    for (i = 1; i <= M; ++ i) r += (s[i] - avg) * (s[i] - avg);
    for (T = 10000; T > 0.1; T *= 0.9)
    {
        k = r; x = rand () % N + 1;
        if (T > 500) y = std :: min_element (s + 1, s + 1 + M) - s;
        else y = rand () % M + 1;
        if (p[x] == y) continue;
        r -= Pow(s[p[x]] - avg), r += Pow(s[p[x]] - a[x] - avg);
        r -= Pow(s[y] - avg), r += Pow(s[y] + a[x] - avg);
        if (rand () % 100000 + 1 > T && r > k) r = k;
        else s[p[x]] -= a[x], s[y] += a[x], p[x] = y;
    }
    if (r < mn) mn = r;
}
int main (int argc, char *argv[])
{
    read (N), read (M); rg int i;
    for (i = 1; i <= N; ++ i) scanf ("%lf", &a[i]), avg += i[a], swap (a[i], a[rand () % i + 1]);
    avg /= (flo) M, mn = INF;
    for (i = 1; i <= 5000; ++ i) BackFire ();
    printf ("%.2lf", sqrt (mn / (flo) M)); return 0;
}
