#include <cstdio>

#define Max 50000
#define INF 1e8

namespace Z
{
    inline int min (int a, int b)
    {
        return a < b ? a : b;
    }
    
    inline int abs (int x)
    {
        return x > 0 ? x : -x;
    }
    
    void read (int &now)
    {
        now = 0;
        register char word = getchar ();
        bool temp = false;
        while (word < '0' || word > '9')
        {
            if (word == '-')
                temp = true;
            word = getchar ();
        }
        while (word >= '0' && word <= '9')
        {
            now = now * 10 + word - '0';
            word = getchar ();
        }
        if (temp)
            now = -now;
    }
}


class Splay_Tree_Type
{
    private :
        
        struct Splay_Tree_Date
        {
            int key;
            int weigth;
            int size;
            int father;
            int child[2];
        }
        tree[Max];
        
        int Count;
        int Root;
        
        inline int Get_Son (int now)
        {
            return tree[tree[now].father].child[1] == now;
        }
        
        inline void Rotate (int now)
        {
            int father = tree[now].father;
            int Grand = tree[father].father;
            int pos = Get_Son (now);
            tree[father].child[pos] = tree[now].child[pos ^ 1];
            tree[tree[father].child[pos]].father = father;
            tree[now].child[pos ^ 1] = father;
            tree[father].father = now;
            tree[now].father = Grand;
            if (Grand)
                tree[Grand].child[tree[Grand].child[1] == father] = now;
            Update (father);
            Update (now);
        }
        
        inline void Update (int now)
        {
            tree[now].size = tree[now].weigth;
            if (tree[now].child[0])
                tree[now].size += tree[tree[now].child[0]].size;
            if (tree[now].child[1])
                tree[now].size += tree[tree[now].child[1]].size;
        }
        
        inline void Splay (int now)
        {
            for (int father; father = tree[now].father; Rotate (now))
                if (tree[father].father)
                    Rotate (Get_Son (now) == Get_Son (father) ? father : now);
            Root = now;
        }
        
    public :
        
        void Insert (int x)
        {
            if (!Root)
            {
                Count++;
                tree[Count].key = x;
                tree[Count].size = 1;
                tree[Count].weigth = 1;
                Root = Count;
                return ;
            }
            int now = Root, father = 0;
            while (true)
            {
                if (tree[now].key == x)
                {
                    tree[now].size++;
                    tree[now].weigth++;
                    Splay (now);
                    return ;
                }
                father = now;
                now = tree[now].child[x > tree[now].key];
                if (!now)
                {
                    Count++;
                    tree[father].child[x > tree[father].key] = Count; 
                    tree[Count].key = x;
                    tree[Count].father = father;
                    tree[Count].size = 1;
                    tree[Count].weigth = 1;
                    Splay (Count);
                    return ;
                }
            }
        }
        
        int Get_Prefix ()
        {
            if (tree[Root].weigth > 1)
                return tree[Root].key;
            int now = tree[Root].child[0];
            if (now == 0)
                return INF;
            while (tree[now].child[1])
                now = tree[now].child[1];                
            return tree[now].key;
        }
        
        int Get_Suffix ()
        {
            if (tree[Root].weigth > 1)
                return tree[Root].key;
            int now = tree[Root].child[1];
            if (now == 0)
                return INF;
            while (tree[now].child[0])
                now = tree[now].child[0];
            return tree[now].key;
        }
};

Splay_Tree_Type Make;

int N;

int main (int argc, char *argv[])
{
    Z :: read (N);
    int x;
    int Prefix, Suffix;
    Z :: read (x);
    Make.Insert (x);
    int Answer =  Z :: abs (x);
    for (int i = 1; i < N; i++)
    {
        if (scanf ("%d", &x) == EOF)
            x = 0;
        Make.Insert (x);
        Prefix = Make.Get_Prefix ();
        Suffix = Make.Get_Suffix ();
        Answer += Z :: min (Z :: abs (x - Prefix), Z :: abs (x - Suffix));
    }
    printf ("%d", Answer);
    return 0;
}
