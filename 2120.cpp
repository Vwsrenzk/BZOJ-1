#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define Max 1000005

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
bool visit[Max];
int L, R, Pos;

struct Query_Data 
{
    int l, r;

    int Id;
    int Last_Change;

    bool operator < (const Query_Data &now) const
    {
        if (belong[this->l] == belong[now.l])
            return this->r < now.r;
        return belong[this->l] < belong[now.l];
    }
};
Query_Data query[Max];

struct Change_Data
{
    int pos;
    int color;
    int Last;
};


Change_Data change[Max];

int res[Max], count[Max];
int number[Max];
int N, M;

int Result;

inline void Updata_Change (int now, bool type)
{
    if (type)
    {
        res[now] = number[change[now].pos];
        number[change[now].pos] = change[now].color;
        if (change[now].pos >= L && change[now].pos <= R)
        {
            count[res[now]] --;
            if (!count[res[now]])
                Result --;
            count[change[now].color]++;
            if (count[change[now].color] == 1)
                Result ++;
        }
    }
    else
    {
        number[change[now].pos] = res[now];
        if (change[now].pos >= L && change[now].pos <= R)
        {
            count[change[now].color] --;
            if (!count[change[now].color])
                Result --;
            count[res[now]] ++;
            if (count[res[now]] == 1)
                Result ++;
        }
    }
}


inline void Updata (int now, bool type)
{
    if (type)
    {
        if (count[number[now]] == 0)
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
    read (M);
    int K_Size = sqrt (N);
    int Query_Count = 0, Change_Count = 0;
    for (int i = 1; i <= N; i ++)
    {
        read (number[i]);
        belong[i] = (i + 1) / K_Size;
    }
    char type[5];
    int x, y;
    for (int i = 1; i <= M; i ++)
    {
        scanf ("%s", type);
        read (x);
        read (y);
        if (type[0] == 'R')
        {
            Change_Count ++;
            change[Change_Count].pos = x;
            change[Change_Count].color = y;
        }
        else
        {
            Query_Count ++;
            query[Query_Count].l = x;
            query[Query_Count].r = y;
            query[Query_Count].Id = Query_Count;
            query[Query_Count].Last_Change = Change_Count;
        }
    }
    std :: sort (query + 1, query + 1 + Query_Count);
    L = 1, R = 0; 
    Pos = 0;
    for (int i = 1; i <= Query_Count; i ++)
    {
        while (Pos < query[i].Last_Change)
            Updata_Change (++ Pos, true);
        while (Pos > query[i].Last_Change)
            Updata_Change (Pos -- , false);
        while (L < query[i].l)
            Updata (L ++, false);
        while (L > query[i].l)
            Updata (-- L, true);
        while (R < query[i].r)
            Updata (++ R, true);
        while (R > query[i].r)
            Updata (R --, false);
        Answer[query[i].Id] = Result;
    }
    for (int i = 1; i <= Query_Count; i ++)
        printf ("%d\n", Answer[i]);
    return 0;
}
