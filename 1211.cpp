#include <cstdio>
#include <iostream>
#define rg register
typedef long long LL;
#define Max 200
inline void read (LL &n)
{
	rg char c = getchar ();
	for (n = 0; !isdigit (c); c = getchar ());
	for (; isdigit (c); n =	n * 10 + c - '0', c = getchar ());
}
LL d[Max], J[Max];
int main (int argc, char *argv[])
{
	LL Answer = 1, N; rg int i, j; LL s = 0; read (N);
	for (i = 1; i <= N; ++ i)
	{
		read (d[i]), s += d[i] - 1;
		if (d[i] == 0 && N != 1) return printf ("0"), 0;
		for (j = 2, J[i] = 1; j <= d[i] - 1; ++ j) J[i] *= j;
	}
	if (s != N - 2) return printf ("0"), 0; 
	for (i = j = 1; i <= N - 2; ++ i)
	{
		Answer *= i; if (j > N) continue;
		if (Answer % J[j] == 0) Answer /= J[j ++];
	}
	printf ("%lld", Answer); return 0;
}
