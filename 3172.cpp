#include <cstdio>
#include <cstring>

#define Max 1000005

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

struct T_D 
{
    T_D *child[26];
    
    T_D *Fail;

    int number;
    int Count;

    T_D ()
    {
        number = 0;

        for (int i = 0; i < 26; i ++)
            this->child[i] = NULL;
        
        Count = 0;
        Fail = NULL;
    }

};

T_D *Queue[Max];

int Answer[Max];

class AC_Type
{

    private :

        T_D *Root;

        int Trie_Count;
        
        int Head, Tail;
    public :

        AC_Type ()
        {
            Root = new T_D;
            Root->number = ++ Trie_Count;    
        }

        void Insert (char *key, int &x)
        {
            int Len = strlen (key);
            T_D *now, *pos;

            now = Root;
            int Id;

            for (int i = 0; i < Len; i ++)
            {
                Id = key[i] - 'a';
                if (now->child[Id] == NULL)
                {
                    now->child[Id] = new T_D;
                    now->child[Id]->number = ++ Trie_Count;
                }
                Answer[now->child[Id]->number] ++;
                now = now->child[Id];
            }
            x = now->number;
        }

        void Build_AC ()
        {
            
            T_D *now, *pos;

            Head = 0, Tail = 0;
            Queue[++ Tail] = Root;

            while (Head != Tail)
            {
                Head ++;
                now = Queue[Head];
                
                pos = NULL;

                for (int i = 0; i < 26; i ++)
                {
                    if (now->child[i] == NULL)
                        continue;
                    if (now == Root)
                        now->child[i]->Fail = Root;
                    else
                    {
                        for (pos = now->Fail; pos; pos = pos->Fail)
                            if (pos->child[i])
                            {
                                now->child[i]->Fail = pos->child[i];
                                break;
                            }
                        if (pos == NULL)
                            now->child[i]->Fail = Root;
                    }
                    Queue[++ Tail] = now->child[i];    
                }
            }
        }

        void Solve ()
        {
            for (int i = Tail; i; i --)
                if (Queue[i]->Fail)
                    Answer[Queue[i]->Fail->number] += Answer[Queue[i]->number];
        }
};

AC_Type Make;

char line[Max];
int to[Max];

int main (int argc, char *argv[])
{

    int N;
    read (N);

    for (int i = 1; i <= N; i ++)
    {
        scanf ("%s", line);
        Make.Insert (line, to[i]);
    }
    
    Make.Build_AC ();

    Make.Solve ();
    for (int i = 1; i <= N; i ++)
        printf ("%d\n", Answer[to[i]]);

    return 0;
}
