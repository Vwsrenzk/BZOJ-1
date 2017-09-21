#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>

const int BUF = 10000020;
char Buf[BUF], *buf = Buf;

void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}

#define Max 200005

int sa[Max], __rank[Max], height[Max];
int str_1[Max], str_2[Max];
int c[Max];

inline void Swap (int *&x, int *&y)
{
    int *now = x;
    x = y;
    y = now;
}

inline int min (int a, int b)
{
    return a < b ? a : b;
}

void D ()
{
    putchar ('\n');
    for (int i = 1; i <= 10; i ++)
        printf ("%d ", sa[i]);
            putchar ('\n');}
void Build_Sa (int *line, int N, int M)
{
    static int *x = str_1, *y = str_2; register int i, pos;
    for (i = 0; i < M; c[i ++] = 0);
       for (i = 0; i < N; c[x[i] = line[i]] ++, ++ i);
    for (i = 1; i < M; c[i] += c[i - 1], ++ i);
    for (i = N - 1; i >= 0; sa[-- c[x[i]]] = i, i --);
    for (int j = 1; pos < N; j <<= 1, M = pos)
    {
        for (i = N - j, pos = 0; i < N; y[pos ++] = i ++);
        for (i = 0; i < N; ++ i) if (sa[i] >= j) y[pos ++] = sa[i] - j;
        for (i = 0; i < M; c[i ++] = 0);
        for (i = 0; i < N; ++ c[x[y[i]]], ++ i);
        for (i = 0; i < M; c[i] += c[i - 1], ++ i);
        for (i = N - 1; i >= 0; sa[-- c[x[y[i]]]] = y[i --]);
        Swap (x, y), pos = 1, x[sa[0]] = 0;
        for (i = 1; i < N; ++ i)
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j] ? pos - 1 : pos ++;
    }
    int j;
    for (i = 1; i < N; __rank[sa[i]] = i, ++ i);
    for (i = 0, pos = 0; i < N - 1; height[__rank[i ++]] = pos)
        for (pos ? pos -- : 0, j = sa[__rank[i] - 1]; line[i + pos] == line[j + pos]; ++ pos);
}

inline int max (int a, int b)
{
    return a > b ? a : b;
}
int number[Max], level[Max];

int st[Max][20];
int Stack[Max], data[Max];

int value[Max];
std :: map<int,int>hash;  

int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N;
    read (N);
    register int i;
    for (i = 0; i < N; ++ i)
        read (number[i]), level[i] = number[i];
        
    int Size = 0;
    for (i = 0; i < N; ++ i)
        if (hash.find (number[i]) == hash.end ())
            hash[level[i]] = ++ Size;
    for (i = 0; i < N; ++ i)
        level[i] = hash[level[i]];
        
    Build_Sa (level, N + 1, Size + 1);
    for (i = 1; i <= N; st[i][0] = height[i], ++ i);
    for (int j = 1; j <= 17; ++ j)
        for (i = 1; i + (1 << j - 1) <= N; ++ i)
            st[i][j] = min (st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
            
    int top = 0, res, pos, l;

    for (i = 1; i <= N; ++ i)
    {
        for (; sa[Stack[top]] > sa[i] && top; -- top);
        res = Stack[top] + 1;
        l = (int) log2 (i - res + 1);
        
        data[i] = min (st[res][l], st[i - (1 << l) + 1][l]);
        Stack[++ top] = i;
    }
    for (i = N, Stack[top = 0] = N + 1; i; -- i)
    {
        for (; sa[Stack[top]] > sa[i] && top; -- top);
        res = Stack[top];
        l = (int) log2 (res - i);
        
        data[i] = max (data[i], min (st[i + 1][l], st[res - (1 << l) + 1][l]));
        Stack[++ top] = i;
    }
    
    for (i = 1; i <= N; ++ i)
        value[data[i] + sa[i]] ++;

    long long now = 0, Answer = 0;
    for (i = 0; i < N; ++ i)
    {
        now += value[i];
        Answer += now;
        printf ("%lld\n", Answer);
    }


    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
