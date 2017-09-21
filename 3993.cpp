#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
 
#define Max 101
#define EPS 0.0001
#define INF 1e7
 
using namespace std;
 
void read (int &now)
{
    now = 0;
    char word = getchar ();
    while (word < '0' || word > '9')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}
 
int deep[Max << 2];
 
int N, M;
int S, T = (Max << 2) - 1;
int armor[Max];
int fight[Max];
int Sum;
int Total;
int map[Max][Max];
 
int Edge_Count;
int edge_list[Max << 2];
 
struct Edge
{
    int to;
    double flow;
    int next;
}edge[(Max * Max) << 1];
 
inline void AddEdge (int from, int to, double flow)
{
    Edge_Count++;
    edge[Edge_Count].to = to;
    edge[Edge_Count].next = edge_list[from];
    edge[Edge_Count].flow = flow;
    edge_list[from] = Edge_Count;
    Edge_Count++;
    edge[Edge_Count].to = from;
    edge[Edge_Count].flow = 0;
    edge[Edge_Count].next = edge_list[to];
    edge_list[to] = Edge_Count;
}
 
double min (double a, double b)
{
    return a < b ? a : b;
}
 
double Flowing (int now, double flow)
{
    if (now == T || flow == 0)
        return flow;
    double res = 0, pos;
    for (int i = edge_list[now]; i; i = edge[i].next)
    {
        if (deep[edge[i].to] != deep[now] + 1 || edge[i].flow <= 0)
            continue;
        pos = Flowing (edge[i].to, min (edge[i].flow, flow));
        if (pos > 0)
        {
            flow -= pos;
            res += pos;
            edge[i].flow -= pos;
            edge[i ^ 1].flow += pos;
            if (flow == 0)
                return res;
        }
    }
    if (res == 0)
        deep[now] = -1;
    return res;
}
 
bool Bfs ()
{
    memset (deep, -1, sizeof deep);
    queue <int> Queue;
    deep[S] = 0;
    Queue.push (S); 
    int now;
    while (!Queue.empty ())
    {
        now = Queue.front ();
        Queue.pop ();
        for (int i = edge_list[now]; i; i = edge[i].next)
            if (deep[edge[i].to] < 0 && edge[i].flow > 0)
            {
                deep[edge[i].to] = deep[now] + 1;
                if (edge[i].to == T)
                    return true;
                Queue.push (edge[i].to); 
            }
    }
    return false;
}
 
bool Check (double Time)
{
    double Answer = 0;
    Edge_Count = 1;
    memset (edge_list, 0, sizeof edge_list);
    for (int i = 1; i <= M; i++)
        AddEdge (S, i, fight[i] * Time);
    for (int i = 1; i <= N; i++)
        AddEdge (i + M, T, armor[i]);
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            if (map[i][j])
                AddEdge (i, j + M, INF);
    while (Bfs ())
        Answer += Flowing (S, INF);
    return Answer >= (double)Sum - EPS;
}
 
int main (int argc, char *argv[])
{
    read (N);
    read (M);
    for (int i = 1; i <= N; i++)
    {
        read (armor[i]);
        Sum += armor[i];
    }
    for (int i = 1; i <= M; i++)
    {
        read (fight[i]);
        Total += fight[i];
    }
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++)
            read (map[i][j]);
    double l = (double)Sum / (double)Total, r = 10000.00;
    double Answer = 0;
    double Mid;
    while (l < r)
    {
        Mid = (l + r) / 2.0;
        if (Check (Mid))
        {
            r = Mid - EPS;
            Answer = Mid;
        }
        else
            l = Mid + EPS;
    }
    printf ("%lf", Answer);
    return 0;
}
