#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
 
#define Max 300
#define INF 1e7
 
using namespace std;
 
inline int min (int a, int b)
{
    return a < b ? a : b;
}
 
void read (int &now)
{
    now = 0;
    char word = getchar ();
    while (word > '9' || word < '0')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}
 
int S, T;
 
struct Edge
{
    int to;
    int next;
    int flow;
}edge[Max << 6];
 
int Edge_Count = 1;
int edge_list[Max];
 
int N, M;
int is[Max];
 
inline void AddEdge (int from, int to)
{
    Edge_Count++;
    edge[Edge_Count].to = to;
    edge[Edge_Count].flow = 1;
    edge[Edge_Count].next = edge_list[from];
    edge_list[from] = Edge_Count;
    Edge_Count++;
    edge[Edge_Count].to = from;
    edge[Edge_Count].flow = 0;
    edge[Edge_Count].next = edge_list[to];
    edge_list[to] = Edge_Count;
}
 
int deep[Max];
 
int Flowing (int now, int flow)
{
    if (flow <= 0 || now == T)
        return flow;
    int res = 0, pos;
    for (int i = edge_list[now]; i; i = edge[i].next)
    {
        if (deep[edge[i].to] != deep[now] + 1 || edge[i].flow <= 0)
            continue;
        pos = Flowing (edge[i].to, min (flow, edge[i].flow));
        flow -= pos;
        res += pos;
        edge[i].flow -= pos;
        edge[i ^ 1].flow += pos;
        if (flow <= 0)
            return res;        
    }
    return res;
}
 
 
int main (int argc, char *argv[])
{
    int G;
    read (G);
    while (G--)
    {
        read (N);
        memset (edge_list, 0, sizeof edge_list);
        memset (is, 0, sizeof is);
        S = 0;
        T = Max - 1;
        Edge_Count = 1;
        int Fact = N;
        for (int i = 1; i <= N; i++)
        {
            read (is[i]);
            if (is[i])
                AddEdge (N + i, T);
        }
        int x;
        int Answer = 0;
        for (int i = 1; i <= N; i++)
        {
            read (x);
            if (is[i])
            {
                if (!x)
                    AddEdge (S, i);
                else
                    Fact--;
            }
            else
                AddEdge (S, i);
        }
        for (int i = 1; i <= N; i++)
        {
            if (is[i])
                AddEdge (i, i + N);
            for (int j = 1; j <= N; j++)
            {
                read (x);
                if (x)
                    AddEdge (i, j + N);
            }
        }
        while (true)
        {
            bool flag = false;
            memset (deep, -1, sizeof deep);
            queue <int> Queue;
            Queue.push (S);
            deep[S] = 0; 
            int now;
            while (!Queue.empty ())
            {
                now = Queue.front ();
                Queue.pop ();
                for (int i = edge_list[now]; i; i = edge[i].next) 
                    if (deep[edge[i].to] < 0 && edge[i].flow)
                    {
                        deep[edge[i].to] = deep[now] + 1;
                        if (edge[i].to == T)
                        {
                            flag = true;
                            break;
                        }
                        Queue.push (edge[i].to); 
                    }
                if (flag)
                    break;
            }
            if (deep[T] < 0)
                break;
            Answer += Flowing (S, INF);
        }
        printf (Answer >= Fact ? "^_^\n" : "T_T\n");
    }
    return 0;
}
