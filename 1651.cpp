#include <cstdio>
#include <iostream>

const int BUF = 12312313;
char Buf[BUF], *buf = Buf;

inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 1000200
int key[Max];
inline int max (int a, int b)
{
    return a > b ? a : b;
}
int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N, x, y; read (N); register int i;
    for (i = 1; i <= N; ++ i)
    {
        read (x), read (y);
        ++ key[x], -- key[y + 1];
    }
    int Answer = -1, res = 0;
    for (i = 1; i <= Max; ++ i)
    {
        res += key[i];
        Answer = max (Answer, res);
    }
    printf ("%d", Answer);

    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
