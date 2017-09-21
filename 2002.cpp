#include <cstdio>
#include <cstdlib>

#define Max 200010

void read (int &now)
{
    now = 0;
    register char word = getchar ();
    while (word < '0' || word > '9')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}

inline int min (int a, int b)
{
    return a < b ? a : b;
}

struct Splay_Tree_Data 
{
    int child[2];
    int father;

    int size;
    int Flandre;

};

int N;

int next[Max];
Splay_Tree_Data tree[Max];
int data[Max];

inline int swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}

class Link_Cut_Tree_Type
{

    private :

        inline void Updata (int now)
        {
            tree[now].size = 1;
            tree[now].size += tree[tree[now].child[0]].size;
            tree[now].size += tree[tree[now].child[1]].size;
        }

        inline void Down (int now)
        {
            if (!tree[now].Flandre)
                return ;
            tree[now].Flandre ^= 1;
            tree[tree[now].child[0]].Flandre ^= 1;
            tree[tree[now].child[1]].Flandre ^= 1;
            swap (tree[now].child[0], tree[now].child[1]);
        }

        bool Is_Root (int now)
        {
            return tree[tree[now].father].child[0] != now && tree[tree[now].father].child[1] != now;
        }

        inline int Get_Pos (int now)
        {
            return tree[tree[now].father].child[1] == now;
        }

        inline void Rotate (int now)
        {
            int father = tree[now].father;
            int Grand = tree[father].father;
            int l, r = 0;
            l = tree[father].child[0] == now ? 0 : 1;
            r = l ^ 1;
            if (!Is_Root (father))
                tree[Grand].child[tree[Grand].child[0] != father] = now;
            tree[father].child[l] = tree[now].child[r];
            tree[now].child[r] = father;
            tree[father].father = now;
            tree[tree[father].child[l]].father = father;
            tree[now].father = Grand;
            Updata (father);
        }
        
        inline void Splay (int now)
        {
            int Count = 0;
            data[++Count] = now;
            for (int i = now; !Is_Root (i); i = tree[i].father)
                data[++Count] = tree[i].father;
            for (int i = Count; i; i --)
                Down (data[i]);
            while (!Is_Root (now))
            {
                int father = tree[now].father;
                int Grand = tree[father].father;
                if (!Is_Root (father))
                {
                    if (tree[father].child[0] == now ^ tree[Grand].child[0] == father)
                        Rotate (now);
                    else
                        Rotate (father);
                }
                Rotate (now);
                Updata (now);
            }
        }

        inline void Access (int now)
        {
            int pos = 0;
            while (now)
            {
                Splay (now);
                tree[now].child[1] = pos;
                pos = now;
                now = tree[now].father;
            }
        }

        inline void Make_Root (int now)
        {
            Access (now);
            Splay (now);
            tree[now].Flandre ^= 1;
        }

        inline void Link (int x, int y)
        {
            Make_Root (x);
            tree[x].father = y;
            Splay (x);
        }

        inline void Cut (int x, int y)
        {
            Make_Root (y);
            Access (x);
            Splay (x);
            tree[x].child[0] = 0;
            tree[y].father = 0;
        }

    public :

        inline void Do_First (int x)
        {
            Make_Root (N + 1);
            x ++;
            Access (x);
            Splay (x);
            printf ("%d\n", tree[tree[x].child[0]].size);
        }

        inline void Do_Second (int x, int y)
        {
            x ++;
            int now = min (N + 1, x + y);
            Cut (x, next[x]);
            Link (x, now);
            next[x] = now;
        }
};

Link_Cut_Tree_Type Make;
int M;

int main (int argc, char *argv[])
{
    read (N);
    int x;
    for (int i = 1; i <= N; i ++)
    {
        read (x);
        tree[i].father = x + i;
        tree[i].size = 1;
        if (tree[i].father > N + 1)
            tree[i].father = N + 1;
        next[i] = tree[i].father;
    }

    tree[N + 1].size = 1;
    read (M);
    for (int x, y, type, i = 1; i <= M; i ++)
    {
        read (type);
        read (x);
        if (type == 1)
            Make.Do_First (x);
        else
        {
            read (y);
            Make.Do_Second (x, y);
        }
    }
    return 0;
}
