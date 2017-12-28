#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

#define Max 1000006
int _v[Max << 1], _n[Max << 1], EC = 1, list[Max];
inline void In (int u, int v)
{ _v[++ EC] = v, _n[EC] = list[u], list[u] = EC; }
typedef long long LL;
int dfn[Max], st[Max], low[Max], top, DC, SC;
bool is[Max];
int a[Max];
int key[Max];
inline int cmin (int &a, int b) { if (b < a) a = b; }
void Dfs (int n, int l)
{
    st[++ top] = n; low[n] = dfn[n] = ++ DC;
    rg int i, v;
    for (i = list[n]; i; i = _n[i])
        if (i != l && i != (l ^ 1))
        {
            if (!dfn[v = _v[i]]) Dfs (v, i), cmin (low[n], low[v]); 
            else cmin (low[n], dfn[v]), is[v] = true;
        }
    if (low[n] == dfn[n])
        if (!is[n]) -- top;
        else
        {
            for (; st[top] != n; a[++ SC] = st[top --], is[a[SC]] = true);
            -- top; a[++ SC] = n;
        }
}
LL f[Max][2];
using std :: max;
LL data[Max][2];
void Dp (int n, int F)
{
    f[n][0] = 0, f[n][1] = key[n]; rg int i, v;
    for (i = list[n]; i; i = _n[i])
        if (!is[v = _v[i]] && v != F)
            Dp (v, n), f[n][0] += max (f[v][1], f[v][0]), f[n][1] += f[v][0];        is[n] = true;
}
int main (int argc, char *argv[])
{
    int N; read (N); rg int i, j; int x;
    for (i = 1; i <= N; ++ i)
        read (key[i]), read (x), In (x, i), In (i, x);
    LL res = 0, s = 0;    
    for (i = 1; i <= N; ++ i)
    {
        if (is[i]) continue;
        top = 0, SC = 0, Dfs (i, 0), res = 0;
        for (i = 1; i <= SC; ++ i) Dp (a[i], 0);
        data[1][0] = f[a[1]][0], data[1][1] = 0;
        
        for (j = 2; j <= SC; ++ j)
        {
            data[j][0] = f[a[j]][0], data[j][1] = f[a[j]][1];
            data[j][0] += max (data[j - 1][0], data[j - 1][1]);
            data[j][1] += data[j - 1][0];
        }

        res = max (data[SC][1], data[SC][0]);
           data[1][0] = 0, data[1][1] = f[a[1]][1];

        for (j = 2; j <= SC; ++ j)
        {
            data[j][0] = f[a[j]][0], data[j][1] = f[a[j]][1];
            data[j][0] += max (data[j - 1][0], data[j - 1][1]);
            data[j][1] += data[j - 1][0];
        }
        res = max (res, data[SC][0]), s += res;
    }
    std :: cout << s;
    return 0;
}
