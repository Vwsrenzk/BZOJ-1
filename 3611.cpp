#include <cstdio>
#include <iostream>
#include <algorithm>
#define INF 1e9

#define Max 1000004

const int BUF = 100000100;

char Buf[BUF], *buf = Buf;
void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
struct Edge
{
    int to, next, w;
};
int deep[Max];

inline int min (int a, int b)
{
    return a < b ? a : b;
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}

struct Graph
{
    Edge e[Max << 1];
    int C, list[Max];
    
    inline void In (int from, int to)
    {
        if (from == to) return ;
        e[++ C].to = to;
        e[C].next = list[from];
        list[from] = C;
        e[C].w = deep[to] - deep[from];
    }

    inline void Clear () { C = 0;}    
};
int dfn[Max], Dfs_Clock;
inline bool Comp (int a, int b)
{
    return dfn[a] < dfn[b];
}

void swap (int &a, int &b)
{
    int now = a;
    a = b;
    b = now;
}
class Tree_Chain_Get
{
    private : Graph G;
              int size[Max], father[Max], chain[Max], son[Max];

    public :
        
        void Dfs_1 (int now, int Father)
        {
            size[now] = 1, father[now] = Father;
               deep[now] = deep[Father] + 1, dfn[now] = ++ Dfs_Clock;
            for (int i = G.list[now]; i; i = G.e[i].next)
                if (G.e[i].to != Father)
                {
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

        inline void Insert_edges (const int &M)
        {
            for (int i = 1, x, y; i <= M; i ++)
            {
                read (x), read (y);
                G.In (x, y), G.In (y, x);
            }
            Dfs_1 (1, 0);
            Dfs_2 (1, 1);
        }

        inline int Get_Lca (int x, int y)
        {
            for (; chain[x] != chain[y]; )
            {
                if (deep[chain[x]] < deep[chain[y]])
                    swap (x, y);
                x = father[chain[x]];
            }
            return deep[x] < deep[y] ? x : y;
        }    
};


Tree_Chain_Get Lca;
class Virtual_Tree
{
    private : 
        
        Graph T;
        int visit[Max];
        int key[Max], Stack[Max], maxn[Max], minn[Max], Total;
        long long Answer_1, size[Max], dp[Max];
        int Answer_2, Answer_3;

    public :
        
        void Dp (int now)
        {
            size[now] = visit[now];
            dp[now] = 0;
            minn[now] = visit[now] ? 0 : INF;
            maxn[now] = visit[now] ? 0 : -INF;
            int to;
            for (int i = T.list[now]; i; i = T.e[i].next)
            {
                to = T.e[i].to;
                Dp (to);
                Answer_1 += (dp[now] + size[now] * T.e[i].w) * size[to] + dp[to] * size[now];
                size[now] += size[to];
                dp[now] += dp[to] + T.e[i].w * size[to];
                Answer_2 = min (Answer_2, minn[now] + minn[to] + T.e[i].w);
                Answer_3 = max (Answer_3, maxn[now] + maxn[to] + T.e[i].w);
                minn[now] = min (minn[now], minn[to] + T.e[i].w);
                maxn[now] = max (maxn[now], maxn[to] + T.e[i].w);
            }
            T.list[now] = 0;
        }    
        void Build_Tree ()
        {
            int K;
            read (K);
            for (int i = 1; i <= K; ++ i)
            {
                read (key[i]);
                visit[key[i]] = 1;
            }
            std :: sort (key + 1, key + 1 + K, Comp);
            int top = 0, lca;register int now;
            T.Clear ();
            Stack[++ top] = 1;
            for (int i = 1; i <= K; ++ i)
            {
                now = key[i];
                lca = Lca.Get_Lca (now, Stack[top]);
                if (lca == Stack[top])
                {
                    Stack[++ top] = now;
                    continue;
                }
                for (; lca == Lca.Get_Lca (now, Stack[top - 1]); )
                {
                    T.In (Stack[top - 1], Stack[top]);
                    -- top;
                    lca = Lca.Get_Lca (now, Stack[top]);
                }
                T.In (lca, Stack[top]);
                Stack[top] = lca;
                Stack[++ top] = now;
            }
            for (; -- top; T.In (Stack[top], Stack[top + 1]));
            Answer_1 = 0,  Answer_2 = INF, Answer_3 = -INF;
            Dp (1);
            printf ("%lld %d %d\n", Answer_1, Answer_2, Answer_3);
            for (int i = 1; i <= K; ++ i)
                visit[key[i]] = 0;
        }

        void Doing (const int &K)
        {
            for (int i = 1; i <= K; ++ i)
                Build_Tree ();
        }
};

Virtual_Tree Flandre;

int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N, M;
    read (N);
    
    Lca.Insert_edges (N - 1);
    read (M);
    Flandre.Doing (M);    

    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
