#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#define rg register
#define INF 1e9
#define EPS 0.78
#define Max 100050
typedef long long LL;
int c[Max * 2][3], h[Max], d[Max], r[Max], li[Max], N, M, EC = 1;
LL Answer; int dis[Max][30], fi[Max], Dis[Max], Zero; bool Flag;
const int BUF = 123123123; char Buf[BUF], *buf = Buf;
inline void read (int &n)
{
     rg char c = getchar ();
     for (n = 0; !isdigit (*buf); ++ buf);
     for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
}
inline void Line (int x, int y, int z)
{
    c[++ EC][0] = y, c[EC][1] = fi[x], fi[x] = EC, c[EC][2] = z;
    c[++ EC][0] = x, c[EC][1] = fi[y], fi[y] = EC, c[EC][2] = z;
}
struct Node { Node *c[2]; int v, s, val; };
Node pool[Max * 40], *unp[Max * 40], *Ta = pool, **top = unp, *_r[Max][2], Null, *null = &Null;
struct Balance_Tree
{
    inline Node* Get(int x)
    {
        Node *k = (top != unp) ? *--top : Ta ++;
        k->c[0] = k->c[1] = null, k->s = 1, k->v = x, k->val = rand (); return k;
    }
    inline void Update (Node *x) { x->s = x->c[0]->s + x->c[1]->s + 1; }
    Node *Rebuild (int x, int y)
    {
        Node* R = Get (dis[li[1]][y] - r[li[1]]);
        for (rg int i = 2; i <= x; ++ i)
            Inse_r (R, Get (dis[li[i]][y] - r[li[i]]));
        return R;
    }
    void Rotate (Node *&x, Node *y)
    {
        bool k = y == x->c[0];
        x->c[!k] = y->c[k], y->c[k] = x, y->s=x->s;
        Update(x), x = y; return;
    }
    int Query (Node *x, int y)
    {
        if (x == null) return 0;
        if (y >= x->v) return x->c[0]->s + 1 + Query (x->c[1], y);
        return Query (x->c[0], y);
    }
    void Clear(Node* &x)
    {
        if (x == null) return;
        *top ++ = x, Clear (x->c[0]), Clear (x->c[1]), x = null;
    }
    void Inse_r (Node *&x, Node *y)
    {
        bool flag = y->v > x->v;
        if (x == null) { x = y; return; } else ++ x->s;
        Inse_r (x->c[flag], y);
        if (x->c[flag]->val > x->val) Rotate (x, x->c[flag]);
    }
} B;
#undef Max
struct Divide_Tree
{
#define Max 100050
    int suf[Max], ct[Max], sg[Max], s[Max], R, Sg;
    int Get_R (int C)
    {
        int _C = li[1]; rg int i, j;
        for (i = C; i >= 1; -- i)
            for (s[li[i]] = 1, j = fi[li[i]]; j; j = c[j][1])
                if (!sg[c[j][0]] && s[c[j][0]] > 0) s[li[i]] += s[c[j][0]];
        for (; true; )
        {
            bool flag = false;
            for (i = fi[_C]; i; i = c[i][1])
                if (s[c[i][0]] < s[_C] && !sg[c[i][0]] && s[c[i][0]] * 2 >= C)
                { _C = c[i][0], flag = true; break; }
            if (!flag) break;
        }
        for (i = 1; i <= C; ++ i) s[li[i]] = 0;
        return _C;
    }
    int Get_s (int x)
    {
        int le = 1, ri = 1; li[1] = x, s[x] = -1;
        for (rg int i; le <= ri; ++ le)
            for (i = fi[li[le]]; i; i = c[i][1])
                if (!s[c[i][0]] && !sg[c[i][0]]) s[li[++ ri] = c[i][0]] = -1;
        return ri;
    }
    void Clear (int x)
    {
        if (!sg[x] || sg[x] < Sg) return;
        sg[x] = 0, B.Clear (_r[x][0]), B.Clear (_r[x][1]);
        for (rg int i = fi[x]; i; i = c[i][1]) Clear (c[i][0]);
    }
    void Get (int x, int y)
    {
        ct[x] = 1, sg[x] = sg[suf[x]] + 1; rg int i, j;
        int _f = 0; _r[x][0] = B.Get (-y), _r[x][1] = B.Get (c[EC][2] - y);
        memcpy (dis[x], dis[suf[x]], sizeof dis[suf[x]]);
        for (i = 1; i < sg[x]; ++ i) dis[x][i] += c[EC][2];
        for (dis[x][sg[x]] = 0, i = suf[x], j = sg[x] - 1; i; i = suf[i], -- j)
        {
            ++ ct[i];
            if (j - 1 && ct[i] / (ct[suf[i]] + 1.0) > EPS) _f = suf[i];
            Answer += B.Query (_r[i][0], y - dis[x][j]), B.Inse_r (_r[i][0], B.Get (dis[x][j] - y));
            if (j - 1) Answer -= B.Query (_r[i][1], y - dis[x][j - 1]), B.Inse_r (_r[i][1], B.Get (dis[x][j - 1] - y));
        }
        if (_f) Sg = sg[_f], Clear (_f), Rebuild (_f, Sg, suf[_f]);
    }
    void Rebuild (int x, int y, int z)
    {
        int C = Get_s (x), _C = Get_R (C);
        dis[_C][y] = 0, Dfs (_C, 0, y), sg[_C] = y;
        if (z) suf[_C] = z; else suf[R = _C] = 0, _r[_C][1] = null;
        _r[_C][0] = B.Rebuild (C, y), ct[_C] = C;
        if (y > 1) _r[_C][1] = B.Rebuild (C, y - 1);
        for (rg int i = fi[_C]; i; i = c[i][1])
            if (!sg[c[i][0]]) Rebuild (c[i][0], y + 1, _C);
    }
    void Dfs (int x,int y,int z)
    {
        for (rg int i = fi[x]; i; i = c[i][1])
            if (!sg[c[i][0]] && c[i][0] != y)
                dis[c[i][0]][z] = dis[x][z] + c[i][2], Dfs (c[i][0], x, z);
    }
#undef Max
} A;
int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin);
       read (Zero), read (N), read (Zero), read (Zero), A.R = 1;
    Null.c[0] = Null.c[1] = &Null; int q, w;
    srand (time (0)), read (r[1]),  A.Get (1, r[1]); puts ("0");
    for (rg int i = 2; i <= N; ++ i)
    {
        read (q), q = q ^ (Answer % (int) INF), read (w);
        read (r[i]), h[i] = h[q] + 1, d[i] = d[q] + w;
        Line (i, q, w), A.suf[i] = q, A.Get (i, r[i]);
        printf ("%lld\n", Answer);
    }
    return 0;
}
