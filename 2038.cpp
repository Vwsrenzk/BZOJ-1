#include <algorithm>
#include <cstdio>
#include <cmath>

#define Max 500090

void read (int &now)
{
    now = 0;
    register char word = getchar ();
    while (word < '0' || word > '9')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}

int belong[Max];

struct Query_Data
{
    int l, r;
    
    int Id;
    
    bool operator < (const Query_Data &now) const
    {
        return belong[this->l] == belong[now.l] ? this->r < now.r : belong[this->l] < belong[now.l];
    }
};


int N, M;
long long Result;
long long count[Max];
int number[Max];

Query_Data query[Max];

inline void Updata (int now, bool type)
{
    if (type)
    {
        Result -= count[number[now]] * count[number[now]];
        count[number[now]] ++;
        Result += count[number[now]] * count[number[now]];
    }    
    else
    {
        Result -= count[number[now]] * count[number[now]];
        count[number[now]] --;
        Result += count[number[now]] * count[number[now]];
    }
}

long long Get_Gcd (long long a, long long b)
{
    return !b ? a : Get_Gcd (b, a % b);
}

long long Answer_up[Max], Answer_down[Max];

inline void Calculate (int now)
{
    register int l = query[now].l, r = query[now].r;
    Answer_up[query[now].Id] = Result - (r - l + 1);
    Answer_down[query[now].Id] = 1ll * (r - l) * (r - l + 1);
    register long long res = Get_Gcd (Answer_up[query[now].Id], Answer_down[query[now].Id]);
    Answer_up[query[now].Id] /= res;
    Answer_down[query[now].Id] /= res;    
}

int main (int argc, char *argv[])
{
    read (N);
    read (M);
    int K_Size = sqrt (N);
    for (int i = 1; i <= N; i ++)
    {
        belong[i] = (i + 1) / K_Size;
        read (number[i]);
    }
    for (int i = 1; i <= M; i ++)
    {
        read (query[i].l);
        read (query[i].r);
        query[i].Id = i;
    }
    std :: sort (query + 1, query + 1 + M);

    int l = 1, r = 0;
    for (int i = 1; i <= M; i ++)
    {
        while (l < query[i].l)
            Updata (l ++, false);
        while (l > query[i].l)
            Updata (-- l, true);
        while (r > query[i].r)
            Updata (r --, false);
        while (r < query[i].r)
            Updata (++ r, true);
        Calculate (i);
    }
    for (int i = 1; i <= M; i ++)
    {    
        printf ("%lld/", Answer_up[i]);
        printf ("%lld\n", Answer_down[i]);
    }
    return 0;
}
