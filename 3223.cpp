#include <cstdio>
 
#define Max 200009
 
inline int swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}
 
inline void read (int &now)
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
 
int value[Max];
int N, M;
 
class Splay_Tree_Type
{
    private :
         
        struct Splay_Tree_Date
        {
            int size;
            int key;
            int father;
            int child[2];
            int Flandre;
        }
        tree[Max]; 
         
        inline int Get_Son (int now)
        {
            return tree[tree[now].father].child[1] == now;
        }
         
        inline void Update (int now)
        {
            tree[now].size = 1;
            if (tree[now].child[0])
                tree[now].size += tree[tree[now].child[0]].size;
            if (tree[now].child[1])
                tree[now].size += tree[tree[now].child[1]].size;
        }
         
        int Root;
        int Answer[Max];
        int Count;
         
        inline void Down (int now)
        {
            tree[now].Flandre = 0;
            swap (tree[now].child[0], tree[now].child[1]);
            if (tree[now].child[0])
                tree[tree[now].child[0]].Flandre ^= 1;
            if (tree[now].child[1])
                tree[tree[now].child[1]].Flandre ^= 1;
        }
         
        inline void Rotate (int now)
        {
            int father = tree[now].father;
            int Grand = tree[father].father;
            int pos = Get_Son (now);
            if (tree[father].Flandre && father)
                Down (father);
            if (tree[now].Flandre && now)
                Down (now);
            tree[father].child[pos] = tree[now].child[pos ^ 1];
            tree[tree[father].child[pos]].father = father;
            tree[now].child[pos ^ 1] =  father;
            tree[father].father = now;
            tree[now].father = Grand;
            if (Grand)
                tree[Grand].child[tree[Grand].child[1] == father] = now;
            Update (father);
            Update (now);
        }
         
        void Get_Answer (int now)
        {
            if (tree[now].Flandre)
                Down (now);
            if (tree[now].child[0])
                Get_Answer (tree[now].child[0]);
            Answer[++Count] = tree[now].key;
            if (tree[now].child[1])
                Get_Answer (tree[now].child[1]);
        }
         
        int Build (int l, int r, int father)
        {
            int now = l + r >> 1;
            tree[now].father = father;
            tree[now].key = value[now];
            if (now > l)
                tree[now].child[0] = Build (l, now - 1, now);
            if (now < r)
                tree[now].child[1] = Build (now + 1, r, now);
            Update (now);
            return now;
        }
         
    public :
         
        void Prepare ()
        {
            Root = 1;
            Root = Build(1, N + 2, 0);
        }
         
        void Splay (int now, int to)
        {
            for (int father; (father = tree[now].father) != to; Rotate (now))
                if (tree[father].father != to)
                    Rotate (Get_Son (now) == Get_Son (father) ? father : now);
            if (!to)
                Root = now;
        }
         
        int Get_Pos (int x)
        {
            int now = Root;
            for (; ; )
            {
                if (tree[now].Flandre)
                    Down (now);
                if (x <= tree[tree[now].child[0]].size)
                    now = tree[now].child[0];
                else
                {
                    x -= tree[tree[now].child[0]].size + 1;
                    if (!x)
                        return now;
                    now = tree[now].child[1];
                }
            }
        }
         
        inline void Print ()
        {
            Get_Answer (Root);
            for (int i = 1; i <= N; i++)
                printf ("%d ", Answer[i + 1]);
        }
             
        inline void Hit_flag ()
        {
            tree[tree[tree[Root].child[1]].child[0]].Flandre ^= 1;
        }
};
 
Splay_Tree_Type Make;
 
int main (int argc, char *argv[])
{
    read (N);
    read (M); 
    for (int i = 1; i <= N + 2; i++)
        value[i] = i - 1;
    int l, r;
    Make.Prepare ();
    for (; M--; )
    {
        read (l);
        read (r);
        r += 2;
        l = Make.Get_Pos (l);
        r = Make.Get_Pos (r);   
        Make.Splay (l, 0);
        Make.Splay (r, l); 
        Make.Hit_flag ();
    }
    Make.Print (); 
    return 0;
}
