#include <cstdio>
#include <cstdlib>

#define Max 200005

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
        now = - now;
}

#define INF 1e60

int Heart;
int N, M; 
long long Total;

inline int swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}

struct Segment_Tree_Data
{
    Segment_Tree_Data *Left, *Right;

    int Mid;
    int key;

    int l, r;

    Segment_Tree_Data (int __l, int __r)
    {
        r = __r;
        Left = Right = NULL;
        Mid = __l == __r ? 0 : (__l + __r >> 1);
        l = __l;
        key = 0;
    }

    inline void Updata ()
    {
        this->key = this->Left->key + this->Right->key;
    }

};

struct Edge_Data
{
    int to;
    int next;
    int value;
};

long long Answer;

struct Point_Data
{
    int size;
    int deep;
    int tree_number;
    int up;
    int father;
    int End;
    int distance;
};

inline int min (int a, int b)
{
    return a < b ? a : b;
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}

Segment_Tree_Data *Root;

class Segment_Tree_Type
{

    private :


        void __Build_ (Segment_Tree_Data *&now, int l, int r)
        {
            now = new Segment_Tree_Data (l, r);
            if (l == r)
                return ;
            __Build_ (now->Left, l, now->Mid);
            __Build_ (now->Right, now->Mid + 1, r);
        }
        
        int __Query_ (Segment_Tree_Data *&now, int l, int r)
        {
            if (l <= now->l && now->r <= r)
                return now->key;
            int res = 0;
            if (l <= now->Mid)
                res += __Query_ (now->Left, l, min (now->Mid, r));
            if (r > now->Mid)
                res += __Query_ (now->Right, max (now->Mid + 1, l), r);
            return res;
        }

        void __Change_ (Segment_Tree_Data *&now, int pos, int to)
        {
            if (now->l == now->r)
            {
                now->key += to;
                return ;
            }
            if (pos <= now->Mid)
                __Change_ (now->Left, pos, to);
            else
                __Change_ (now->Right, pos, to);
            now->Updata ();
        }

    public :
        
        void Build (int l, int r)
        {
            __Build_ (Root, l, r);
            return ;
        }

        int Query (int l, int r)
        {
            return __Query_ (Root, l, r);
        }

        void Change (int pos, int to)
        {
            __Change_ (Root, pos, to);
            return ;
        }
};

Segment_Tree_Type Tree;

Edge_Data edge[Max << 2];

class Tree_Chain_Get_Type
{

    private :

        int edge_list[Max];

        int Edge_Count;

        Point_Data point[Max];

        inline void Add_Edge (int from, int to, int dis)
        {
            Edge_Count ++;
            edge[Edge_Count].to = to;
            edge[Edge_Count].next = edge_list[from];
            edge[Edge_Count].value = dis;
            edge_list[from] = Edge_Count;
            
            Edge_Count ++;
            edge[Edge_Count].to = from;
            edge[Edge_Count].value = dis;
            edge[Edge_Count].next = edge_list[to];
            edge_list[to] = Edge_Count;
        }
        
        int Count;

        void Dfs_1 (int now, int father)
        {
            int pos = Count ++;
            point[now].father = father;
            point[now].deep = point[father].deep + 1;
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to == father)
                {
                    point[now].distance = point[father].distance + edge[i].value;
                    break;
                }            
                for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != father)
                    Dfs_1 (edge[i].to, now);
            point[now].size = Count - pos;
        }

        void Dfs_2 (int now, int chain)
        {
            int pos = 0;
            point[now].up = chain;
            point[now].tree_number = ++Count;
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (!point[edge[i].to].tree_number && point[edge[i].to].size > point[pos].size)
                    pos = edge[i].to;
            if (!pos)
            {
                point[now].End = Count;
                return ;
            }
            Dfs_2 (pos, chain);
            for (int i = edge_list[now]; i; i = edge[i].next)
                if (edge[i].to != pos && !point[edge[i].to].tree_number)
                    Dfs_2 (edge[i].to, edge[i].to);
            point[now].End = Count;
        }

    public :

        void Insert_edges ()
        {
            for (int i = 1, x, y, z; i < N; i++)
            {
                read (x);
                read (y);
                read (z);
                Add_Edge (x, y, z);
            }
        }

        int Get_Lca (int x, int y)
        {
            while (point[x].up != point[y].up)
            {
                if (point[point[x].up].deep < point[point[y].up].deep)
                    swap (x, y);
                x = point[point[x].up].father;
            }
            return point[x].deep < point[y].deep ? x : y;
        }
    
        void Prepare ()
        {
            Count = 0;
            Dfs_1 (1, 0);
            Count = 0;
            Dfs_2 (1, 1);
            Count = 0;
            Tree.Build (1, N);
        }

        int Get_Dis (int x, int y)
        {
            return point[x].distance + point[y].distance - 2 * point[Get_Lca (x, y)].distance;
        }
        
        long long Calculate (int now, int v)
        {
            int now_1, now_2;
            if (now == point[Heart].father)
            {
                now_1 = Tree.Query (point[Heart].tree_number, point[Heart].End);
                now_2 = Total - now_1;
            }
            else
            {
                now_2 = Tree.Query (point[now].tree_number, point[now].End);
                now_1 = Total - now_2;
            }
            return Answer + (long long) (now_1 - now_2) * v;
        }

        void Move_Heart (int now)
        {
            long long Minn = (long long)INF;
            long long res;
            int pos = 0;
            for (int i = edge_list[now]; i; i = edge[i].next)
            {
                res = Calculate (edge[i].to, edge[i].value);
                if (res < Minn)
                {
                    Minn = res;
                    pos = edge[i].to;
                }
            }
            if (Minn < Answer)
            {
                Heart = pos;
                Answer = Minn;
                Move_Heart (Heart);
            }
        }

        int Get_tree_number (int x)
        {
            return point[x].tree_number;
        }
};

Tree_Chain_Get_Type Make;


int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int x, y;
    Make.Insert_edges ();
    Make.Prepare ();
    Heart = 1;
    for (; M --; )
    {
        read (x);
        read (y);
        Answer += (long long) y * Make.Get_Dis (x, Heart);
        Total += y;
        Tree.Change (Make.Get_tree_number (x), y);
        Make.Move_Heart (Heart);
        printf ("%lld\n", Answer);
    }    
    return 0;
}
