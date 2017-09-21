#include <cstdio>
#include <iostream>

void read (long long &now)
{
    register char word = getchar ();
    for (now = 0; !isdigit (word); word = getchar ());
    for (; isdigit (word); now = now * 10 + word - '0', word = getchar ());
}

#define Max 3333
long long data_1[Max], data_2[Max];
long long N, M;
long long number[Max];
int Head, Tail;
int Queue[Max];
long long *dp = data_1, *data = data_2;

double make (int x, int y)
{
    return double (data[x] - data[y] + number[x] * number[x] - number[y] * number[y]) / (number[x] - number[y]);  
}

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    register int i;
    for (i = 1; i <= N; ++ i)
    {
        read (number[i]);
        number[i] += number[i - 1];
    }
    
    for (i = 1; i <= N; ++ i)
        dp[i] = number[i] * number[i];
        
    register int j;
    for (j = 1; j < M; ++ j)
    {
        Head = Tail = 1;
        std :: swap (dp, data);
        Queue[Head] = 0;
        for (i = 1; i <= N; ++ i)
        {
            for (; Head < Tail && make (Queue[Head], Queue[Head + 1]) < 2 * number[i]; ++ Head);

            dp[i] = data[Queue[Head]] + (number[i] - number[Queue[Head]]) * (number[i] - number[Queue[Head]]);
            
            for (; Head < Tail && make (Queue[Tail], Queue[Tail - 1]) > make(Queue[Tail], i); -- Tail);
            Queue[++ Tail] = i;
        }
    }
    
    printf ("%lld", M * dp[N] - number[N] * number[N]);
    return 0;
}
