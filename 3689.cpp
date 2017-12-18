#include <cstdio>
#include <iostream>
#include <queue>
#define rg register
struct IO
{
    static const int BUF = 12323233;
    char p[BUF], *s, *t, e[BUF]; int a[25];
    IO () : s (p), t (e) { fread (s, 1, BUF, stdin); }
    ~IO () { fwrite (e, 1, t - e, stdout); }
    operator int ()
    {
        rg int j = 1, v = 0;
        for (; *s < 48; j = *s ++ ^ 45);
        do v = v * 10 + *s ++ - 48; while (*s >= 48);
        return j ? v : -v;
    }
    
    void pt (int v)
    {
        static int *q = a;
        if (!v) *t ++ = 48;
        else 
        {
            if (v < 0) *t ++ = 45, v *= -1;
            
            for (; v; *q ++ = v % 10 + 48, v /= 10);
            for (; q != a; *t ++ = *-- q);
        }
        *t ++ = ' ';
    }
} ip;
        
#define Max 200203
int tr[Max * 20][2], TC, s[Max * 20];

void In (int key)
{
    int n = 0;
    for (rg int t, i = 30; i >= 0; -- i)
    {
        t = (key >> i) & 1;
        if (!tr[n][t]) tr[n][t] = ++ TC;
        n = tr[n][t], ++ s[n];
    }
}

int Ask (int key, int k)
{
    int res = 0, n = 0;
    for (rg int i = 30, t; i >= 0; -- i)
    {
        t = (key >> i) & 1;
        if (s[tr[n][t]] >= k) n = tr[n][t];
        else k -= s[tr[n][t]], n = tr[n][t ^ 1], res += (1 << i);
    }
    return res;
}
struct D 
{ 
    int key, rk, x; 
    
    D (int a = 0, int b = 0, int c = 0) : key (a), rk (b), x (c) {}
     
    bool operator < (const D &rhs) const 
    { return x > rhs.x; }
};

int a[Max];
std :: priority_queue <D> Q;

int main (int argc, char *argv[])
{
    int N = ip, K = ip; rg int i; D n;
    
    for (i = 1; i <= N; ++ i) a[i] = ip, In (a[i]);
    
    for (i = 1; i <= N; ++ i) Q.push (D (a[i], 2, Ask (a[i], 2)));
    
    for (i = 1; i < (K << 1); ++ i)
    {
        n = Q.top (), Q.pop ();
        if (i & 1) ip.pt (n.x);
        ++ n.rk, n.x = Ask (n.key, n.rk), Q.push (n);
    }
    return 0;
}
