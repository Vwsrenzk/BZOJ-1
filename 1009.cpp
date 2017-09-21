#include <cstring>
#include <cstdio>
 
#define Max 100
 
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
 
int Mod;
int N, M;
 
 
char line[Max];
 
struct Martix_Data
{
    int data[Max][Max];
     
    Martix_Data operator * (const Martix_Data &now) const
    {
        Martix_Data res;
         
        for (register int i = 0; i < M; i ++)
            for (register int j = 0; j < M; j ++)
            {
                res.data[i][j] = 0;
                 
                for (register int k = 0; k < M; k ++)
                    res.data[i][j] = (res.data[i][j] + this->data[i][k] * now.data[k][j]) % Mod;
            }
             
        return res;
    }
     
};
 
Martix_Data S;
Martix_Data Answer;
 
Martix_Data operator ^ (Martix_Data now, int P)
{
    Martix_Data res = Answer;
     
    for (; P; now = now * now, P >>= 1)
        if (P & 1)
            res = now * res;
     
    return res;
}
  
int next[Max];
 
void Kmp_Prepare (char *__line)
{
     
    int pos = 0;
    for (int i = 2; i <= M; i ++)
    {
        for (; pos && __line[pos + 1] != __line[i]; )
            pos = next[pos];
         
        if (__line[pos + 1] == __line[i])
            pos ++;
        next[i] = pos;
    }
     
    for (int i = 0, pos; i < M; i ++)
        for (char j = '0'; j <= '9'; j ++)
        {
             
            for (pos = i; pos && __line[pos + 1] != j; )
                pos = next[pos];
                 
            if (j == __line[pos + 1])
                S.data[i][pos + 1] ++;
            else
                S.data[i][0] ++;
        }
}
 
int main (int argc, char *argv[])
{
    read (N);
    read (M);
    read (Mod);
     
    scanf ("%s", line + 1);
     
    Kmp_Prepare (line);
 
    for (int i = 0; i < M; i ++)
        Answer.data[i][i] = 1;
         
    Answer = S ^ N;
     
    int Total = 0;
    for (int i = 0; i < M; i ++)
        Total = (Total + Answer.data[0][i]) % Mod;
         
    printf ("%d", Total);
 
    return 0;
}
