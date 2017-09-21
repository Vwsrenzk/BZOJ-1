#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

#define Max 3050
 
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

inline int max (int a, int b)
{
    return a > b ? a : b;
}

struct Edge_Data
{
    int to;
    int dis;
    int next;
};

struct Data_
{
    int Id;
    int dis;
    
    Data_ (int __Id, int __dis) : Id (__Id), dis (__dis) {};
     
    bool operator < (const Data_ &now) const
    {
        return this->dis > now.dis; 
    }
    
    Data_ () {};
};

int N, M;
int number[Max];

int __link[Max][Max];
int count[Max];

int Answer;

class Dijkstra_Type
{
    private :
        
        Edge_Data edge[Max * 100];
        
        int Edge_Count ;
        int edge_list[Max];
        
        int dis_1[Max];
        int dis_2[Max];
        
        bool visit[Max];
        
    public :
        
        inline void Insert_Edge (int from, int to, int dis)
        {
            
            Edge_Count ++;
            edge[Edge_Count].to = to;
            edge[Edge_Count].next = edge_list[from];
            edge[Edge_Count].dis = dis;
            edge_list[from] = Edge_Count;
            
        }
    
        void Dijkstra (int Start, int End)
        {
            memset (dis_1, 0x3f, sizeof dis_1);
            
            std :: priority_queue <Data_> Queue;
            Queue.push (Data_ (Start, 0)); 
            dis_1[1] = 0;
            
            Data_ now;
            register int Maxn, res;
            register int pos;
            
            while (!Queue.empty ())
            {
                now = Queue.top ();
                Queue.pop ();
                
                if (visit[now.Id])
                    continue;
                
                visit[now.Id] = true;
                Maxn = max (dis_1[now.Id], dis_2[now.Id]);
                
                for (int i = edge_list[now.Id]; i; i = edge[i].next)
                    if (dis_1[edge[i].to] > Maxn + edge[i].dis)
                    {
                        dis_1[edge[i].to] = Maxn + edge[i].dis;
                        int res = max (dis_1[edge[i].to], dis_2[edge[i].to]);
                        if (!number[edge[i].to])
                            Queue.push (Data_ (edge[i].to, res)); 
                    }
                    
                for (int i = 1; i <= count[now.Id]; i ++)
                {
                    pos = __link[now.Id][i];
                    number[pos] --;
                    dis_2[pos] = max (dis_2[pos], Maxn);
                    res = max (dis_1[pos], dis_2[pos]);
                    if (!number[pos])
                        Queue.push (Data_ (pos, res)); 
                }
            }
            Answer = max (dis_1[End], dis_2[End]);
        }
};

Dijkstra_Type Make;

int main (int argc, char *argv[])
{
    
    read (N);
    read (M);
    int x, y, z;
    
    for (int i = 1; i <= M; i ++)
    {
        read (x);
        read (y);
        read (z);
        
        if (x != y)
            Make.Insert_Edge (x, y, z); 
    }
    
    for (int i = 1; i <= N; i ++)
    {
        read (number[i]);
        for (int pos = 1, x; pos <= number[i]; pos ++)
        {
            read (x);
            __link[x][++ count[x]] = i;
        }
    }
    
    Make.Dijkstra (1, N);
    
    printf ("%d", Answer);
    return 0;
}
