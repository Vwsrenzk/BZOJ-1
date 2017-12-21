#include <cstdio>
#include <iostream>
#include <cstdlib>
#define Max 500005
#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
int _n[Max << 1], _v[Max << 1], list[Max], EC, key[Max];
int f[Max], up[Max], s[Max], d[Max], id[Max], son[Max], tk[Max];
void Dfs_1 (int n, int F)
{
    f[n] = F, d[n] = d[F] + 1, s[n] = 1;
    for (rg int i = list[n]; i; i = _n[i])
        if (_v[i] != F)
        {
            Dfs_1 (_v[i], n), s[n] += s[_v[i]];
            if (s[son[n]] < s[_v[i]]) son[n] = _v[i];
        }
}
int TC;
void Dfs_2 (int n, int C)
{
    id[n] = ++ TC, tk[TC] = key[n], up[n] = C;        
    if (son[n]) Dfs_2 (son[n], C); else return ;
    for (rg int i = list[n]; i; i = _n[i])
        if (_v[i] != son[n] && _v[i] != f[n]) Dfs_2 (_v[i], _v[i]);
}

namespace seg
{
    int L[Max << 2], R[Max << 2], key[Max << 2];

    void Build (int n, int l, int r)
    {
        L[n] = l, R[n] = r;
        if (l == r) { key[n] = tk[l]; return ; }
        int m = l + r >> 1;
        Build (n << 1, l, m), Build (n << 1 | 1, m + 1, r);
        key[n] = key[n << 1] ^ key[n << 1 | 1];
    }

    void Modi (int n, int p, int k)
    {
        if (L[n] == R[n]) { key[n] = k; return; }
        int m = L[n] + R[n] >> 1;
        if (p <= m) Modi (n << 1, p, k); else Modi (n << 1 | 1, p, k);
        key[n] = key[n << 1] ^ key[n << 1 | 1];
    }

    int Query (int n, int l, int r)
    {
        if (l <= L[n] && R[n] <= r) return key[n];
        int m = L[n] + R[n] >> 1, ls = n << 1, rs = n << 1 | 1, a = -1;
        if (l <= m) a = Query (ls, l, r); 
        if (r > m) 
        {
            if (a != -1) a ^= Query (rs, l, r);
            else a = Query (rs, l, r);
        }
        return a;
    }
}
int in[Max];
inline void In (int u, int v)
{ _v[++ EC] = v, _n[EC] = list[u], list[u] = EC, ++ in[v]; }

inline bool Ask (int x, int y)
{
    int res = -1;
    for (; up[x] != up[y]; x = f[up[x]])
    {
        if (d[up[x]] < d[up[y]]) std :: swap (x, y);
        if (res == -1) res = seg :: Query (1, id[up[x]], id[x]);
        else res ^= seg :: Query (1, id[up[x]], id[x]);
    }
    if (d[x] > d[y]) std :: swap (x, y);
    if (res == -1) res = seg :: Query (1, id[x], id[y]);
    else res ^= seg :: Query (1, id[x], id[y]);
    return res != 0;
}
int pos[Max];
int main (int argc, char *argv[])
{
    int N, M, x, y; read (N); rg int i; int f1 = 0, f2 = 0;
    for (i = 1; i <= N; ++ i) read (key[i]);
    for (i = 1; i < N; ++ i)
        read (x), read (y), In (x, y), In (y, x);        

    int t = 0, pre; 
    for (i = 1; i <= N; ++ i)
        if (in[i] == 2) ++ f2; 
        else if (in[i] == 1) ++ f1, pos[++ t] = i;
    read (M); 
    char type[4];
    if (f1 + f2 == N) 
    {
        int n = pos[1];
        id[n] = ++ TC, pre = 0, tk[TC] = key[n];
        
        for (; n != pos[2]; )
            for (i = list[n]; i; i = _n[i])
                if (_v[i] != pre)
                { id[_v[i]] = ++ TC, tk[TC] = key[_v[i]], pre = n, n = _v[i]; break; }
                    
        id[n] = ++ TC, tk[TC] = key[n];

        seg :: Build (1, 1, N);    
        
        for (; M; -- M)
        {
            scanf ("%s", type),    read (x), read (y);
            if (type[0] == 'Q')
            {
                if (id[x] > id[y]) std :: swap (x, y);
                puts (seg :: Query (1, id[x], id[y]) == 0 ? "No" : "Yes");
            }
            else seg :: Modi (1, id[x], y);
        }
        return 0;
    }

    Dfs_1 (1, 0), Dfs_2 (1, 1), seg :: Build (1, 1, N);
    for (; M; -- M)
    {
        scanf ("%s", type); read (x), read (y);
        if (type[0] == 'Q')
            puts (Ask (x, y) ? "Yes" : "No");
        else seg :: Modi (1, id[x], y);
    }    

    return 0;
}
