#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

const int BUF = 12312312;
char Buf[BUF], *buf = Buf;

#define Max 205
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
using std :: min;
using std :: max;

#define INF 1e8
struct E
{
    E *n, *r;
    int to, f;
    double c;
};

class Net_Flow
{
    private :
    
        E poor[Max * Max * 2], *list[Max], *Tail, *pre[Max];    
        int S, T, can[Max];
           double deep[Max];
        bool visit[Max];

    public :
        
        inline void In (int u, int v, int f, double c)
        {
            ++ Tail, Tail->to = v, Tail->n = list[u], list[u] = Tail;
            Tail->c = c, Tail->f = f;
            ++ Tail, Tail->to = u, Tail->n = list[v], list[v] = Tail;
            Tail->c = -c, Tail->f = 0;
            (Tail - 1)->r = Tail, Tail->r = (Tail - 1);
        }    

        inline void Set_ST (int x, int y) { S = x, T = y; }

        bool Bfs ()
        {
            std :: queue <int> Queue; Queue.push (S); can[S] = INF;
            for (register int i = 0; i < Max; ++ i) deep[i] = -INF;
            memset (visit, false, sizeof visit); E *e; int now;
            for (deep[S] = 0, visit[S] = true; !Queue.empty (); Queue.pop ())
            {
                now = Queue.front (); visit[now] = false;
                for (e = list[now]; e; e = e->n)
                    if (e->f && deep[e->to] < deep[now] + e->c)
                    {
                        pre[e->to] = e, can[e->to] = min (can[now], e->f);
                        deep[e->to] = deep[now] + e->c;
                        if (!visit[e->to])
                            visit[e->to] = true, Queue.push (e->to);
                    }
            }
            return deep[T] > -INF;
        }

        double Dinic ()
        {
            double res = 0;
            for (int x; Bfs (); )
            {
                x = can[T];
                for (int t = T; t != S; t = pre[t]->r->to)
                    pre[t]->f -= x, pre[t]->r->f += x;
                res += deep[T];    
            }
            return res;
        }

        void Clear ()
        {
            Tail = poor;
            for (register int i = 0; i < Max; ++ i)
                list[i] = NULL;
        }
};
Net_Flow Flow;

double a[Max][Max], b[Max][Max];

int Main ()
{
    fread (buf, 1, BUF, stdin);

    int N, x; read (N); register int i, j;
    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= N; ++ j)
            read (x), a[i][j] = (double) x;
    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= N; ++ j)
            read (x), b[i][j] = (double) x;
    int S, T; Flow.Set_ST (S = 0, T = (N << 1) + 1);
    double l, r = 1e4, Mid, res;

    for (int Time = 1; Time <= 37; ++ Time)
    {
        Mid = (l + r) / 2.0; Flow.Clear ();
        for (i = 1; i <= N; ++ i)
            Flow.In (S, i, 1, 0), Flow.In (N + i, T, 1, 0);
        for (i = 1; i <= N; ++ i)
            for (j = 1; j <= N; ++ j)
                Flow.In (i, N + j, 1, a[i][j] - b[i][j] * Mid);
        res = Flow.Dinic ();
        if (res <= 0) r = Mid;
        else l = Mid;
    }
    printf ("%.6lf", l);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
