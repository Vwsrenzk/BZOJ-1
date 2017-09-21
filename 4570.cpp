#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

void read (long long &now)
{
    register char word = getchar ();
    int temp = 0;
    for (now = 0; !isdigit (word); word = getchar ())
        if (word == '-')
            temp = 1;
    for (; isdigit (word); now = now * 10 + word - '0', word = getchar ());
    if (temp)
        now = -now;
}

#define INF 1e9

struct Point
{
    long long x, y;
    
    Point (long long __x, long long __y) : x (__x), y (__y) {}
    Point () {}
    
    bool operator < (const Point &now) const
    {
        return this->x == now.x ? this->y < now.y : this->x < now.x;
    }
    
    Point operator - (const Point &now) const
    {
        return Point (this->x - now.x, this->y - now.y);
    }
};

inline long long Cross (const Point &A, const Point &B)
{
    return A.x * B.y - A.y * B.x;
}

#define Max 1000250

inline double Calculate (const Point &now, const double &k)
{
    return k >= 0 ? INF : (double) now.x + now.y + - k * now.x - now.y / k;
}

inline double Get_point_k (const Point &now)
{
    return -sqrt ((double) now.y / now.x);
}

inline double Get_line_k (const Point &A, const Point &B)
{
    return (A.x ^ B.x) ? ((double)(A.y - B.y) / (double) (A.x - B.x)) : INF;
}

int Get_convex_Hull (Point *point, int N, Point *Stack)
{
    std :: sort (point + 1, point + N + 1);
    
    register int top = 0;
    for (int i = 1; i <= N; ++ i)
    {
        for (; top > 1 && Cross (Stack[top] - Stack[top - 1], point[i] - Stack[top - 1]) >= 0; -- top);
        Stack[++ top] = point[i];
    }
    return top;
}

Point yukari[Max], Stack[Max];

int main (int argc, char *argv[])
{
    register int i;
    int N;
    scanf ("%d", &N);
    for (i = 1; i <= N; ++ i)
        read (yukari[i].x), read (yukari[i].y);
    
    int M = Get_convex_Hull (yukari, N, Stack);
    
    if (M < 2)
    {
        printf ("%.4lf", Calculate (Stack[1], Get_point_k (Stack[1])));
        return 0;
    }
    double k, _k, __k, Answer = INF;
    
    k = Get_point_k (Stack[1]);
    __k = Get_line_k (Stack[1], Stack[2]);
    
    if (k >= __k)
        Answer = std :: min (Answer, Calculate (Stack[1], k));
    
    k = Get_point_k (Stack[M]);
    _k = Get_line_k (Stack[M - 1], Stack[M]);
    
    if (k <= _k)
        Answer = std :: min (Answer, Calculate (Stack[M], k));
    Answer = std :: min (Answer, Calculate (Stack[M], _k));
    
    for (i = 2; i < M; ++ i)
    {
        _k = Get_line_k (Stack[i - 1], Stack[i]);
        __k = Get_line_k (Stack[i], Stack[i + 1]);
        
        k = Get_point_k (Stack[i]);
        
        Answer = std :: min (Answer, Calculate (Stack[i], _k));
        if (k <= _k && k >= __k)
            Answer = std :: min (Answer, Calculate (Stack[i], k));
    }
    printf ("%.4lf", Answer);
    return 0;
}
