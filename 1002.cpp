#include <cstdio>
#include <iostream>
 
#define L 101
struct Int { int c[L], l; };
 
Int operator - (Int A, Int B) 
{
    register int i; A.c[1] += 2;
    for (i = 1; A.c[i] >= 10; ++ i)
        A.c[i] %= 10, ++ A.c[i + 1];
    for (i = 1; i <= A.l; ++ i)
    {
        A.c[i] -= B.c[i];
        if (A.c[i] < 0)
            A.c[i] += 10, -- A.c[i + 1];
    }
    for (; !A.c[A.l]; -- A.l);
    return A;
}
 
Int operator * (Int A, int b)
{
    register int i;
    for (i = 1; i <= A.l; ++ i) A.c[i] *= b;
    for (i = 1; i <= A.l; ++ i)
        A.c[i + 1] += A.c[i] / 10, A.c[i] %= 10;
    if (A.c[A.l + 1]) ++ A.l;
    return A;
}
#define Max 101
Int f[Max];
 
int Main ()
{
    int N; register int i; scanf ("%d", &N);
    f[1].l = f[2].l = 1; f[1].c[1] = 1, f[2].c[1] = 5;
    for (i = 3; i <= N; ++ i)
        f[i] = (f[i - 1] * 3) - f[i - 2];
    for (i = f[N].l; i; -- i)
        printf ("%d", f[N].c[i]);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
