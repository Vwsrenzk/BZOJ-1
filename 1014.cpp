#include <cstdio>
#include <iostream>
typedef long long LL;
#include <cstring>
#define Max 150000
#define BASE 257
#define rg register
int N, M; unsigned long long mi[Max];
inline void read (int &n)
{
	rg char c = getchar ();
	for (n = 0; !isdigit (c); c = getchar ());
	for (; isdigit (c); n = n * 10 + c - '0', c = getchar ());
}
struct SD
{
	SD *c[2], *f; unsigned long long h; int s; char r;
	inline void Up ()
	{
		s = c[0]->s + c[1]->s + 1;
		h = c[0]->h + r * mi[c[0]->s] + c[1]->h * mi[c[0]->s + 1];
	}
} *null, *Root = NULL, poor[Max], *Ta = poor;
char line[Max];
class SplayType
{
	private :
		void R (SD *&n)
		{
			SD *F = n->f, *G = F->f; int p = n == F->c[1];
			if ((F->c[p] = n->c[p ^ 1]) != null) F->c[p]->f = F;
			F->f = n, n->c[p ^ 1] = F;
			if ((n->f = G) != null) G->c[F == G->c[1]] = n;
			F->Up (), n->Up ();
		}
		
		void Splay (SD *&n, SD *&t)
		{
			for (SD *F; (F = n->f) != t; R (n))
				if (F->f != t) R ((F->c[1] == n) == (F->f->c[1] == F) ? F : n);
			if (t == null) Root = n;
		}
		
	public :
		
		SD *Gkth (int k)
		{
			SD *n = Root; 
			for (; k && n != null; )
			{
				if (n->c[0]->s >= k) n = n->c[0];
				else if (n->c[0]->s + 1 == k) return n;
				else k -= n->c[0]->s + 1, n = n->c[1];
			}
			return n;
		}

		SD *Build (int l, int r)
		{
			if (l > r) return null; int m = l + r >> 1;
			SD *n = ++ Ta; n->r = line[m];
			if ((n->c[0] = Build (l, m - 1)) != null) n->c[0]->f = n;
			if ((n->c[1] = Build (m + 1, r)) != null) n->c[1]->f = n;
			n->Up (); return n;
		}
		
		inline void I (int pos, char r)
		{
			SD *n = ++ Ta, *p = Gkth (pos); n->r = r;
			n->c[0] = null, n->c[1] = p->c[1], n->f = p;
			n->c[1]->f = n, p->c[1] = n, n->Up ();
			for (; p != null; p->Up (), p = p->f);
		}
		
		inline void C (int pos, char r)
		{
			SD *p = Gkth (pos), *n; p->r = r;
			for (n = p; n != null; n->Up (), n = n->f);
		}
		
		inline unsigned long long Q (int l, int r)
		{
			SD *L = Gkth (l - 1), *R = Gkth (r + 1);
			Splay (L, null), Splay (R, L); return R->c[0]->h;
		}
} S;

int Main ()
{
	scanf ("%s", line + 2); N = strlen (line + 2); read (M); rg int i, j;
	null = new SD; null->c[0] = null->c[1] = null->f = null; null->s = null->h = null->r = 0;
	for (mi[0] = i = 1; i < Max; ++ i) mi[i] = mi[i - 1] * BASE; 
	line[1] = '~', line[N + 2] = '!', Root = S.Build (1, N + 2);
	Root->f = null; int x, y, s, l, r, m; 
	for (char c; M; -- M)
	{
		for (; c = getchar (), c < 'A'; );
		if (c == 'Q')
		{
			read (x), read (y), ++ x, ++ y;
			if (S.Gkth (x)->r != S.Gkth (y)->r) { puts ("0");  continue; }
			for (s = l = 1, r = N - (x < y ? y : x) + 2; l <= r; )
			{
				m = l + r >> 1;
				if (S.Q (x, x + m - 1) == S.Q (y, y + m - 1)) l = (s = m) + 1; 
				else r = m - 1;
			}
			printf ("%d\n", s);
		}
		else 
		{
			y = c == 'R', N += y ^ 1;
			read (x), ++ x; for (; c = getchar (), c < 'a'; );
			if (y) S.C (x, c); else S.I (x, c);
		}
	}
	return 0;
}
int ZlycerQan = Main (); int main (int argc, char *argv[]) {;}
