#include <cstdio>
#include <iostream>
#include <cstring>
 
const int BUF = 12312313;
char Buf[BUF], *buf = Buf;
 
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
 
const int _L = (1 << 19) - 1;
#define Max 200010
int root[Max * 20], c[Max], S;
inline int max (int a, int b) { return a > b ? a : b; }
class President_Tree
{
    private :
 
        int tree[Max * 30][2], size[Max * 30];
        int T_C;
 
    public :
        President_Tree () { T_C = 0; }
        void Change (int &now, int last, int l, int r, int key)
        {
            now = ++ T_C;
            memcpy (tree[now], tree[last], sizeof tree[now]);
            size[now] = size[last] + 1;
            if (l == r) return ;
            int Mid = l + r >> 1;
            if (key <= Mid)
                Change (tree[now][0], tree[last][0], l, Mid, key);
            else Change (tree[now][1], tree[last][1], Mid + 1, r, key);
        }
 
        int Query (int l, int r, int b, int x, int L, int R)
        {
            if (l == r) return b ^ l;
            int Mid = l + r >> 1; -- S;
            if (b & (1 << S))
            {
                if (Q (L, R , 0, _L, max (0, l - x), max (0, Mid - x)))
                    return Query (l, Mid, b, x, L, R);
                else return Query (Mid + 1, r, b, x, L, R);
            }
            else
            {
                if (Q (L, R, 0, _L, max (0, Mid + 1 - x), max (0, r - x)))
                    return Query (Mid + 1, r, b, x, L, R);
                else return Query (l, Mid, b, x, L, R);
            }
        }
 
        int Q (int L, int R, int x, int y, int l, int r)
        {
            if (x == l && y == r) return size[R] - size[L];
            int Mid = x + y >> 1;
            if (r <= Mid) 
                return Q (tree[L][0], tree[R][0], x, Mid, l, r);
            else if (l > Mid)
                return Q (tree[L][1], tree[R][1], Mid + 1, y, l, r);
            else
                return Q (tree[L][0], tree[R][0], x, Mid, l, Mid) + Q (tree[L][1], tree[R][1], Mid + 1, y, Mid + 1, r);
        }
};
President_Tree Tree;
 
int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N, M; register int i, j; read (N), read (M);
    int x, b, l, r;
    for (i = 1; i <= N; ++ i) 
        read (c[i]), Tree.Change (root[i], root[i - 1], 0, _L, c[i]);
     
    for (i = 1; i <= M; ++ i)
    {
        read (b), read (x), read (l), read (r); S = 19;
        printf ("%d\n", Tree.Query (0, _L, b, x, root[l - 1], root[r]));
    }
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
