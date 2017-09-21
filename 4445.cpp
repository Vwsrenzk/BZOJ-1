#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
 
const int BUF = 12312312;
char Buf[BUF], *buf = Buf;
 
#define flo double 
inline void read (int &now)
{
    bool temp = false;
    for (now = 0; !isdigit (*buf); ++ buf)
        if (*buf == '-') temp = true;
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
    if (temp) now = -now;
}
#define Max 100005
 
struct P { flo x, y; };
P p[Max], _q[Max];
struct L 
{ 
    P u, v; 
    flo a;
    inline void Cal () { a = atan2 (v.y, v.x); }
};
L q[Max], r[Max];
P operator + (P a, P b) { return (P) { a.x + b.x, a.y + b.y }; }
P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y }; }
P operator * (flo a, P b) { return (P) { a * b.x, a * b.y }; }
flo Cross (P a, P b) { return a.x * b.y - a.y * b.x; }
flo Cal (P a, L b) { return Cross (a - b.u, b.v); }
P Over (L a, L b)
{
    return a.u + Cross (a.u - b.u, b.v) / Cross (b.v, a.v) * a.v;
}
bool operator < (L a, L b)
{
    return a.a < b.a || a.a == b.a && Cal (a.u, b) < 0; 
}
void Insert (int i, int j)
{
    flo a = p[0].y - p[i].y - p[1].y + p[j].y;
    flo b = p[1].x - p[j].x - p[0].x + p[i].x;
    flo c = Cross (p[0], p[1]) - Cross (p[i], p[j]);
    r[i].u.x = b ? 0 : -c / a, r[i].u.y = b ? -c / b : 0;
    r[i].v = (P) {-b, a};
}
 
flo Cal_area (P *p, int N)
{
    flo res = Cross (p[N - 1], p[0]);
    for (register int i = 1; i < N; ++ i)
        res += Cross (p[i - 1], p[i]);
    return res;
}
 
int Main ()
{
    fread (buf, 1, BUF, stdin); int N;
    read (N); register int i; int x;
    for (i = 0; i < N; ++ i)
        read (x), p[i].x = x, read (x), p[i].y = x;
    r[0].u = p[0], r[0].v = p[1] - p[0];
    for (i = 1; i < N; ++ i) Insert (i, (i + 1) % N);
    for (i = 0; i < N; ++ i) r[i].Cal ();
    std :: sort (r, r + N); int L = 0, R = -1;
    for (i = 0; i < N; ++ i)
    {
        for (; L < R && Cal (_q[R], r[i]) > 0; -- R);    
        for (; L < R && Cal (_q[L + 1], r[i]) > 0; ++ L);
        if (L > R || r[i].a != q[R].a)
            q[++ R] = r[i], _q[R] = Over (q[R], q[R - 1]);
    }
    for (; L < R && Cal (_q[R], q[L]) > 0; -- R);
    _q[L] = Over (q[L], q[R]);
    flo Answer = Cal_area (_q + L, R - L + 1) / Cal_area (p, N);
    printf ("%.4lf", Answer);
 
    return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
