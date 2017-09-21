#include <cstdio>
#include <cstdlib>
#include <iostream>

#define Max 400009

int N;

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
    Splay_Tree_Data *child[2];
    Splay_Tree_Data *father;

    int Flandre;

    Splay_Tree_Data ()
    {
        Flandre = 0;
        father = NULL;
        child[0] = child[1] = NULL;
    }

    inline void Down ()
    {
        if (!Flandre)
            return ;
        std :: swap (child[0], child[1]);
        Flandre = 0;
        if (child[0])
            child[0]->Flandre ^= 1;
        if (child[1])
            child[1]->Flandre ^= 1;
    }

    inline int Get_Pos ()
    {
        return this->father->child[1] == this;
    }

    inline int Is_Root ()
    {
        return !(this->father) || (this->father->child[0] != this && this->father->child[1] != this);
    }
};

Splay_Tree_Data *data[Max];
Splay_Tree_Data *node[Max];

class Link_Cut_Tree_Type
{
    private :
        
        inline void Rotate (Splay_Tree_Data *now)
        {
            int pos = now->Get_Pos () ^ 1;
            Splay_Tree_Data *Father = now->father;
            Father->child[pos ^ 1] = now->child[pos];
            if (now->child[pos])
                now->child[pos]->father = Father;
            now->father = Father->father;
            if (!(Father->Is_Root ()))
                now->father->child[Father->Get_Pos ()] = now;
            Father->father = now;
            now->child[pos] = Father;
        }

        inline void Splay (Splay_Tree_Data *now)
        {
            int Count = 0;
            for (Splay_Tree_Data *Father = now; ; Father = Father->father)
            {
                data[++Count] = Father;
                 if (Father->Is_Root ())
                    break;
            }
            for (; Count >= 1; -- Count)
                data[Count]->Down ();
            for (; !(now->Is_Root ()); Rotate (now))
                if (!(now->father->Is_Root ()))
                    Rotate (now->Get_Pos () == now->father->Get_Pos () ? now->father : now);
        }

        inline void Access (Splay_Tree_Data *now)
        {
            for (Splay_Tree_Data *Father = NULL; now; Father = now, now = now->father)
            {
                Splay (now);
                now->child[1] = Father;
            }
        }

        inline void Make_Root (Splay_Tree_Data *now)
        {
            Access (now);
            Splay (now);
            now->Flandre ^= 1;
        }


    public :

        inline void Cut (Splay_Tree_Data *x, Splay_Tree_Data *y)
        {
            Make_Root (x);
            Access (y);
            Splay (y);
            x->father = y->child[0] = NULL;
        }

        inline void Link (Splay_Tree_Data *x, Splay_Tree_Data *y)
        {
            Make_Root (x);
            x->father = y;
        }
        
        int Query (Splay_Tree_Data *x, Splay_Tree_Data *y)
        {
            while (x->father)
                x = x->father;
            while (y->father)
                y = y->father;
            return x == y;
        }
};

Link_Cut_Tree_Type Make;

int main (int argc, char *argv[])
{
    read (N);
    
    char type[10];
    int x, y;
    int M;
    for (int i = 0; i <= N; i ++)
        node[i] = new Splay_Tree_Data;
    for (read (M); M--; )
    {
        scanf ("%s", type);
        read (x);
        read (y);
        if (type[0] == 'Q')
            printf (Make.Query (node[x], node[y]) ? "Yes\n" : "No\n");
        else if (type[0] == 'C')
            Make.Link (node[x], node[y]);
        else 
            Make.Cut (node[x], node[y]); 
    }
    return 0;
}
