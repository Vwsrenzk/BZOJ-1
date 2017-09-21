#include <cstdio>
 
#define Max  200000
 
void read (long long &now)
{
    now = 0;
    register char word = getchar ();
    while (word > '9' || word < '0')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}
         
inline long long max (long long a, long long b)
{
    return a > b ? a : b;
}
 
long long N;
long long Mod;
 
struct Segment
{
    struct Segment_Tree
    {
        long long l;
        long long r;
        long long Mid;
        long long Maxn;
         
    };
     
    Segment_Tree tree[Max << 3];
     
    void Tree_Build (long long l, long long r, long long now)
    {
        tree[now].l = l;
        tree[now].r = r;
        if (l == r)
            return ;
        tree[now].Mid = (l + r) >> 1;
        Tree_Build (l, tree[now].Mid, now << 1);
        Tree_Build (tree[now].Mid + 1, r, now << 1 | 1);  
    }
     
    void Tree_Insert (long long pos, long long now, long long number)
    {
        if (tree[now].l == tree[now].r)
        {
            tree[now].Maxn = number;
            return ;
        }
        if (pos <= tree[now].Mid)
            Tree_Insert (pos, now << 1, number);
        else
            Tree_Insert (pos, now << 1 | 1, number);
        tree[now].Maxn = max (tree[now << 1].Maxn, tree[now << 1 | 1].Maxn);
    }
     
    long long Tree_Query (long long l, long long r, long long now)
    {
        if (tree[now].l == l && tree[now].r == r)
            return tree[now].Maxn;
        if (r <= tree[now].Mid)
            return Tree_Query (l, r, now << 1);
        else if (l > tree[now].Mid)
            return Tree_Query (l, r, now << 1 | 1);
        else
            return max (Tree_Query (l, tree[now].Mid, now << 1), Tree_Query (tree[now].Mid + 1, r, now << 1 | 1));
    }
     
};
 
Segment Tree;
 
long long Tree_Pos;
 
int main (int argc, char *argv[])
{
    read (N);
    read (Mod);
    Tree_Pos = 0;
    Tree.Tree_Build (1, N, 1);
    char type[5];
    long long x;
    long long t = 0;
    while (N--)
    {
        scanf ("%s", type);
        read (x);
        if (type[0] == 'Q')
        {
            t = Tree.Tree_Query (Tree_Pos - x + 1, Tree_Pos, 1);
            printf ("%lld\n", t);
        }
        else
            Tree.Tree_Insert (++Tree_Pos, 1, (x + t) % Mod); 
    }
    return 0;
}
