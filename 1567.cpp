#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 60
int a[Max][Max], b[Max][Max];
int main (int argc, char *argv[])
{
    int N; read (N); rg int i, j, k, x, y, z, c;
    for (i = 1; i <= N; ++ i) for (j = 1; j <= N; ++ j) read (a[i][j]);
    for (i = 1; i <= N; ++ i) for (j = 1; j <= N; ++ j) read (b[i][j]);
    for (i = N; i >= 1; -- i)
        for (j = 1; j <= N - i + 1; ++ j)
            for (k = 1; k <= N - i + 1; ++ k)
                for (x = 1; x <= N - i + 1; ++ x)
                    for (y = 1; y <= N - i + 1; ++ y)
                    {
                        for (z = 0; z < i; ++ z)
                            for (c = 0; c < i; ++ c)
                                if (a[j + z][k + c] != b[x + z][y + c]) goto Here;
                        printf ("%d", i); return 0;
                        Here : continue;
                    }    
    printf ("0"); return 0;
}
