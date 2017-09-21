#include <cstdio>
#include <iostream>
#define rg register
typedef long long LL;
void read (LL &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Mod 100003
LL P (LL x, LL p)
{
    LL r = 1;
    for (; p; x = x * x % Mod, p >>= 1)
        if (p & 1) r = r * x % Mod;
    return r;
}
int main (int argc, char *argv[]) 
{
    LL M, N; read (M), read (N); rg int i, j;   
    printf ("%lld", (Mod + P (M, N) % Mod - M * P (M - 1, N - 1) % Mod) % Mod); return 0;
}
