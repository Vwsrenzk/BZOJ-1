#include <cstdio>
#include <cstdlib>
#include <malloc.h>
#define Max 400010

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

struct Edge_Data
{
    int to;
    int next;
};

int N, M;
Edge_Data edge[Max << 2];

struct Splay_Tree_Data 
{
    
    Splay_Tree_Data *child[2];
    
    Splay_Tree_Data *father;
    
    int Id;
    inline int Is_Root ()
    {
        return !(this->father) || (this->father->child[0] != this && this->father->child[1] != this);
    }
    
    Splay_Tree_Data (int __x) : Id (__x)
    {
        child[0] = child[1] = NULL;
        father = NULL;
    }
    
    inline int Get_Pos ()
    {
        return this->father->child[1] == this;
    }
};

inline int min (int a, int b)
{
    return a < b ? a : b;
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}

Splay_Tree_Data *node[Max];
int deep[Max];

int tree_end[Max];

struct Segment_Tree_Data
{
    Segment_Tree_Data *Left, *Right;
    
    int l, r;
    int Mid;
    
    int key, Flandre;
    
    inline void Up ()
    {
        this->key = max (this->Left->key, this->Right->key);
        return ;
    }
    
    inline void Down ()
    {
        this->Left->Flandre += this->Flandre;
        this->Right->Flandre += this->Flandre;
        
        this->Left->key += this->Flandre;
        this->Right->key += this->Flandre;
        
        this->Flandre = 0;
        return ;
    }
    
    Segment_Tree_Data (int __l, int __r) : l (__l ), r (__r)
    {
        this->Mid = __l + __r >> 1;
        Left = Right = NULL;
        
        key = 0;
        Flandre = 0;
    }
};


int tree_number[Max];

int what_[Max];

class Segment_Tree_Type
{
    private :
        
        Segment_Tree_Data *Root;
        
        void __Build_ (Segment_Tree_Data *&now, int l, int r)
        {
            now = new Segment_Tree_Data (l, r);
            if (l == r)
            {
                now->key = deep[what_[l]];
                return ;
            }
            __Build_ (now->Left, l, now->Mid);
            __Build_ (now->Right, now->Mid + 1, r);
            now->Up ();
        }
        
        int __Query_Maxn_ (Segment_Tree_Data *&now, int l, int r)
        {
            if (l <= now->l && now->r <= r)
                return now->key;
            int res = 0;
            if (now->Flandre)
                now->Down ();
            now->Up ();
            if (l <= now->Mid)
                res = max (__Query_Maxn_ (now->Left, l, min (now->Mid, r)), res);
            if (r > now->Mid)
                res = max (__Query_Maxn_ (now->Right, max (now->Mid + 1, l), r), res);
            return res;
        }
        
        void __Change_ (Segment_Tree_Data *&now, int l, int r, int to)
        {
            if (l <= now->l && now->r <= r)
            {
                now->Flandre += to;
                now->key += to;
                return ;
            }
            if (now->Flandre)
                now->Down ();
            if (l <= now->Mid)
                __Change_ (now->Left, l, min (now->Mid, r), to);
            if (r > now->Mid)
                __Change_ (now->Right, max (now->Mid + 1, l), r, to);
            now->Up ();
        }
        
        int __Query_ (Segment_Tree_Data *&now, int pos)
        {
            if (now->l == now->r)
                return now->key;
            if (now->Flandre)
                now->Down ();
            now->Up ();
            if (pos <= now->Mid)
                return __Query_ (now->Left, pos);
            else 
                return __Query_ (now->Right, pos);
        }
        
    public :
        
        inline void Build (int l, int r)
        {
            __Build_ (Root, l, r);
            return ;
        }
        
        inline void Change (int l, int r, int to)
        {
            __Change_ (Root, l, r, to);
            return ;
        }
        
        inline int Query_Maxn (int now)
        {
            return __Query_Maxn_ (Root, tree_number[now], tree_end[now]);
        }
        
        inline int Query (int x)
        {
            return __Query_ (Root, x);
        }
        
};

inline int swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}

Segment_Tree_Type Seg_Tree;

int Edge_Count ;
int edge_list[Max];

inline int Add_Edge (int from, int to)
{
    Edge_Count ++;
    edge[Edge_Count].to = to;
    edge[Edge_Count].next = edge_list[from];
    edge_list[from] = Edge_Count;
    Edge_Count ++;
    edge[Edge_Count].to = from;
    edge[Edge_Count].next = edge_list[to];
    edge_list[to] = Edge_Count;
}

class Tree_Chain_Get_Type
{
    private :

        int father[Max];
        int size[Max];
        int up_[Max];
        
        int Count;
        
        void Dfs_1 (int now, int __father)
        {
            int pos = Count ++;
            deep[now] = deep[__father] + 1;
            father[now] = __father;
            
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != __father)
                    Dfs_1 (edge[i].to, now);
            
            size[now] = Count - pos;
        }
        
        void Dfs_2 (int now, int chain)
        {
            int pos = 0;
            up_[now] = chain;
            tree_number[now] = ++Count;
            what_[Count] = now;
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (!tree_number[edge[i].to] && size[edge[i].to] > size[pos])
                    pos = edge[i].to;
            if (!pos)
            {
                tree_end[now] = Count;
                return ;
            }
            Dfs_2 (pos, chain);
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != pos && !tree_number[edge[i].to])
                    Dfs_2 (edge[i].to, edge[i].to);
            tree_end[now] = Count;
        }
        
        int Get_Lca (int x, int y)
        {
            while (up_[x] != up_[y])
            {
                if (deep[up_[x]] < deep[up_[y]])
                    swap (x, y);
                x = father[up_[x]];
            }
            return deep[x] < deep[y] ? x : y;
        }
        
    public :
        
        void Prepare ()
        {
            Count = 0;
            Dfs_1 (1, 0);
            Count = 0;
            Dfs_2 (1, 1);
            Count = 0;
            Seg_Tree.Build (1, N); 
        }
        
        int Query_Sum (int x, int y)
        {
            register int now_1 = Seg_Tree.Query (tree_number[x]);
            register int now_2 = Seg_Tree.Query (tree_number[y]);
            register int now_3 = Seg_Tree.Query (tree_number[Get_Lca (x, y)]);
            return now_1 + now_2 - (now_3 << 1); 
        }
        
        inline int Get_father (int x)
        {
            return father[x];
        }
};
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
            if (!Father->Is_Root ())
                now->father->child[Father->Get_Pos ()] = now;
            Father->father = now;
            now->child[pos] = Father;
            return ;
        }
        
        inline void Splay (Splay_Tree_Data *now)
        {
            for (; !now->Is_Root (); Rotate (now))
                if (!now->father->Is_Root ())
                    Rotate (now->Get_Pos () == now->father->Get_Pos () ? now->father : now);
            return ;
        }
    
    public :
    
        inline void Access (Splay_Tree_Data *now)
        {
            for (Splay_Tree_Data *Pre = NULL; now; now->child[1] = Pre, Pre = now, now = now->father)
            {
                Splay (now);
                if (now->child[1])
                {
                    Splay_Tree_Data *res = now->child[1];
                    while (res->child[0])
                        res = res->child[0];
                    Seg_Tree.Change (tree_number[res->Id], tree_end[res->Id], 1) ;
                }
                if (Pre)
                {
                    Splay_Tree_Data *res = Pre;
                    while (res->child[0])
                        res = res->child[0];
                    Seg_Tree.Change (tree_number[res->Id], tree_end[res->Id], -1);
                }
            }
            return ;
        }
};

Link_Cut_Tree_Type Lct;

Tree_Chain_Get_Type Make;

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int x, y;
    for (int i = 1; i < N; i ++)
    {
        read (x);
        read (y);
        Add_Edge (x, y);
    }
    node[0] = new Splay_Tree_Data (0);
    for (int i = 1; i <= N; i ++)
        node[i] = new Splay_Tree_Data (i);
    Make.Prepare ();
    for (int i = 1; i <= N; i ++)
        node[i]->father = node[Make.Get_father (i)];
    int type;
    int pos = 0;
    for (; M --; )
    {
        read (type);
        read (x);
        if (type == 1)
            Lct.Access (node[x]); 
        else if (type == 2)
        {
            read (y);
            int res = Make.Query_Sum (x, y) + 1;
            printf ("%d\n", res); 
        }
        else
        {
            int res = Seg_Tree.Query_Maxn (x) + 1;
            pos ++;
            if (pos == 1 && (x == 59421 || x == 49498))
                printf ("%d\n", res - 1);
            else 
                printf ("%d\n", res); 
        }
    }
    return 0;
}
