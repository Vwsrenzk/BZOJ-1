#include <cstdio>
#define rg register
#include <iostream>
#include <cstring>
#define INF 1e8
inline void read (int &n)
{
	rg char c = getchar ();
	for (n = 0; !isdigit (c); c = getchar ());
	for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
#define Max 55
int N, M, p[Max], l[Max], m[Max], f[Max][Max * 2][Max * 40], g[Max][Max * 40], h[Max][Max * 40], deg[Max];
int T, C, s;
struct E { E *n; int v, d; } *list[Max], poor[Max * 200], *Ta = poor;
inline void In (int u, int v, int d)
{ ++ Ta, Ta->v = v, Ta->n = list[u], list[u] = Ta, Ta->d = d, ++ deg[v]; }
inline void cmax (int &x, int y) { if (y > x) x = y; }
inline void cmin (int &x, int y) { if (y < x) x = y; }
void Dp (int n)
{
	rg int i, j, k; E *e; int V, r;
	if (!list[n])
	{
		for (cmin (l[n], M / m[n]), i = 0; i <= l[n]; ++ i)
			for (j = i; j <= l[n]; ++ j)
				f[n][i][j * m[n]] = (j - i) * p[n];
		return ;
	}
	for (l[n] = INF, e = list[n]; e; e = e->n)
		Dp (V = e->v), cmin (l[n], l[V] / e->d), m[n] += e->d * m[V];
	cmin (l[n], M / m[n]); memset (g, -0x3f, sizeof g); g[0][0] = 0;
	for (i = l[n]; i >= 0; -- i)
	{
		for (r = 0, e = list[n]; e; e = e->n)
			for (++ r, j = 0; j <= M; ++ j)
				for (k = 0; k <= j; ++ k)
					cmax (g[r][j], g[r - 1][j - k] + f[e->v][i * e->d][k]);
		for (j = 0; j <= i; ++ j)
			for (k = 0; k <= M; ++ k)
				cmax (f[n][j][k], g[r][k] + p[n] * (i - j));
	}
}
int main (int argc, char *argv[])
{
	memset (f, -0x3f, sizeof f);
	read (N), read (M); int x, y, z; rg int i, j, k; char ty[5];
	for (i = 1; i <= N; ++ i)
	{
		read (p[i]); scanf ("%s", ty);
		if (ty[0] == 'A')
			for (read (x); x; -- x)	read (y), read (z), In (i, y, z);
		else read (m[i]), read (l[i]);
	}
	for (x = 1; x <= N; ++ x)
		if (!deg[x])
			for (Dp (x), ++ T, i = 0; i <= M; ++ i)
				for (j = 0; j <= i; ++ j)
					for (k = 0; k <= l[x]; ++ k)
						cmax (h[T][i], h[T - 1][j] + f[x][k][i - j]);
	for (i = 0; i <= M; ++ i) cmax (s, h[T][i]);
	printf ("%d", s); return 0;
}
