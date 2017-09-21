#include <cstdio>

#define Max 500090

inline int min (int a, int b)
{
    return a < b ? a : b;
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}

inline int swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}

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

struct Edge_Type
{
    struct Edge
    {
        int to;
        int next;
    };
    
    Edge edge[Max << 2];
    
    int Edge_Count;
    int edge_list[Max];
    
    void Add_Edge (int from, int to)
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

Edge_Type Graph;

struct Segment_Tree_Type
{
    
    struct Segment_Tree
    {
        int l;
        int r;
        int Mid;
        int Sum;
        int Ruri;
    };
    
    Segment_Tree tree[Max << 3];
    
    void Build (int l, int r, int now)
    {
        tree[now].l = l;
        tree[now].r = r;
        if (l == r)
            return ;
        tree[now].Mid = (l + r) >> 1;
        Build (l, tree[now].Mid, now << 1);
        Build (tree[now].Mid + 1, r, now << 1 | 1);
    }
    
    int Query_Section_Sum (int l, int r, int now)
    {
        if (tree[now].l == l && tree[now].r == r)
            return tree[now].Sum;
        if (tree[now].Ruri == 1)
        {
            tree[now << 1].Sum = tree[now << 1].r - tree[now << 1].l + 1;
            tree[now << 1].Ruri = 1;
            tree[now << 1 | 1].Sum = tree[now << 1 | 1].r - tree[now << 1 | 1].l + 1;
            tree[now << 1 | 1].Ruri = 1;
            tree[now].Ruri = 0;
        }
        else if (tree[now].Ruri == 2)
        {
            tree[now << 1].Sum = 0;
            tree[now << 1 | 1].Sum = 0;
            tree[now << 1].Ruri = 2;
            tree[now << 1 | 1].Ruri = 2;
            tree[now].Ruri = 0;
        }
        tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;    
        if (r <= tree[now].Mid)
            return Query_Section_Sum (l, r, now << 1);
        else if (l > tree[now].Mid)
            return Query_Section_Sum (l, r, now << 1 | 1);
        else 
            return Query_Section_Sum (l, tree[now].Mid, now << 1) + Query_Section_Sum (tree[now].Mid + 1, r, now << 1 | 1);
    }
    
    void Change_Section (int l, int r, int now, int to)
    {
        if (tree[now].l == l && tree[now].r == r)
        {
            if (to == 1)
            {
                tree[now].Sum = tree[now].r - tree[now].l + 1;
                tree[now].Ruri = 1;
                return ;
            }
            else if (to == 2)
            {
                tree[now].Sum = 0;
                tree[now].Ruri = 2;
                return ;
            }
        }
        if (tree[now].Ruri == 1)
        {
            tree[now << 1].Sum = tree[now << 1].r - tree[now << 1].l + 1;
            tree[now << 1].Ruri = 1;
            tree[now << 1 | 1].Sum = tree[now << 1 | 1].r - tree[now << 1 | 1].l + 1;
            tree[now << 1 | 1].Ruri = 1;
            tree[now].Ruri = 0;
        }
        else if (tree[now].Ruri == 2)
        {
            tree[now << 1].Sum = 0;
            tree[now << 1 | 1].Sum = 0;
            tree[now << 1].Ruri = 2;
            tree[now << 1 | 1].Ruri = 2;
            tree[now].Ruri = 0;
        }
        if (r <= tree[now].Mid)
            Change_Section (l, r, now << 1, to);
        else if (l > tree[now].Mid)
            Change_Section (l, r, now << 1 | 1, to);
        else
        {
            Change_Section (l, tree[now].Mid, now << 1, to);
            Change_Section (tree[now].Mid + 1, r, now << 1 | 1, to); 
        }
        tree[now].Sum = tree[now << 1].Sum + tree[now << 1 | 1].Sum;
    }
    
};

Segment_Tree_Type Tree;

struct Tree_Chain_Get_Type
{
    
    struct Point_Type
    {
        int size;
        int deep;
        int father;
        int chain_up_point;
        int tree_number;
        int end;
    };
    
    Point_Type point[Max];
    
    int Count;
    
    void Dfs_1 (int now, int father)
    {
        int pos = Count++;
        point[now].deep = point[father].deep + 1;
        point[now].father = father;
        for (int i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
            if (Graph.edge[i].to != father)
                Dfs_1 (Graph.edge[i].to, now);
        point[now].size = Count - pos;
    }
    
    void Dfs_2 (int now, int chain)
    {
        int pos = 0;
        point[now].chain_up_point = chain;
        point[now].tree_number = ++Count;
        for (int i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
            if (!point[Graph.edge[i].to].tree_number && point[Graph.edge[i].to].size > point[pos].size)
                pos = Graph.edge[i].to;
        if (pos)
            Dfs_2 (pos, chain);
        for (int i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
            if (!point[Graph.edge[i].to].tree_number)
                Dfs_2 (Graph.edge[i].to, Graph.edge[i].to);
        point[now].end = Count;    
    }
    
    void Chain_Change (int x, int y, int type)
    {
        while (point[x].chain_up_point != point[y].chain_up_point)
        {
            if (point[point[x].chain_up_point].deep < point[point[y].chain_up_point].deep)
                swap (x, y);
            Tree.Change_Section (point[point[x].chain_up_point].tree_number, point[x].tree_number, 1, type); 
            x = point[point[x].chain_up_point].father;
        }
        Tree.Change_Section (min (point[x].tree_number, point[y].tree_number), max (point[x].tree_number, point[y].tree_number), 1, type);
        return ; 
    }
    
    int Chain_Query (int x, int y)
    {
        int Answer = 0;
        while (point[x].chain_up_point != point[y].chain_up_point)
        {
            if (point[point[x].chain_up_point].deep < point[point[y].chain_up_point].deep)
                swap (x, y);
            Answer += Tree.Query_Section_Sum (point[point[x].chain_up_point].tree_number ,point[x].tree_number, 1); 
            x = point[point[x].chain_up_point].father;
        }
        Answer += Tree.Query_Section_Sum (min (point[x].tree_number, point[y].tree_number), max (point[x].tree_number, point[y].tree_number), 1);
        return Answer; 
    }
};

Tree_Chain_Get_Type Make;

int N, M;

int main (int argc, char *argv[])
{
    read (N);
    int x;
    for (int i = 2; i <= N; i++)
    {
        read (x);
        x++;
        Graph.Add_Edge (i, x);
    }
    Make.Dfs_1 (1, 0);
    Make.Count = 0;
    Make.Dfs_2 (1, 1);
    Tree.Build (1, N, 1);
    read (N);
    char type[10];
    int now;
    while (N--)
    {
        scanf ("%s", type);
        read (x);
        x++;
        if (type[0] == 'i')
        {
            now = Make.Chain_Query (1, x); 
            Make.Chain_Change (1, x, 1); 
            printf ("%d\n", Make.point[x].deep - now);
        }
        else
        {
            now = Tree.Query_Section_Sum (Make.point[x].tree_number, Make.point[x].end, 1);
            Tree.Change_Section (Make.point[x].tree_number, Make.point[x].end, 1, 2);
            printf ("%d\n", now);
        }
    }
    return 0;
}
