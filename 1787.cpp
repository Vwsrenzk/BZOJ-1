#include <cstdio>

#define Max 500097

inline int abs (int a)
{
    return a > 0 ? a : -a;
}

inline void swap (int &a, int &b)
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

class Tree_Chain_Lca_Type
{
    private :
        
        struct Points 
        {
            int size;
            int father;
            int up_chain_point;
            int deep;
        }
        
        point[Max];
        
        int Count;
        
        struct Edges 
        {
            int to;
            int next;
        }
        edge[Max << 2];
        
        int Edge_Count;
        int edge_list[Max];
        
    public :
        
        inline void AddEdge (int from, int to)
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
        
        void Dfs_1 (int now, int father)
        {
            int pos = Count++;
            point[now].father = father;
            point[now].deep = point[father].deep + 1;
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != father)
                    Dfs_1 (edge[i].to, now);
            point[now].size = Count - pos;
        }
        
        void Dfs_2 (int now, int chain)
        {
            point[now].up_chain_point = chain;
            int pos = 0;
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != point[now].father && point[edge[i].to].size > point[pos].size)
                    pos = edge[i].to;
            if (!pos)
                return;
            Dfs_2 (pos, chain);
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != pos && edge[i].to != point[now].father)
                    Dfs_2 (edge[i].to, edge[i].to);
        }
        
        int Get_Lca (int x, int y)
        {
            while (point[x].up_chain_point != point[y].up_chain_point)
            {
                if (point[point[x].up_chain_point].deep < point[point[y].up_chain_point].deep)
                    swap (x, y);
                x = point[point[x].up_chain_point].father;
            }
            return point[x].deep < point[y].deep ? x : y;
        }
        
        int Get_dis (int x, int y)
        {
            int now = Get_Lca (x, y);
            return point[x].deep + point[y].deep - (point[now].deep << 1);
        }
        
        void Clear ()
        {
            Dfs_1 (1, 0);
            Count = 0;
            Dfs_2 (1, 1);
        }
};

Tree_Chain_Lca_Type Make;

int N, M;

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int x, y, z;
    for (int i = 1; i < N; i++)
    {
        read (x);
        read (y);
        Make.AddEdge (x, y); 
    }
    Make.Clear ();  
    int now_1, now_2, now_3;
    int Answer, now;
    while (M--)
    {
        read (x);
        read (y);
        read (z);
        now_1 = Make.Get_Lca (x, y);
        now_2 = Make.Get_Lca (x, z);
        now_3 = Make.Get_Lca (y, z);   
        if (now_1 == now_2)
            now = now_3;
        else if (now_1 == now_3)
            now = now_2;
        else
            now = now_1;
        printf ("%d %d\n", now, Make.Get_dis (x, now) + Make.Get_dis (y, now) + Make.Get_dis (z, now)); 
    }
    return 0;
}
