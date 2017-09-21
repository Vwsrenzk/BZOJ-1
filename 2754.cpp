#include <cstdio>
#include <map>
#include <vector>
#include <queue>
 
#define Max 80090
 
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
 
int N, M;
 
struct T_D 
{
    int Flandre;
    int Id;
    T_D *Fail;
    std :: map <int, T_D *> child;
 
    T_D ()
    {
     
        child.clear ();
        Flandre = 0;
        Id = 0;
 
        Fail = NULL;
    }
};
 
std :: map <int, bool> visit;
 
std :: vector <int> name[Max];
std :: vector <int> count[Max * 3];
 
int Answer_1[Max];
int Answer_2[Max];
 
class AC_Type
{
     
    private :
 
        T_D *Root ;
        int Count;
 
        int Insert_Count;
 
    public :
 
        AC_Type ()
        {
            Count = 0;
            Root = new T_D ;
            Root->Id = ++ Count;
            Insert_Count = 0;
 
        }
 
        void Insert (int Len)
        {
 
            T_D *now = Root;
            int Id;
            for (int i = 1; i <= Len; i ++)
            {
                read (Id);  
                if (now->child[Id] == NULL)
                {
                    now->child[Id] = new T_D;
                    now->child[Id]->Id = ++ Count;
                }
                now = now->child[Id];
            }
            now->Flandre ++;
            count[now->Id].push_back (++ Insert_Count);
        }
 
        void Build_AC ()
        {
            std :: queue <T_D *> Queue;
             
            Queue.push (Root);
            T_D *now, *pos;
 
            while (!Queue.empty ())
            {
                now = Queue.front ();
                Queue.pop ();
 
                pos = NULL;
 
                for (std :: map <int, T_D *> :: iterator i = now->child.begin (); i != now->child.end (); i ++)
                {
                    if (now == Root)
                        i->second->Fail = Root;
                    else
                    {
                        for (pos = now->Fail; pos; pos = pos->Fail)
                            if (pos->child[i->first])
                            {
                                i->second->Fail = pos->child[i->first];
                                break;
                            }
                        if (pos == NULL)
                            i->second->Fail = Root;
                    }
                    Queue.push (i->second);
                }
            }
        }
 
        T_D *Get_Root ()
        {
            return Root;
        }
};
 
AC_Type Make;

void Calculate (T_D *now, int i)
{
    if (now->Flandre)
    {
        Answer_2[i] += now->Flandre;
        for (int k = 0; k < count[now->Id].size (); k ++)
            Answer_1[count[now->Id][k]] ++;
    }
}

int main (int argc, char *argv[])
{   
    read (N);
    read (M);

    for (int i = 1, x, y; i <= N; i ++)
    {
        read (x);
        for (int j = 1; j <= x; j ++)
        {
            read (y);
            name[i].push_back (y);
        }
        name[i].push_back (-1);
        read (x);
        for (int j = 1; j <= x; j ++)
        {
            read (y);
            name[i].push_back (y);
        }
        name[i].push_back (-2);
    }

    for (int i = 1, x; i <= M; i ++)
    {
        read (x);
        Make.Insert (x);
    }

    Make.Build_AC ();

    int Len;
    T_D *now , *pos;

    for (int i = 1; i <= N; i ++)
    {
        Len = name[i].size ();
        visit.clear ();
        now = Make.Get_Root ();
        pos = NULL;
 
        for (int j = 0; j < Len; j ++)
        {
            if (!visit[now->Id])
            {
                visit[now->Id] = true;
                Calculate (now, i);
                for (pos = now->Fail; pos; pos = pos->Fail)
                    if (!visit[pos->Id])
                    {
                        visit[pos->Id] = true;
                        Calculate (pos, i);
                    }
            }
            if (now->child[name[i][j]])
                now = now->child[name[i][j]];
            else
            {
                for (pos = now->Fail; pos; pos = pos->Fail)
                {
                    if (!visit[pos->Id])
                    {
                        visit[pos->Id] = true;
                        Calculate (pos, i);
                    }
                    if (pos->child[name[i][j]])
                    {
                        now = pos->child[name[i][j]];
                        for (T_D *Saber = pos->Fail; Saber; Saber = Saber->Fail)
                            if (!visit[Saber->Id])
                            {
                                visit[Saber->Id] = true;
                                Calculate (Saber, i);
                            }
                        break;
                    }
                }
                if (pos == NULL)
                    now = Make.Get_Root ();
            }
        }
    }

    for (int i = 1; i <= M; i ++)
        printf ("%d\n", Answer_1[i]);
    printf ("%d", Answer_2[1]);
 
    for (int i = 2; i <= N; i ++)
        printf (" %d", Answer_2[i]);
 
    return 0;
}
