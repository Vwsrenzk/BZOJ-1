#include <cstdio>
#include <stack>
#include <queue>

#define Max 500900

inline int max (int a, int b)
{
    return a > b ? a : b;
}

inline int min (int a, int b)
{
    return a < b ? a : b;
}

void read (int &now)
{
    now = 0;
    register char word = getchar ();
    while (word > '9' || word < '0')
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
        int dis;
    } 
    edge[Max];
    
    int Edge_Count;
    int edge_list[Max];
    
    void Add_Edge (int from, int to)
    {
        Edge_Count++;
        edge[Edge_Count].to = to;
        edge[Edge_Count].next = edge_list[from];
        edge_list[from] = Edge_Count;
    }
};

Edge_Type Graph_1;

Edge_Type Graph;

int point_dis[Max];
int value[Max];

int N, M;

struct Tarjan_Type
{
    
    std :: stack <int> Stack;
    
    int number[Max];
    int lowlink[Max];
    int Scc_Count;
    
    int Count;
    
    int scc_number[Max];
    
    void Tarjan_ (int N)
    {
        for (int i = 1; i <= N; i++)
            if (!number[i])
                Dfs (i);
    }
    
    void Dfs (int now)
    {
        Count++;
        number[now] = Count;
        lowlink[now] = Count;
        Stack.push (now);
        for (int i = Graph_1.edge_list[now]; i; i = Graph_1.edge[i].next)
            if (!number[Graph_1.edge[i].to])
            {
                Dfs (Graph_1.edge[i].to);
                lowlink[now] = min (lowlink[now], lowlink[Graph_1.edge[i].to]);
            }
            else if (!scc_number[Graph_1.edge[i].to])
                lowlink[now] = min (lowlink[now], number[Graph_1.edge[i].to]);
        if (lowlink[now] == number[now])
        {
            Scc_Count++;
            int res = now + 1;
            while (res != now)
            {
                res = Stack.top ();
                Stack.pop ();
                scc_number[res] = Scc_Count;
                point_dis[Scc_Count] += value[res];
            }
        }
    }
    
    void Narrow_Point ()
    {
        for (int now = 1; now <= N; now++)
            for (int i = Graph_1.edge_list[now]; i; i = Graph_1.edge[i].next)
                if (scc_number[now] != scc_number[Graph_1.edge[i].to])
                    Graph.Add_Edge (scc_number[now], scc_number[Graph_1.edge[i].to]); 
    }
};


Tarjan_Type Make;

struct Spfa_Type
{
    int distance[Max];
    
    std :: queue <int> Queue;
    bool visit[Max];
    
    int S;
    
    void Do_Spfa (int S)
    {
        Queue.push (S); 
        visit[S] = true;
        int now;
        distance[S] = point_dis[S];
        while (!Queue.empty ())
        {
            now = Queue.front ();
            Queue.pop ();  
            visit[now] = false;
            for (int i = Graph.edge_list[now]; i; i = Graph.edge[i].next)
                if (distance[Graph.edge[i].to] < distance[now] + point_dis[Graph.edge[i].to])
                {
                    distance[Graph.edge[i].to] = distance[now] + point_dis[Graph.edge[i].to];
                    if (!visit[Graph.edge[i].to])
                    {
                        Queue.push (Graph.edge[i].to);
                        visit[Graph.edge[i].to] = true; 
                    }
                }
        }
    }
};

Spfa_Type Spfa;
int S, P;

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int x, y;
    for (int i = 1; i <= M; i++)
    {
        read (x);
        read (y);
        Graph_1.Add_Edge (x, y); 
    }
    for (int i = 1; i <= N; i++)
        read (value[i]);
    Make.Tarjan_ (N);
    Make.Narrow_Point ();
    read (S);
    read (P);
    Spfa.Do_Spfa (Make.scc_number[S]);
    int Answer = 0;
    for (int i = 1; i <= P; i++)
    {
        read (x);
        Answer = max (Answer, Spfa.distance[Make.scc_number[x]]);
    }  
    printf ("%d", Answer);
    return 0;
}
