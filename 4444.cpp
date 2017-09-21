#include <cstdio>
#include <iostream>
#include <algorithm>

const int BUF = 12312312;
char Buf[BUF], *buf = Buf;

inline void read (int &now)
{
    bool temp = false;
    for (now = 0; !isdigit (*buf); ++ buf)
        if (*buf == '-')  temp = true;
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
    if (temp) now = -now;
}
#define Max 800009

int x[Max], y[Max], s[Max];
int rank[Max], father[Max];
int Answer[Max], L, Stack[Max], top;
int list[Max], next[Max];
int N, M;

void Dfs (int now)
{
    Stack[++ top] = now;
    if (now <= M)
        for (int i = L; ; ++ i)
            if (Stack[top - i] >= now + M)
            {
                Answer[now] = i;
                break;
            }
    for (int i = list[now]; i; i = next[i])
        Dfs (i);
    -- top;
}

int Main ()
{
    fread (buf, 1, BUF, stdin);
    read (N), read (M); M = 0;
    register int i;
    for (i = 1; i <= N; ++ i)
        read (x[i]), read (y[i]), rank[++ M] = x[i], rank[++ M] = y[i];
    std :: sort (rank + 1, rank + 1 + M);
    int Size = std :: unique (rank + 1, rank + 1 + M) - rank - 1;
    for (i = 1; i <= N; ++ i)
    {
        s[i] = x[i] = std :: lower_bound (rank + 1, rank + 1 + Size, x[i]) - rank;
        y[i] = std :: lower_bound (rank + 1, rank + 1 + Size, y[i]) - rank;
        if (x[i] < y[i])
        {
            if (father[x[i]] < y[i]) father[x[i]] = y[i];
            if (father[x[i] + M] < y[i] + M) father[x[i] + M] = y[i] + M;
        }
        else
        {
            if (father[1] < y[i]) father[1] = y[i];
            if (father[x[i]] < y[i] + M) father[x[i]] = y[i] + M;
            if (father[x[i] + M] < (M << 1)) father[x[i] + M] = (M << 1);
        }
    }
    for (i = 1; i <= (M << 1); ++ i)
        if (father[i] < father[i - 1]) 
            father[i] = father[i - 1];
    
    for (i = 1; i < (M << 1); ++ i)
        next[i] = list[father[i]], list[father[i]] = i;

    for (L = -1, i = 1; i <= M; i = father[i]) ++ L;    
    for (Dfs (M << 1), i = 1; i <= N; ++ i)
        printf ("%d ", Answer[s[i]]);    
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
