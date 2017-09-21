#include <cstdio>
#include <iostream>
#include <algorithm>
typedef double flo;
#define Max 50004
#define rg register
struct L
{
    flo k, b; int id;
    bool operator < (const L &A) const
    {
        return k == A.k ? b > A.b : k < A.k;
    }
    flo operator & (const L &A) const
    {
        return (A.b - b) / (k - A.k);
    }
} l[Max]; int s[Max], t;
bool Comp (const int &a, const int &b)
{
    return l[a].id < l[b].id;
}
int main (int argc, char *argv[])
{
    int N, M; rg int i, j; scanf ("%d", &N);
    for (i = 1; i <= N; ++ i) scanf ("%lf%lf", &l[i].k, &l[i].b), l[i].id = i;
    std :: sort (l + 1, l + 1 + N); s[++ t] = 1;
    for (i = 2; i <= N; ++ i)
    {
        if (l[i].k == l[i - 1].k) continue;
        for (; t > 1 && (l[i] & l[s[t - 1]]) <= (l[s[t - 1]] & l[s[t]]); -- t);
        s[++ t] = i;
    }
    std :: sort (s + 1, s + 1 + t, Comp); for (i = 1; i <= t; ++ i) printf ("%d ", l[s[i]].id);
    return 0;
}
