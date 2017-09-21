#include <cstdio>
#include <iostream>

const int BUF = 10000010;
char Buf[BUF], *buf = Buf;

void read (int &now)
{
    int temp = 0;
    for (now = 0; !isdigit (*buf); ++ buf)
        if (*buf == '-')
            temp = 1;
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
    if (temp)
        now = -now;
}

#define Max 100007

int number[Max];

long long Maxn;
inline int abs (int x)
{
    return x < 0 ? -x : x;
}

int N, K;
int Check (long long key)
{
    int Count = 0;
    register long long res = 0;
    for (int i = 1; i <= N; ++ i)
    {
        res += number[i];
        if (res < 0)    res = 0;
        if (res >= key)
        {
            res = 0;
            ++ Count;
        }
    }
    return Count;
}

int main (int argc, char *argv[])
{
    fread (buf, 1, BUF, stdin);
    read (N);
    read (K);

    for (int i = 1; i <= N; ++ i)
        read (number[i]), Maxn += abs (number[i]);
    
    register long long l, r, Mid;
    long long Answer_Min = -1, Answer_Max = -1;

    for (l = 1, r = Maxn; l <= r; )
    {
        Mid = l + r >> 1;
        if (Check (Mid) <= K)
        {    
            r = Mid - 1;
            Answer_Min = Mid;
        }
        else
            l = Mid + 1;
    }
    
    for (l = 1, r = Maxn; l <= r; )
    {
        Mid = l + r >> 1;
        if (Check (Mid) >= K)
        {
            l = Mid + 1;
            Answer_Max = Mid;
        }
        else 
            r = Mid - 1;
    }
    if (Check (Answer_Min) != K || Check (Answer_Max) != K)
        return printf ("-1"), 0;
    printf ("%lld %lld", Answer_Min, Answer_Max);

    return 0;
}
