#include <cstdio>
#include <iostream>

#define rg register
#define Max 300007
#define INF 1e8
const int BUF = 12312331; char Buf[BUF], *buf = Buf;
inline void read (int &n)
{
    bool t = false;
    for (n = 0; !isdigit (*buf); ++ buf) if (*buf == '-') t = true;
    for (; isdigit (*buf); n = n * 10 + *buf - '0', ++ buf);
    if (t) n = -n;
}
struct E { E *n; int v; } *list[Max], poor[Max << 1], *Ta = poor;
int N, in[Max], tk[Max], TC, key[Max];
int GT ()
{
    for (; (*buf) != 'Q' && (*buf) != 'C'; ++ buf);
    if (*(buf + 1) == 'M') return 2;
    else if (*(buf + 1) == 'S') return 1; return 3;
}
inline int min (int a, int b) { return a < b ? a : b; }
inline int max (int a, int b) { return a > b ? a : b; }
struct SD 
{ 
    SD *L, *R; int l, r, m, mx, s; 
    inline void Up () { mx = max (L->mx, R->mx), s = L->s + R->s; }
} poorT[Max << 2 | 1], *TT = poorT;
class SegmentTRee
{
    private : SD *Root;
    
    private :
        
        inline SD* New (int _l, int _r)
        { 
            ++ TT, TT->L = TT->R = NULL; TT->mx = TT->s = 0; 
            TT->l = _l, TT->r = _r, TT->m = _l + _r >> 1; return TT; 
        }
        
        void Build (SD *&n, int l, int r)
        {
            n = New (l, r); if (l == r) { n->mx = n->s = tk[l];  return ; }
            Build (n->L, l, n->m), Build (n->R, n->m + 1, r); n->Up ();
        }
        
        void C (SD *&n, int p, int t)
        {
            if (n->l == n->r) { n->mx = n->s = t; return ; }
            if (p <= n->m) C (n->L, p, t); else C (n->R, p, t); n->Up ();
        }
        
        int Q (SD *&n, int l, int r, bool t)
        {
            if (l <= n->l && n->r <= r) { if (t) return n->s; return n->mx; } 
            int A, B; if (t) A = B = 0; else A = B = -INF; 
            if (l <= n->m) A = Q (n->L, l, r, t); if (r > n->m) B = Q (n->R, l, r, t);
            return t ? A + B : max (A, B);
        }
        
    public :
        
        void Build (int l, int r) { return Build (Root, l, r); }
        void C (int p, int t) { return C (Root, p, t); }
        int Q_max (int l, int r) { return Q (Root, l, r, false); }
        int Q_sum (int l, int r) { return Q (Root, l, r, true); }
} Seg;
    
inline void swap (int &a, int &b) { int c = a; a = b, b = c; }
inline void cmax (int &a, int b) { if (b > a) a = b; }
class TreeChain
{
    private : int d[Max], s[Max], son[Max], c[Max], f[Max];

    private :
        
        void Dfs_1 (int n, int F)
        {
            s[n] = 1, d[n] = d[F] + 1, f[n] = F; int V;
            for (E *e = list[n]; e; e = e->n)
                if ((V = e->v) != F)
                {
                    Dfs_1 (V, n); s[n] += s[V];
                    if (s[son[n]] < s[V]) son[n] = V;
                }
        }
        
        void Dfs_2 (int n, int C)
        {
            c[n] = C; in[n] = ++ TC, tk[TC] = key[n];
            if (son[n]) Dfs_2 (son[n], C); else return ; int V;
            for (E *e = list[n]; e; e = e->n)
                if ((V = e->v) != f[n] && V != son[n]) Dfs_2 (V, V);
        }
        
        inline int Q (int x, int y, bool t)
        {
            int r; if (t) r = 0; else r = -INF;
            for (; c[x] != c[y]; x = f[c[x]])
            {
                if (d[c[x]] < d[c[y]]) swap (x, y);
                if (t) r += Seg.Q_sum (in[c[x]], in[x]);
                else cmax (r, Seg.Q_max (in[c[x]], in[x]));
            }
            if (d[x] > d[y]) swap (x, y);
            return t ? (r + Seg.Q_sum (in[x], in[y])) : (max (r, Seg.Q_max (in[x], in[y])));
        }
        
    public :
        
        inline void Prepare () { Dfs_1 (1, 0), Dfs_2 (1, 1), Seg.Build (1, N); }
        inline void C (int p, int t) { return Seg.C (in[p], t); }
        inline int Q_max (int x, int y) { return Q (x, y, false); }
        inline int Q_sum (int x, int y) { return Q (x, y, true); }
} T;

int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin); int i, j; int x, y; read (N);
    for (i = 1; i < N; ++ i)
    {
        read (x), read (y);
        ++ Ta, Ta->v = y, Ta->n = list[x], list[x] = Ta;
        ++ Ta, Ta->v = x, Ta->n = list[y], list[y] = Ta;
    }
    for (i = 1; i <= N; ++ i) read (key[i]);
    for (read (N), T.Prepare (); N; -- N)
    {
        i = GT (); read (x), read (y);
        if (i == 1) printf ("%d\n", T.Q_sum (x, y));
        else if (i == 2) printf ("%d\n", T.Q_max (x, y));
        else T.C (x, y);
    }
    return 0;
}
