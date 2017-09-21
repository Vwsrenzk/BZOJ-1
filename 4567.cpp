#include <cstdio>
#include <algorithm>
#include <cstring>
#define Max 100008
#define L 26
int N;
char line[Max * 10];
typedef long long LL;
 
int trie[Max * 10][L], T_C = 1;
bool is[Max * 10];
struct E
{
    E *n; int to;
};
E *list[Max * 20], poor[Max], *Ta = poor;
void Dfs (int now, int Father)
{
    if (is[now]) 
    {
        ++ Ta, Ta->to = now, Ta->n = list[Father], list[Father] = Ta;
        Father = now;
    }
    for (int i = 0; i < L; ++ i) 
        if (trie[now][i]) 
            Dfs (trie[now][i], Father);
}
int size[Max * 10];
 
void Re_Dfs (int now)
{
    size[now] = 1;
    for (E *e = list[now]; e; e = e->n)
        Re_Dfs (e->to), size[now] += size[e->to];
}
int dfn[Max * 10], top, C, Stack[Max];
LL Answer;
inline bool Comp (int a, int b)
{
    return size[a] < size[b];
}
void Get_Answer (int now)
{
    dfn[now] = ++ C; int pos = top + 1;
    for (E *e = list[now]; e; e = e->n)
        Stack[++ top] = e->to;
    if (top < pos) return ;
    std :: sort (Stack + pos, Stack + top + 1, Comp);
    for (int i = pos; i <= top; ++ i)
        Get_Answer (Stack[i]), Answer += dfn[Stack[i]] - dfn[now];
    top = pos - 1;
}
 
int Main ()
{
    scanf ("%d", &N); register int i, j;
    int Id, x, now, Len;
    for (i = 1; i <= N; ++ i)
    {
        scanf ("%s", line); Len = strlen (line);
        for (j = Len - 1, now = 1; j >= 0; -- j)
        {
            Id = line[j] - 'a';
            if (trie[now][Id] == 0)
                trie[now][Id] = ++ T_C;
            now = trie[now][Id];
        }   
        is[now] = true;
    }   
    Dfs (1, 1), Re_Dfs (1), Get_Answer (1);
    printf ("%lld", Answer);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
