#include <algorithm>
#include <cstdio>
#include <cmath>

#define Max 1000001

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
        if (belong[now.l] == belong[this->l])
            return this->r < now.r;
        else
            return belong[this->l] < belong[now.l];
    }
};


int N, M;

int number[Max];
Query_Data query[Max];

int count[Max];

int Result;

bool visit[Max];

inline void Updata (int now, bool type) 
{
    if (type)
    {
        if (!count[number[now]])
            Result ++;
        count[number[now]] ++;
    }
    else
    {
        if (count[number[now]] == 1)
            Result --;
        count[number[now]] --;
    }
}

int Answer[Max];

int main (int argc, char *argv[])
{
    read (N);
    int Size = sqrt (N);
    for (int i = 1; i <= N; i ++)
    {
        read (number[i]);
        belong[i] = (i + 1) / Size;
    }
    read (M);
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
        if (l < query[i].l)
            for (int pos = l; pos < query[i].l; pos ++)
                Updata (pos, false);
        else if (l >= query[i].l)
            for (int pos = l - 1; pos >= query[i].l; pos --)
                Updata (pos, true);
        if (r > query[i].r)
            for (int pos = r; pos > query[i].r; pos--)
                Updata (pos, false);
        else if (r <= query[i].r)
            for (int pos = r + 1; pos <= query[i].r; pos++)
                Updata (pos, true);
        l = query[i].l;
        r = query[i].r;
        Answer[query[i].Id] = Result;
    }
    for (int i = 1; i <= M; i ++)
        printf ("%d\n", Answer[i]);
    return 0;
}
