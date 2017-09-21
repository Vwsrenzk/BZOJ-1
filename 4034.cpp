#include <cstdio>

#define Max 200190

void read (long long &now)
{
    now = 0;
    register char word = getchar ();
    bool flag = false;
    while (word < '0' || word > '9')
    {
        if (word == '-')
            flag = true;
        word = getchar ();
    }
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }    
    if (flag)
        now = -now; 
}

inline long long min (long long a, long long b)
{
    return a < b ? a : b;
}

inline long long max (long long a, long long b)
{
    return a > b ? a : b;
}

inline long long swap (long long &a, long long &b)
{
    long long now = a; 
    a = b;
    b = now;
}

long long tree_dis[Max];
long long Cur;

class Segment_Tree_Type
{
    private :
        
        struct Segment_Tree
        {
            long long l;
            long long r;
            long long Mid;
            long long Sum;
            long long Ruri;
        }
        tree[Max << 3];
        
    public :
        
        void Build (long long l, long long r, long long now)
        {
            tree[now].l = l;
            tree[now].r = r;
            if (l == r)
            {
                tree[now].Sum = tree_dis[++Cur];
                return ;
            }
            tree[now].Mid = (l + r) >> 1;
            Build (l, tree[now].Mid, now << 1);
            Build (tree[now].Mid + 1, r, now << 1 | 1);
            tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;
        }
        
        void Change_single (long long pos, long long now, long long to)
        {
            if (tree[now].l == tree[now].r)
            {
                tree[now].Sum += to;
                return ;
            }
            if (tree[now].Ruri)
            {
                tree[now << 1].Sum += (tree[now << 1].r - tree[now << 1].l + 1) * tree[now].Ruri;
                tree[now << 1].Ruri += tree[now].Ruri;
                tree[now << 1 | 1].Sum += (tree[now << 1 | 1].r - tree[now << 1 | 1].l + 1) * tree[now].Ruri;
                tree[now << 1 | 1].Ruri += tree[now].Ruri;
                tree[now].Ruri = 0;
            }
            if (pos <= tree[now].Mid)
                Change_single (pos, now << 1, to);
            else if (pos > tree[now].Mid)
                Change_single (pos, now << 1 | 1, to);
            tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;
        }
        
        void Change_section (long long l, long long r, long long now, long long to)
        {
            if (tree[now].l == l && tree[now].r == r)
            {
                tree[now].Sum += (tree[now].r - tree[now].l + 1) * to;
                tree[now].Ruri += to;
                return ;
            }
            if (tree[now].Ruri)
            {
                tree[now << 1].Sum += (tree[now << 1].r - tree[now << 1].l + 1) * tree[now].Ruri;
                tree[now << 1].Ruri += tree[now].Ruri;
                tree[now << 1 | 1].Sum += (tree[now << 1 | 1].r - tree[now << 1 | 1].l + 1) * tree[now].Ruri;
                tree[now << 1 | 1].Ruri += tree[now].Ruri;
                tree[now].Ruri = 0;
            }
            if (r <= tree[now].Mid)
                Change_section (l, r, now << 1, to);
            else if (l > tree[now].Mid)
                Change_section (l, r, now << 1 | 1, to);
            else 
            {
                Change_section (l, tree[now].Mid, now << 1, to);
                Change_section (tree[now].Mid + 1, r, now << 1 | 1, to);
            }
            tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;
        }
        
        long long Query_section (long long l, long long r, long long now)
        {
            if (tree[now].l == l && tree[now].r == r)
                return tree[now].Sum;
            if (tree[now].Ruri)
            {
                tree[now << 1].Sum += (tree[now << 1].r - tree[now << 1].l + 1) * tree[now].Ruri;
                tree[now << 1].Ruri += tree[now].Ruri;
                tree[now << 1 | 1].Sum += (tree[now << 1 | 1].r - tree[now << 1 | 1].l + 1) * tree[now].Ruri;
                tree[now << 1 | 1].Ruri += tree[now].Ruri;
                tree[now].Ruri = 0;
            }
            tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;
            if (r <= tree[now].Mid)
                return Query_section (l, r, now << 1);
            else if (l > tree[now].Mid)
                return Query_section (l, r, now << 1 | 1);
            else 
                return Query_section (l, tree[now].Mid, now << 1) + Query_section (tree[now].Mid + 1, r, now << 1 | 1); 
        }
};

Segment_Tree_Type Tree;

struct Graph_Type
{
    
    struct Edges
    {
        long long to;
        long long next;
    }
    
    edge[Max << 3];
    long long edge_list[Max];
    long long Edge_Count;
    
    inline void Add_Edge (long long from, long long to)
    {
        Edge_Count++;
        edge[Edge_Count].to = to;
        edge[Edge_Count].next = edge_list[from];
        edge_list[from] = Edge_Count;
        Edge_Count++;
        edge[Edge_Count].to = from;
        edge[Edge_Count].next = edge_list[to];
        edge_list[to] = Edge_Count;
    }
};

Graph_Type Graph;

class Tree_Chain_Get_Type 
{
    private :
        
        struct Point_Type
        {
            long long deep;
            long long size;
            long long father;
            long long up_chain_point;
            long long end;
            long long dis;
            long long tree_number;
        }
        
        point[Max];
    
        long long Count;
            
    public :
 
        inline void Clear ()
        {
             Count = 0;
        }
        
        void Dfs_1 (long long now, long long father)
        {
            point[now].father = father;
            point[now].deep = point[father].deep + 1;
            long long pos = Count++;
            for (long long i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
                if (Graph.edge[i].to != father)
                    Dfs_1 (Graph.edge[i].to, now);
            point[now].size = Count - pos;
        }
        
        void Dfs_2 (long long now, long long chain)
        {
            long long pos = 0;
            point[now].up_chain_point = chain;
            point[now].tree_number = ++Count;
            tree_dis[Count] = point[now].dis;
            for (long long i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
                if (!point[Graph.edge[i].to].tree_number && point[Graph.edge[i].to].size > point[pos].size)
                    pos = Graph.edge[i].to;
            if (!pos)
            {
                point[now].end = Count;
                return ;
            }
            Dfs_2 (pos, chain);
            for (long long i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
                if (Graph.edge[i].to != pos && !point[Graph.edge[i].to].tree_number)
                    Dfs_2 (Graph.edge[i].to, Graph.edge[i].to);
            point[now].end = Count;
        }
        
        long long Query_chain (long long x)
        {
            long long Answer = 0;
            while (point[x].up_chain_point)
            {
                Answer += Tree.Query_section (point[point[x].up_chain_point].tree_number, point[x].tree_number, 1);
                x = point[point[x].up_chain_point].father; 
            }
            return Answer;
        }
        
        long long Get_Point_number (long long now)
        {
            return point[now].tree_number;
        }
        
        void Key_in_point_dis (long long now, long long dis)
        {
            point[now].dis = dis;
        }
        
        long long Get_Point_End_number (long long now)
        {
            return point[now].end;
        }
};

Tree_Chain_Get_Type Make;

long long N, M;

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    long long x, y;
    for (long long i = 1; i <= N; i++)
    {
        read (x);
        Make.Key_in_point_dis (i, x); 
    }
    for (long long i = 1; i < N; i++)
    {
        read (x);
        read (y);
        Graph.Add_Edge (x, y); 
    }
    Make.Dfs_1 (1, 0);
    Make.Clear ();
    Make.Dfs_2 (1, 1);
    Tree.Build (1, N, 1);
    while (M--)
    {
        read (x);
        if (x == 1)
        {
            read (x);
            read (y);
            Tree.Change_single (Make.Get_Point_number (x), 1, y);  
        }
        else if (x == 2)
        {
            read (x);
            read (y);
            Tree.Change_section (Make.Get_Point_number (x), Make.Get_Point_End_number (x), 1, y); 
        }
        else 
        {
            read (x);
            printf ("%lld\n", Make.Query_chain (x));
        }
    }
    return 0;
}
