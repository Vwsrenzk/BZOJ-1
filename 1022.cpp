#include <cstdio>
#include <iostream>

#define rg register
inline void read (int &n)
{
    rg char c = getchar ();
    for (n = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}

int main (int argc, char *argv[])
{
    int T, N, x, sg; bool f; rg int i;
    read (T);
    for (; T; -- T)
    {
        read (N); f = false, sg = 0;
        for (i = 1; i <= N; ++ i)
        {
            read (x);
            if (x != 1) f = true;
            sg ^= x;
        }
        if ((!f && !sg) || (sg && f)) puts ("John");
        else puts ("Brother");
    }    

    return 0;
}
