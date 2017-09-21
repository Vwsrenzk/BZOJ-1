#include <cstdio>
#include <cmath>
#include <set>
typedef long long LL;
#define Set std :: set <LL> 
 
int main ()
{
    LL N, a, b; scanf ("%lld", &N); register LL i, j;
    int L = sqrt (N); Set Answer;
    for (i = 1; i <= L; ++ i)
        if (N % i == 0)
        {
            a = i, b = N / i;
            for (j = 0; j <= N; j += b)
            {
                if ((j + 2) % a == 0 && j + 2 < N) Answer.insert (j + 1);
                if ((j - 2) % a == 0 && j - 2 >= 0) Answer.insert (j - 1);
            }
        }
    if (Answer.size () == 0) return printf ("None"), 0;
    for (Set :: iterator i = Answer.begin (); i != Answer.end (); ++ i)
        printf ("%lld\n", *i);  
    return 0;
}
