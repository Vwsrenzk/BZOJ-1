#include <cstdio>
#include <cstring>
#define rg register
#define Max 5000
int f[2][Max], s, Answer, N, Mod;
int main (int argc, char *argv[])
{
    scanf ("%d%d", &N, &Mod); f[1][1] = 1; rg int i, j;
    for (i = 2; i <= N; ++ i)
    {
        memset (f[i & 1], 0, sizeof f[0]);
        for (j = i - 1, s = 0; j; -- j)
            s = (s + f[i & 1 ^ 1][i - j]) % Mod, f[i & 1][j] = s;
    }
    for (j = 1; j <= N; ++ j) Answer = (Answer + f[N & 1][j]) % Mod;
    printf ("%d", (Answer << 1) % Mod); return 0;
}
