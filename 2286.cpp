#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
 
#define INF 1e17
 
const int BUF = 10000010;
char Buf[BUF], *buf = Buf;
 
void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
 
#define Max 1000010
 
struct Edge
{
    int to, next, w; 
    Edge (int _x, int _y, int _z) : to (_x), next (_y), w (_z) {}
    Edge () {}
};
 
int N, M;
long long value[Max];
int dfn[Max], Count;
struct Graph
{
    Edge e[Max << 1];
    int C;
    Graph () { C = 0;}
 
    int list[Max];
    inline void Clear ()
    {
        C = 0;
    }
    inline void Add_Edge (int from, int to, int dis)
    {
        if (from == to) return ;
        e[++ C].to = to;
        e[C].next = list[from];
        list[from] = C;
        e[C].w = dis; 
    }
    inline void Add_Edge (int from, int to)
    {
        if (from == to) return ;
        e[++ C].to = to;
        e[C].next = list[from];
        list[from] = C;
    }
};
 
inline void swap (int &x, int &y)
{
    int now = x;
    x = y;
    y = now;
}
 
inline long long min (int x, long long y)
{
    return x < y ? x : y;
}
 
class Tree_Chain_Get
{
    private : 
        Graph G;
        int  size[Max], chain[Max], father[Max], son[Max];
 
    public :
 
        int deep[Max];
 
        void Dfs_1 (int now, int Father)
        {
            size[now] = 1;
            father[now] = Father;
            dfn[now] = ++ Count;
            deep[now] = deep[Father] + 1;
            for (int i = G.list[now]; i; i = G.e[i].next)
                if (G.e[i].to != Father)
                {
                    value[G.e[i].to] = min (G.e[i].w, value[now]); 
                    Dfs_1 (G.e[i].to, now);
                    size[now] += size[G.e[i].to];
                    if (size[son[now]] < size[G.e[i].to])
                       son[now] = G.e[i].to; 
                }
        }       
         
        void Dfs_2 (int now, int point)
        {
           chain[now] = point;
           if (son[now])
              Dfs_2 (son[now], point);
           else return ;
           for (int i = G.list[now]; i; i = G.e[i].next)
              if (G.e[i].to != son[now] && G.e[i].to != father[now])
                 Dfs_2 (G.e[i].to, G.e[i].to);
        }
         
        int Get_Lca (int x, int y)
        {
            for (; chain[x] != chain[y]; )
            {
                if (deep[chain[x]] < deep[chain[y]])
                    swap (x, y);
                x = father[chain[x]];
            }
            return deep[x] < deep[y] ? x : y;
        }
         
        inline void Insert_edges (const int L)
        {
            for (int i = 1, x, y, z; i <= L; ++ i)
            {
                read (x), read (y), read (z);
                G.Add_Edge (x, y, z);
                G.Add_Edge (y, x, z);
            }
            value[1] = INF;
            deep[1] = 0;
            Dfs_1 (1, 0);
            Dfs_2 (1, 1);
        }
};
Tree_Chain_Get Lca;
 
inline bool Comp (const int &x, const int &y)
{
    return dfn[x] < dfn[y];
}
 
class Virtual_Tree
{
    private : Graph T; int Stack[Max], top;
            long long dp[Max];
            int queue[Max];
 
    public :
 
        Virtual_Tree () {top = 0;}
 
        void Build_Tree ()
        {
            int M;
            read (M);
            for (int i = 1; i <= M; ++ i)
                read (queue[i]);
            std :: sort (queue + 1, queue + 1 + M, Comp);
            int cur = 0;
            queue[++ cur] = queue[1];
            for (int i = 2; i <= M; ++ i)
                if (Lca.Get_Lca (queue[i], queue[cur]) != queue[cur])
                    queue[++ cur] = queue[i];
            int top = 0;
            Stack[++ top] = 1;
            int __lca;
            T.Clear ();
            for (int i = 1; i <= cur; ++ i)
            {
                __lca = Lca.Get_Lca (Stack[top], queue[i]);
                for (; ; )
                {
                    if (Lca.deep[Stack[top - 1]] <= Lca.deep[__lca])
                    {
                        T.Add_Edge (__lca, Stack[top]);
                        -- top;
                        if (Stack[top] != __lca)
                            Stack[++ top] = __lca;
                        break;
                    }
                    T.Add_Edge (Stack[top - 1], Stack[top]);
                    -- top;
                }
                if (Stack[top] != queue[i])
                    Stack[++ top] = queue[i];
            }
            top --;
            for (; top; -- top)
                T.Add_Edge (Stack[top], Stack[top + 1]);
            Dp (1);
            printf ("%lld\n", dp[1]);
        }
                
 
        void Dp (int now)
        {
            long long res = 0; dp[now] = value[now];
            for (int i = T.list[now]; i; i = T.e[i].next)
            {
                Dp (T.e[i].to);
                res += dp[T.e[i].to];
            }
            T.list[now] = 0;
            if (!res)
                dp[now] = value[now];
            else if (res < dp[now])
                dp[now] = res;
        }
 
        void Doing (const int &K)
        {
            for (int i = 1; i <= K; ++ i)
                Build_Tree ();
        }
};
 
Virtual_Tree V_T;
 
int Main ()
{
    fread (buf, 1, BUF, stdin);
    read (N);
 
    Lca.Insert_edges (N - 1);
    int K;
    read (K);
    V_T.Doing (K);
 
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]){;}
