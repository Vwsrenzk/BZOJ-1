#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#define Max 2005
std :: bitset <1005> a[Max];
#define rg register
char s[Max];
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
int Answer;
inline void cmax (int &a, int b) { if (b > a) a = b; }
void Gauss (int N, int M)
{
    rg int i, j, n = 0, k;
    for (i = 1; i <= N; ++ i)
    {
        for (j = n + 1; !a[j][i] && j <= M; ++ j);
        if (j == M + 1) { Answer = -1; return ; }
        else cmax (Answer, j);
        for (++ n, std :: swap (a[j], a[n]), k = 1; k <= M; ++ k)
            if (k != n && a[k][i]) a[k] ^= a[n];
    }            
}
int main (int argc, char *argv[])
{
    int N, M, x; read (N), read (M); rg int i, j;
    for (i = 1; i <= M; ++ i)
    {
        scanf ("%s", s + 1);
        for (j = 1; j <= N; ++ j) a[i][j] = s[j] - '0';
        read (x); a[i][N + 1] = x;
    }
    Gauss (N, M);
    if (Answer != -1)
    {
        std :: cout << Answer << std :: endl;
        for (i = 1; i <= N; ++ i)
            if (a[i][N + 1]) puts ("?y7M#");
            else puts ("Earth");
    }
    else puts ("Cannot Determine");
    return 0;
}
