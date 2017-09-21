#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define Max 1000006
#define INF 1e8
 
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
inline int min (int a, int b)
{
    return a < b ? a : b;
}
 
struct Edge
{
    int to;
    int next;
    int flow;
}edge[Max * 6];
 
int Edge_Count = 1, edge_list[Max];
int deep[Max];
 
inline void AddEdge (int from, int to, int flow)
{
    Edge_Count++;
    Edge *now = &edge[Edge_Count];
    now->flow = flow;
    now->to = to;
    now->next = edge_list[from];
    edge_list[from] = Edge_Count;
}
 
int N, M, S, T;
 
int Get_Flow (int now, int flow)
{
    if (now == T)
        return flow;
    int res = 0, pos;
    for (int i = edge_list[now]; i; i = edge[i].next)
    {
        if (deep[edge[i].to] != deep[now] + 1 || edge[i].flow <= 0)
            continue;
        pos = flow - res;
        pos = Get_Flow (edge[i].to, min (pos, edge[i].flow));
        res += pos;
        edge[i].flow -= pos;
        edge[i ^ 1].flow += pos;
        if (res == flow)
            return flow;
    }
    if (res == 0)
        deep[now] = -1;
    return res;
}
 
int Answer;
int dasf;
bool Bfs ()
{
    memset (deep, -1, sizeof (deep));
    queue <int> Queue;
    Queue.push (S);
    deep[S] = 0;
    int now;
    while (!Queue.empty())
    {
        now = Queue.front();
        Queue.pop ();
        for (int i = edge_list[now]; i; i = edge[i].next)
            if (edge[i].flow && deep[edge[i].to] < 0)
            {
                deep[edge[i].to] = deep[now] + 1;
                Queue.push (edge[i].to); 
            }
    } 
    if (deep[T] == -1)
        return false;
    return true;
}
 
int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int x;
    S = 1;
    T = N * M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j < M; j++)
        {
            read (x);
            AddEdge ((i - 1) * M + j, (i - 1) * M + j + 1, x);
            AddEdge ((i - 1) * M + j + 1, (i - 1) * M + j, x);
        } 
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= M; j++)
        {
            read (x);
            AddEdge ((i - 1) * M + j, i * M + j, x);
            AddEdge (i * M + j, (i - 1) * M + j, x);
        }
    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
        {
            read (x);
            AddEdge ((i - 1) * M + j, i * M + j + 1, x);
            AddEdge (i * M + j + 1, (i - 1) * M + j, x);
        }
    while (Bfs ())
        Answer += Get_Flow (S, INF);
    printf ("%d", Answer);
    return 0;
}
﻿
