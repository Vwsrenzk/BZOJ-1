#include <cstdio>
#include <iostream>
#include <cmath>

#define rg register
typedef double flo;

struct vec
{
    flo x, y; vec (flo a = 0, flo b = 0) : x (a), y (b) { }

    vec operator + (const vec &rhs)
    { return vec (x + rhs.x, y + rhs.y); }

    vec operator - (const vec &rhs)
    { return vec (x - rhs.x, y - rhs.y); }

    vec operator * (const vec &rhs)
    { return vec (x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }

    vec operator /= (const flo &k)
    { return x /= k, y /= k, *this; }
};
#define Max 300005
const flo PI = acos (-1.0);
int rd[Max];
void DFT (vec *a, int N, int f = 1)
{
    rg int i, j, k; vec wn, w, x, y;
    for (i = 0; i < N; ++ i) if (rd[i] > i) std :: swap (a[i], a[rd[i]]);
    for (k = 1; k < N; k <<= 1)
    {
        wn = vec (cos (PI / k), f * sin (PI / k)); 
        for (j = 0; j < N; j += k << 1)
            for (w = vec (1, 0), i = 0; i < k; ++ i, w = w * wn)
                x = a[j + i], y = w * a[i + j + k], a[j + i] = x + y, a[i + j + k] = x - y;
    }
    if (f == -1) for (i = 0; i < N; ++ i) a[i] /= N;
}

vec f1[Max], f2[Max], g[Max], a[Max], b[Max];

int main (int argc, char *argv[])
{
    int N; scanf ("%d", &N); -- N; rg int i;
    for (i = 0; i <= N; ++ i)
        scanf ("%lf", &f1[i].x), f2[N - i] = f1[i];
    
    for (i = 1; i <= N; ++ i) g[i] = vec (1.0 / i / i, 0);

    int M = N << 1, L = 0;
    for (N = 1; N <= M; N <<= 1, ++ L);    
    
    for (i = 0; i < N; ++ i)    
        rd[i] = (rd[i >> 1] >> 1) | ((i & 1) << (L - 1));
    
    DFT (f1, N), DFT (f2, N), DFT (g, N);

    for (i = 0; i < N; ++ i) a[i] = f1[i] * g[i];

    for (i = 0; i < N; ++ i) b[i] = f2[i] * g[i];

    DFT (a, N, -1), DFT (b, N, -1);
    
    for (i = 0, M >>= 1; i <= M; ++ i)
        printf ("%lf\n", a[i].x - b[M - i].x);
    

    return 0;
}
