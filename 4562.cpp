#include <cstdio>
#include <iostream>
 
const int BUF = 12312312;
char Buf[BUF], *buf = Buf;
 
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 200004
 
int N, M, S, T, Answer;
struct E { E *n; int v; }; 
E *list[Max], poor[Max << 2], *Ta = poor;
int _in[Max], _out[Max];
 
int c[Max];
 
int Dfs (int now)
{
    if (_out[now] == 0) return 1;
    if (c[now]) return c[now]; int res = 0;
    for (E *e = list[now]; e; e = e->n)
        res += Dfs (e->v);
    c[now] = res; return res;
}
 
int Main ()
{
    fread (buf, 1, BUF, stdin); int x, y;
    read (N), read (M); register int i, j;
    for (i = 1; i <= M; ++ i)
    {
        read (x), read (y);
        ++ Ta, Ta->n = list[x], list[x] = Ta, Ta->v = y;
        ++ _in[y], ++ _out[x];
    }
    for (i = 1; i <= M; ++ i)
        if (_in[i] == 0 && _out[i]) Answer += Dfs (i);    
    printf ("%d", Answer);
    return 0;
}
 
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
