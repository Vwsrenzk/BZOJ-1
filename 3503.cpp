#include <cstdio>
#include <iostream>
#include <bitset>

#define rg register
#define Max 52

std :: bitset <Max> m[Max];
typedef long long LL;
LL a[Max][Max]; 
int b[Max][Max];

inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
void Gauss (int N, int M)
{
    rg int i, j, n = 0, k;
    for (i = 1; i <= M; ++ i)
    {
        for (j = n + 1; m[j][i] == 0 && j <= M; ++ j);
        if (j == M + 1) continue;
        for (++ n, std :: swap (m[j], m[n]), k = n + 1; k <= M; ++ k)
            if (m[k][i] != 0) m[k] ^= m[n];
    }
    for (i = M; i >= 1; -- i)
    {
        b[1][i] = m[i][M + 1];
        if (m[i][i] == 0) { b[1][i] = 1; continue; }
        for (j = i + 1; j <= M; ++ j)
            if (m[i][j]) b[1][i] ^= b[1][j];
    }
}

int main (int argc, char *argv[])
{
    int N, M; read (N), read (M); rg int i, j;
    for (i = 1; i <= M; ++ i)
        a[1][i] = (LL) 1 << (i - 1);
    for (i = 2; i <= N + 1; ++ i)
        for (j = 1; j <= M; ++ j)
            a[i][j] = a[i - 2][j] ^ a[i - 1][j - 1] ^ a[i - 1][j + 1] ^ a[i - 1][j];
    for (i = 1; i <= M; ++ i)
    {
        for (j = 1; j <= M; ++ j)
            m[i][j] = ((LL) 1 << (j - 1) & a[N + 1][i]) ? 1 : 0;
        m[i][M + 1] = 0;
    }
    for (Gauss (N, M), i = 2; i <= N; ++ i)
        for (j = 1; j <= M; ++ j)
            b[i][j] = b[i - 2][j] ^ b[i - 1][j - 1] ^ b[i - 1][j + 1] ^ b[i - 1][j];

    for (i = 1; i <= N; ++ i)
        for (j = 1; j <= M; ++ j)
            if (j != M) printf ("%d ", b[i][j]);
            else printf ("%d\n", b[i][j]);

    return 0;
}
