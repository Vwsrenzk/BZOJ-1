#include <cstdio>
#include <iostream>
 
const int BUF = 12312313;
char Buf[BUF], *buf = Buf;
 
inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}
#define Max 100002
int c[Max], s[Max];
short fc[Max], zc[Max];
 
int Main ()
{
    fread (buf, 1, BUF, stdin); int N, B; read (N), read (B);
    register int i, j; int x, p = -1, Answer = 0;
    for (i = 1; i <= N; ++ i) 
    {
        read (x); s[i] = s[i - 1];
        if (x > B) ++ s[i];  else if (x < B) -- s[i]; else p = i;
        if (p == -1) s[i] < 0 ? ++ fc[- s[i]] : ++ zc[s[i]]; 
    }
    for (++ zc[0]; p <= N; ++ p) Answer += s[p] < 0 ? fc[- s[p]] : zc[s[p]];
    printf ("%d", Answer);  
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
