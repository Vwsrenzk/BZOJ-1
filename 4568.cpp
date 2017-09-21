#include <cstdio>
#include <iostream>
 
const int BUF = 12312334;
char Buf[BUF], *buf = Buf;
#define _L 60
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
 
typedef long long LL;
#define Max 20040
struct E { E *n; int to; };
struct LB
{   
    long long v[_L | 1];
    inline void Insert (long long key)
    {
        for (register int i = _L; i >= 0; -- i)
            if (key & (1LL << i))
            {
                if (!v[i])  { v[i] = key; break; }
                key ^= v[i];
            }
    }
 
    void Clear () { for (register int i = 0; i <= _L; ++ i) v[i] = 0; }
    long long Query ()
    {
        long long res = 0;
        for (register int i = _L; i >= 0; -- i)
            if ((res ^ v[i]) > res) res ^= v[i];
        return res;
    }
};
 
inline void read_L (LL &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
LL key[Max];
int N, in[Max];
struct S_D
{
    S_D *Left, *Right;
    LB key;
    int Mid;
};
LB Answer;
inline void swap (int &a, int &b) 
{
    int now = a; a = b, b = now;
}
class Segment_Tree
{
    private :
        S_D poor[Max << 2], *Ta, *Root;   
         
        inline LB Merge (LB A, LB B)
        {
            LB res; res = B;
            for (register int i = 0; i <= _L; ++ i)
                if (A.v[i]) res.Insert (A.v[i]);
            return res;
        }
     
        inline S_D *New (int l, int r)
        {
            ++ Ta, Ta->key.Clear (), Ta->Left = Ta->Right = NULL;
            Ta->Mid = l + r >> 1; return Ta;
        }
 
        void Build (S_D *&now, int l, int r)
        {
            now = New (l, r);
            if (l == r) return ;
            Build (now->Left, l, now->Mid), Build (now->Right, now->Mid + 1, r);
        }
 
        void C (S_D *&now, int L, int R, int pos, LL to)
        {
            if (L == R) { now->key.Insert (to); return ; }
            if (pos <= now->Mid) C (now->Left, L, now->Mid, pos, to);
            if (pos > now->Mid) C (now->Right, now->Mid + 1, R, pos, to);
            now->key = Merge (now->Left->key, now->Right->key);
        }
        void Q (S_D *&now, int L, int R, int l, int r)
        {
            if (l <= L && R <= r) { Answer = Merge (Answer, now->key); return ; }
            if (l <= now->Mid) Q (now->Left, L, now->Mid, l, r);
            if (r > now->Mid) Q (now->Right, now->Mid + 1, R, l, r);
        }
 
    public :
     
        Segment_Tree () { Ta = poor; }  
        void Build (int l, int r) { return Build (Root, l, r); }        
        void C (int pos, LL to) { return C (Root, 1, N, pos, to); }
        void Q (int l, int r) { return Q (Root, 1, N, l, r); }  
};
Segment_Tree Seg;
class Tree_Chain
{
    private : 
 
        int size[Max], deep[Max], son[Max], chain[Max], father[Max];
        E poor[Max << 1], *Ta, *list[Max];
        int Count;
    public :
         
        Tree_Chain () { Ta = poor; }
         
        void Do () 
        { 
            Dfs_1 (1, 0), Count = 0, Dfs_2 (1, 1); 
            for (register int i = 1; i <= N; ++ i)
                Seg.C (in[i], key[i]);
        }
        void Dfs_1 (int now, int F)
        {
            father[now] = F, size[now] = 1, deep[now] = deep[F] + 1;
            for (E *e = list[now]; e; e = e->n)
                if (e->to != F)
                {
                    Dfs_1 (e->to, now), size[now] += size[e->to];
                    if (size[son[now]] < size[e->to]) son[now] = e->to;
                }
        }
 
        void Dfs_2 (int now, int P)
        {
            chain[now] = P; in[now] = ++ Count;
            if (son[now]) Dfs_2 (son[now], P);
            else return ; 
            for (E *e = list[now]; e; e = e->n)
                if (e->to != son[now] && e->to != father[now])
                    Dfs_2 (e->to, e->to);
        }
         
        void In (int u, int v)
        {
            ++ Ta, Ta->to = v, Ta->n = list[u], list[u] = Ta;
            ++ Ta, Ta->to = u, Ta->n = list[v], list[v] = Ta;
        }
 
        LL Q (int x, int y)
        {
            for (Answer.Clear (); chain[x] != chain[y]; x = father[chain[x]])
            {
                if (deep[chain[x]] < deep[chain[y]]) swap (x, y);
                Seg.Q (in[chain[x]], in[x]);
            }
            if (deep[x] > deep[y]) swap (x, y);
            Seg.Q (in[x], in[y]);
            return Answer.Query ();
        }
};
Tree_Chain T;
 
int Main ()
{
    fread (buf, 1, BUF, stdin);
    int Q; read (N), read (Q); register int i;
    int x, y;
    for (i = 1; i <= N; ++ i) read_L (key[i]);
    for (i = 1; i < N; ++ i)
        read (x), read (y), T.In (x, y);
    Seg.Build (1, N), T.Do ();
    for (i = 1; i <= Q; ++ i)
    {
        read (x), read (y);
        printf ("%lld\n", T.Q (x, y));
    }
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
