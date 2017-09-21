#include <cstdio>

void read (int &now)
{
    register char word = getchar ();
    for (now = 0; word < '0' || word > '9'; word = getchar ());
    for (; word >= '0' && word <= '9'; now = now * 10 + word - '0', word = getchar ());
}

#define Max 5000010

int __next[Max];
int __to[Max];
int edge_list[Max];
int Edge_Count = 1;
char __key[Max];

int value[Max];

inline int max (int a, int b)
{
    return a > b ? a : b;
}

int main (int argc, char *argv[])
{
    int N;
    read (N);
    register char c;
    long long Answer = 0;
    int now, pos;
    for (register int i, j; N; -- N)
    {
        for (c = getchar (); c == '\n'; c = getchar ());
        
        for (j = now = 1; c != '\n'; c = getchar (), j ++)
        {
            for (pos = 0, i = edge_list[now]; i; i = __next[i])
                if (__key[i] == c)
                {
                    pos = __to[i];
                    break;
                }
            if (!pos)
            {
                pos = ++ Edge_Count;
                __to[Edge_Count] = pos;
                __next[Edge_Count] = edge_list[now];
                edge_list[now] = Edge_Count;
                __key[Edge_Count] = c;
            }
            value[now = pos] ++;
            Answer = max (Answer, (long long) j * value[now]);
        }
    }
    
    printf ("%d", Answer);
    return 0;
}
