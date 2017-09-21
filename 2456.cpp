#include <cstdio>

#define INF 1e7

void read (int &now)
{
    now = 0;
    register char word = getchar ();
    bool flag = false;
    while (word < '0' || word > '9')
    {
        if (word == '-')
            flag = true;
        word = getchar ();
    }
    while (word <= '9' && word >= '0')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
    if (flag)
        now = -now;
}

int N;
int Count;

int main (int argc, char *argv[])
{
    read (N);
    Count = 0;
    int Answer = INF;
    int x;
    for (int i = 1; i <= N; i++)
    {
        read (x);
        if (Answer != x)
        {
            Count--;
            if (Count <= 0)
            {
                Count = 1;
                Answer = x;
            }
        }
        else
            Count++;
    }
    printf ("%d", Answer);
    return 0;
}
