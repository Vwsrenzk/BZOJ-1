#include <cstdio>
#include <cstring>
 
 
void read (long long &now)
{
    register char word = getchar ();
    for (now = 0; word < '0' || word > '9'; word = getchar ());
    for (; word >= '0' && word <= '9'; now = now * 10 + word - '0', word = getchar ());
}
 
long long N;
long long Mod;
 
struct Martix
{
     
    static const int _L = 3;
    long long data[_L][_L];
     
    inline void Fill ()
    {
        memset (this->data, 0, sizeof this->data);
        this->data[1][0] = this->data[2][0] = 1;
        this->data[1][1] = this->data[2][1] = 1;
        this->data[2][2] = 1;
    }
     
    Martix operator * (const Martix &now) const
    {
        Martix res;
         
        for (register int i = 0, j, k; i < _L; i ++)
            for (j = 0; j < _L; j ++)
            {
                res.data[i][j] = 0;
                for (k = 0; k < _L; k ++)
                    res.data[i][j] = (res.data[i][j] + this->data[i][k] * now.data[k][j]) % Mod;
            }
        return res;
    }
};
 
Martix operator ^ (Martix now, long long P)
{
    Martix res;
    for (register int i = 0, j; i < Martix :: _L; i ++)
        for (j = 0; j < Martix :: _L; j ++)
            res.data[i][j] = (i == j);
    for (; P; P >>= 1)
    {
        if (P & 1)
            res = res * now;
        now = now * now;
    }
    return res;
}
 
Martix Answer;
 
inline void Solve (long long t, long long P)
{
    Martix res;
    res.Fill ();
    res.data[0][0] = t % Mod;
    Answer = Answer * (res ^ (P - t / 10 + 1));
}
 
int main (int argc, char *argv[])
{
    read (N);
    read (Mod);
     
    for (int i = 0; i < Martix :: _L; i ++)
        Answer.data[i][i] = 1;
    long long T = 10;
    for (; N >= T; Solve (T, T - 1), T *= 10);
     
    Solve (T, N);
    printf ("%lld", Answer.data[2][0]);
    return 0;
}
