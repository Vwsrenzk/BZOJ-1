#include <cstdio>
#include <iostream>
#include <cstring>

const int BUF = 12312312;
char Buf[BUF], *buf = Buf;

#define Mod 20170408

inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}

#define Max 20000007
#define L 100
struct Matrix
{
    int c[L][L];
    Matrix () { memset (c, 0, sizeof c); }

    Matrix operator * (const Matrix &now) const
    {
        Matrix res;
        for (register int i = 0, j, k; i < L; ++ i)
            for (k = 0; k < L; ++ k)
                if (this->c[i][k])
                    for (j = 0; j < L; ++ j)
                        res.c[i][j] = (res.c[i][j] + 1LL * this->c[i][k] * now.c[k][j]) % Mod;
        return res;    
    }
};

int operator ^ (Matrix A, int p)
{
    Matrix res; res.c[0][0] = 1;
    for (; p; A = A * A, p >>= 1)
        if (p & 1)
            res = res * A;
    return res.c[0][0];
}

Matrix A;
int prime[Max];
bool is[Max];
int C;

void Euler (const int N)
{
    is[1] = true;
    for (register int i = 2, j; i <= N; ++ i)
    {
        if (!is[i]) prime[++ C] = i;
        for (j = 1; i * prime[j] <= N && j <= C; ++ j)
        {
            is[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

int data[Max];

int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N, M, K; read (N), read (M), read (K);
    Euler (Max - 7); register int i, j;

    for (i = 1; i <= M; ++ i) ++ data[i % K];
    for (i = 0; i < K; ++ i) 
        for (j = 0; j < K; ++ j)
            A.c[i][(i + j) % K] = data[j] % Mod;
    int Answer = A ^ N; memset (A.c, 0, sizeof A.c);
    memset (data, 0, sizeof data);
    for (i = 1; i <= M; ++ i)
        if (is[i]) ++ data[i % K];
    for (i = 0; i < K; ++ i)
        for (j = 0; j < K; ++ j)
            A.c[i][(i + j) % K] = data[j] % Mod;
    Answer -= A ^ N;

    printf ("%d", (Answer + Mod) % Mod);
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
