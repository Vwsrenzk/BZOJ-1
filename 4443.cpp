#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

const int BUF = 10000102;
char Buf[BUF], *buf = Buf;

void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);    
}

#define Max 301
#define INF 1e9

int S, T;
int number[Max][Max];
int N, M, K;

inline int min (int a, int b)
{
    return a < b ? a : b;
}
struct Edge 
{
    int to, next, flow;
};

class Net_Flow
{
    private :

         Edge e[Max * Max * 20];
         int C, list[Max * Max * 2], _tech[Max * Max * 2];
         
         int deep[Max * Max * 2];
         
    public :

         inline void In (int u, int v, int flow)
         {
             e[++ C].to = v, e[C].next = list[u];
             e[C].flow = flow, list[u] = C;
             e[++ C].to = u, e[C].next = list[v];
             e[C].flow = 0, list[v] = C; 
         }
         
         bool Bfs ()
         {
             std :: queue <int> Queue;
             Queue.push (S);
             memset (deep, -1, sizeof deep);
             int now, i; 
             for (deep[S] = 0; !Queue.empty (); Queue.pop ())
             {
                 now = Queue.front ();
                 for (i = list[now]; i; i = e[i].next)
                     if (deep[e[i].to] < 0 && e[i].flow)
                     {
                         deep[e[i].to] = deep[now] + 1;
                         if (e[i].to == T)
                             return true;
                         Queue.push (e[i].to);
                     }
             }
             return deep[T] >= 0;
         }

         int Flowing (int now, int Flow)
         {
             if (now == T || !Flow)
                 return Flow;
             int res = 0, pos;
             for (int &i = _tech[now]; i; i = e[i].next)
             {
                 if (e[i].flow < 0 || deep[e[i].to] != deep[now] + 1)
                     continue;
                 pos = Flowing (e[i].to, min (e[i].flow, Flow));
                 if (pos > 0)
                 {
                     e[i].flow -= pos;
                    res += pos;
                    Flow -= pos;
                    e[i ^ 1].flow += pos;
                    if (Flow == 0)
                        break;
                 }
             }
             if (res != Flow)
                 deep[now] = -1;
             return res;
         }

         int Dinic ()
         {
              int Answer = 0;
               for (; Bfs (); )
             {
                for (int i = 0; i <= T; ++ i)
                    _tech[i] = list[i];
                 Answer += Flowing (S, INF);
              }
              return Answer;
         }
         
         inline void Clear ()
         {
             C = 1;
             for (int i = 0; i <= T; i ++)
                 list[i] = 0;
         }
};

Net_Flow Flow;
     
bool Check (int key)
{
    Flow.Clear ();
    int i, j;
    for (i = 1; i <= N; ++ i)
        Flow.In (S, i, 1);

    for (i = 1; i <= M; ++ i)
        Flow.In (i + N, T, 1);

    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= M; ++ j)
            if (number[i][j] <= key)
            {
                Flow.In (i, i * M + j - M, INF);
                Flow.In (i * M + j - M, j + N, INF);
            }

    return Flow.Dinic () >= K;    
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}
int Main ()
{
    fread (buf, 1, BUF, stdin);

    read (N);
    read (M);
    read (K);
    
    K = N - K + 1;
    register int Maxn = 0;
    register int i, j;
    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= M; ++ j)
            read (number[i][j]), Maxn = max (Maxn, number[i][j]);
    T = N + M + Max * Max + 1;
    int l = 0, r = Maxn, Mid;
    int Answer;

    for (; l <= r; )
    {
        Mid = l + r >> 1;
        if (Check (Mid))
        {
            r = Mid - 1;
            Answer = Mid;
        }
        else
            l = Mid + 1;
    }
        
    printf ("%d", Answer);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
