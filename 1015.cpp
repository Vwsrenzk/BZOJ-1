#include <cstdio>
#include <iostream>
#define Max 400004
#define rg register
struct E { E *n; int v; } *list[Max], poor[Max], *Ta = poor;
int f[Max], C, p[Max], s[Max]; bool is[Max];
inline void read (int &n)
{
	rg char c = getchar ();
	for (n = 0; !isdigit (c); c = getchar ());
	for (; isdigit (c); n = n * 10 + c - '0', c = getchar ()); ++ n;
}
inline int Find (int x) { return f[x] == x ? x : f[x] = Find (f[x]); }
int main (int argc, char *argv[])
{
	int N, M, n, x, y, V, K; read (N), read (M); rg int i, j; -- N, -- M; E *e;
	for (i = 0; i < M; ++ i)
	{
		read (x), read (y);
		++ Ta, Ta->n = list[x], list[x] = Ta, Ta->v = y;
		++ Ta, Ta->n = list[y], list[y] = Ta, Ta->v = x;
	}
	read (K); -- K; C = N - K; for (i = 1; i <= N; f[i] = i, ++ i);
	for (i = 1; i <= K; ++ i) read (p[i]), is[p[i]] = true; 
	for (i = 1; i <= N; ++ i)
	{
		if (is[i]) continue;
		for (e = list[i]; e; e = e->n)
			if (!is[(V = e->v)])
			{
				x = Find (i), y = Find (V);
				if (x != y) f[x] = y, -- C;
			}
	}
	for (i = K, s[K + 1] = C; i >= 1; -- i)
	{
		n = p[i], is[n] = false; ++ C;
		for (e = list[n]; e; e = e->n)
			if (!is[(V = e->v)])
			{
				x = Find (n), y = Find (V);
				if (x != y) f[x] = y, -- C;
			}
		s[i] = C;
	}
	for (i = 1; i <= K + 1; ++ i) printf ("%d\n", s[i]); return 0;
}
