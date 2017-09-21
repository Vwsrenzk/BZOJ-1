#include <cstdio>
#include <iostream>
 
#define INF 1e9
 
inline void read (int &now)
{
    register char c = getchar (); int temp = 0;
    for (now = 0; !isdigit (c); c = getchar ());
    for (; isdigit (c); now = now * 10 + c - '0', c = getchar ());
}
 
using namespace std;
#define Max 2020
 
int N, M, V, E;
 
double map[Max][Max];
int room[Max], other[Max];
double k[Max];
double dp[Max][Max][2];
 
int Main ()
{
 
    read (N), read (M), read (V), read (E);
 
    register int i, j;
     
    for (i = 1; i <= N; ++ i)
        read (room[i]);
    for (i = 1; i <= N; ++ i)
        read (other[i]);
    for (i = 1; i <= N; ++ i)
        scanf ("%lf", &k[i]);
 
    int x, y, z;
 
    for (i = 1; i <= V; ++ i)
        for (j = 1; j <= V; ++ j)
            if (i == j)    map[i][i] = 0;
            else map[i][j] = INF;
 
    for (i = 1; i <= E; ++ i)
    {
        read (x), read (y), read (z);
        if (x == y) continue;
        map[x][y] = min (map[x][y], (double)z);
        map[y][x] = map[x][y];
    }
 
    int pos;
    for (pos = 1; pos <= V; ++ pos)
        for (i = 1; i <= V; ++ i)
            for (j = 1; j <= V; ++ j)
                map[i][j] = min (map[i][j], map[i][pos] + map[pos][j]);
 
    int L; double res;
    for (i = 0; i <= N; ++ i)
        for (j = 0; j <= M; ++ j)
            dp[i][j][0] = dp[i][j][1] = INF;
    dp[1][0][0] = 0, dp[1][1][1] = 0;
 
    for (i = 2; i <= N; ++ i)
    {    
        dp[i][0][0] = dp[i - 1][0][0] + map[room[i - 1]][room[i]];
        for (j = 1, L = min (M, i); j <= L; ++ j)
        {
            dp[i][j][0] = min (dp[i - 1][j][0] + map[room[i - 1]][room[i]], dp[i - 1][j][1] + map[room[i - 1]][room[i]] * (1.0 - k[i - 1]) + map[other[i - 1]][room[i]] * k[i - 1]);
            dp[i][j][1] = dp[i - 1][j - 1][0] + map[room[i - 1]][room[i]] * (1.0 - k[i]) + map[room[i - 1]][other[i]] * k[i];
            res = dp[i - 1][j - 1][1] + map[room[i - 1]][room[i]] * (1.0 - k[i - 1]) * (1.0 - k[i]);
            res += map[other[i - 1]][room[i]] * k[i - 1] * (1.0 - k[i]);
            res += map[room[i - 1]][other[i]] * (1.0 - k[i - 1]) * k[i];
            res += map[other[i - 1]][other[i]] * k[i - 1] * k[i];
            dp[i][j][1] = min (dp[i][j][1], res);
        }
    }
 
    double Answer = INF;
    for (i = 0; i <= M; ++ i)
        Answer = min (Answer, min (dp[N][i][0], dp[N][i][1]));
    printf ("%.2lf", Answer);
     
    fclose (stdin);
    fclose (stdout);    
    return 0;
}
 
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
