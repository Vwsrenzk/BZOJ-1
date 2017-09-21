#include <iostream>
#include <cstdio>

#define Max 100090

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

struct S_D
{
    S_D *child[2];
    
    S_D *father;
    
    int size;
    int Flandre;
    int weigth;
    
    S_D ()
    {
        size = 1;    
        weigth = 0;
        
        Flandre = 0;
        father = NULL;
        child[0] = child[1] = NULL;    
    }
    
    inline void Up ()
    {
        size = weigth + 1;
        if (this->child[0])
            this->size += this->child[0]->size;
        if (this->child[1])
            this->size += this->child[1]->size;
        return ;
    }
    
    inline void Down ()
    {
        if (!Flandre)
            return ;
        std :: swap (child[0], child[1]);
        if (this->child[1])    
            this->child[1]->Flandre ^= 1;
        if (this->child[0])
            this->child[0]->Flandre ^= 1;
        this->Flandre = 0;
        return ;
    }
    
    inline int Get_Pos ()
    {
        return this->father->child[1] == this;
    }
    
    inline int Is_Root ()
    {
        return !(this->father) || (this->father->child[1] != this && this->father->child[0] != this);
    }
};

S_D *node[Max];
int N, M;

class Link_Cut_Tree_Type
{
    
    private :
        
        S_D *data[Max];
        
        inline void Rotate (S_D *now)
        {
            int pos = now->Get_Pos () ^ 1;
            S_D *Father = now->father;
            Father->child[pos ^ 1] = now->child[pos];
            if (now->child[pos])
                now->child[pos]->father = Father;
            now->father = Father->father;
            if (!Father->Is_Root ())
                now->father->child[Father->Get_Pos ()] = now;
            Father->father = now;
            now->child[pos] = Father;
            Father->Up ();
            now->Up ();
        }
        
        inline void Splay (S_D *now)
        {
            int pos = 0;
            for (S_D *Father = now; ; Father = Father->father)
            {
                data[++ pos] = Father;
                if (Father->Is_Root ())
                    break;
            }
            for (; pos >= 1; -- pos)
                data[pos]->Down ();
            for (; !now->Is_Root (); Rotate (now))
                if (!now->father->Is_Root ())
                    Rotate (now->Get_Pos () == now->father->Get_Pos () ? now->father : now);
            now->Up ();        
        }
    
        inline void Make_Root (S_D *now)
        {
            Access (now);
            Splay (now);
            now->Flandre ^= 1;
            return ;
        }
        
    public :

        inline void Access (S_D *now)
        {
            for (S_D *Pre = NULL; now; now->child[1] = Pre, Pre = now, now = now->father)
            {
                Splay (now);
                if (now->child[1] && !Pre)
                    now->weigth += now->child[1]->size;
                else if (!now->child[1] && Pre)
                    now->weigth -= Pre->size;
                else if (now->child[1] && Pre)
                    now->weigth += now->child[1]->size - Pre->size;
            }
        }
        
        inline void Link (S_D *x, S_D *y)
        {
            Make_Root (x);
            Access (y);
            Splay (y);
            x->father = y;
            y->weigth += x->size;
            return ;
        }
        
        inline int Query (S_D *x, S_D *y)
        {
            Make_Root (x);
            Access (y);
            return (x->weigth + 1) * (y->weigth + 1);
        }
};

Link_Cut_Tree_Type Lct;

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    for (int i = 1; i <= N; i ++)
        node[i] = new S_D ();
    char type[5];
    int x, y;
    for (; M --; )
    {
        scanf ("%s", type);
        read (x);
        read (y);
        if (type[0] == 'A')
            Lct.Link (node[x], node[y]);
        else
            printf ("%d\n", Lct.Query (node[x], node[y]));
    }
    return 0;
}
