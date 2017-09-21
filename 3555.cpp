#include <algorithm>
#include <cstring>
#include <cstdio>

void read (int &now)
{
    register char word = getchar ();
    bool temp = false;
    for (now = 0; word < '0' || word > '9'; word = getchar ())
        if (word == '-')
            temp = true;
    for (; word >= '0' && word <= '9'; now = now * 10 + word - '0', word = getchar ());
    if (temp)
        now = -now;
}

#define Max 30006
char line[Max / 150];

unsigned long long Hash;
#define L 233

int Len;
unsigned long long mi[L];

unsigned long long Get_Hash (char *key)
{
    Hash = 0;
    for (int i = 0; i < Len; i ++)
        Hash = Hash * L + key[i];
    
    return Hash;
}

unsigned long long hash[Max * 210];

int main (int argc, char *argv[])
{
    int N, M, K;
    read (N);
    read (M);
    read (K);
    Len = M;
    register int i, j;
    mi[0] = 1;
    for (int i = 1; i <= L; i ++)
        mi[i] = mi[i - 1] * L;
        
    int cur = 0;
    unsigned long long res;
    for (i = 1; i <= N; i ++)
    {
        scanf ("%s", line);
        res = Get_Hash (line);
        
        for (j = 0; j < Len; j ++)
            hash[++ cur] = res - mi[Len - j - 1] * line[j];
    }

    std :: sort (hash + 1, hash + 1 + cur);
    long long Answer = 0;
    K = 1;
    for (i = 2; i <= cur; i ++)
        if (hash[i] == hash[i - 1])
            K ++;
        else
        {
            Answer += K * (K - 1) / 2;
            K = 1;
        }
    Answer += K * (K - 1) / 2;
    
    printf ("%lld", Answer);
    return 0;
}
