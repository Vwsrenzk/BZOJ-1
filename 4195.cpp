#include <algorithm>
#include <cstring>
#include <cstdio>
 
#define Max 200800
 
void read (int &now)
{
    now = 0;
    register char word = getchar ();
    while (word > '9' || word < '0')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}
 
int number[Max << 2];
 
struct Date
{
    int first;
    int second;
    int type;
};
 
struct Union_and_Find 
{
    int father[Max];
     
    void Clear (int N)
    {
        for (int i = 1; i <= N; i++)
            father[i] = i;
    }
     
    int Find (int x)
    {
        return father[x] == x ? x : father[x] = Find (father[x]);
    }
};
 
Union_and_Find Make;
 
Date date[Max];
 
int res[2][Max];
int Res_Cur;
 
int main (int argc, char *argv[])
{
    int T, N;
    read (T);
    int x, y;
    int size;
    while (T--)
    {
        read (N);
        Res_Cur = 0;
        Make.Clear (Max); 
        memset (number, 0, sizeof number);
        int Cur = 0;
        for (int i = 1; i <= N; i++)
        {
            read (x);
            date[i].first = x;
            number[++Cur] = x;
            read (x);
            number[++Cur] = x;
            date[i].second = x;
            read (date[i].type);
        }
         
        std :: sort (number + 1, number + 1 + Cur);
        size = std :: unique (number + 1, number + 1 + Cur) - number - 1;
        for (int i = 1; i <= N; i++)
        {
            date[i].first = std :: lower_bound (number + 1, number + 1 + size, date[i].first) - number;
            date[i].second = std :: lower_bound (number + 1, number + 1 + size, date[i].second) - number;
        }
        for (int i = 1; i <= N; i++)
            if (date[i].type)
            {
                x = Make.Find (date[i].first);
                y = Make.Find (date[i].second);
                if (x != y)
                    Make.father[x] = y; 
            }
            else
            {
                ++Res_Cur;
                res[0][Res_Cur] = date[i].first;
                res[1][Res_Cur] = date[i].second;
            }
        for (int i = 1; i <= Res_Cur; i++)
            if (Make.Find (res[0][i]) == Make.Find (res[1][i]))
            {
                puts ("NO");
                goto Continue;;
            }
        puts ("YES");
        Continue : 
            continue;
    }
    return 0;
}
