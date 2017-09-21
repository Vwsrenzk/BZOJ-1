#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <cstring>

const int Big_B = 1000000000; const int Big_L = 9;
inline int intcmp_ (int a, int b) { if (a > b) return 1; return a < b ? -1 : 0; }
struct Int 
{
#define rg register
	inline int max (int a, int b) { return a > b ? a : b; }
	inline int min (int a, int b) { return a < b ? a : b; }
	std :: vector <int> c; Int () {} typedef long long LL; 
	Int (int x) { for (; x > 0; c.push_back (x % Big_B), x /= Big_B); }
	Int (LL x) { for (; x > 0; c.push_back (x % Big_B), x /= Big_B); }
	inline void CrZ () { for (; !c.empty () && c.back () == 0; c.pop_back ()); }
	inline Int &operator -= (const Int &rhs)
	{
		c.resize (max (c.size (), rhs.c.size ())); rg int i, t = 0, S;
		for (i = 0, S = rhs.c.size (); i < S; ++ i)
			c[i] -= rhs.c[i] + t, t = c[i] < 0, c[i] += Big_B & (-t);
		for (i = rhs.c.size (), S = c.size (); t && i < S; ++ i)
			c[i] -= t, t = c[i] < 0, c[i] += Big_B & (-t);
		CrZ (); return *this;
	}
	inline int Comp (const Int &rhs) const 
	{
		if (c.size () != rhs.c.size ()) return intcmp_ (c.size (), rhs.c.size ());
		for (rg int i = c.size () - 1; i >= 0; -- i) 
			if (c[i] != rhs.c[i]) return intcmp_ (c[i], rhs.c[i]);
		return 0;
	}
	friend inline Int operator - (const Int &lhs, const Int &rhs)
	{ Int res = lhs; return res -= rhs; }	
	friend inline std :: ostream &operator << (std :: ostream &out, const Int &rhs)
	{ 
		if (rhs.c.size () == 0) out << "0";
		else 
		{
			out << rhs.c.back ();
			for (rg int i = rhs.c.size () - 2; i >= 0; -- i)
				out << std :: setfill ('0') << std :: setw (Big_L) << rhs.c[i];
		}
		return out;
	} 
	friend inline std :: istream &operator >> (std :: istream &in, Int &rhs)
	{
		static char s[10000];
		in >> s + 1; int Len = strlen (s + 1);
		int v = 0; LL r = 0, p = 1;
		for (rg int i = Len; i >= 1; -- i)
		{
			++ v; r = r + (s[i] - '0') * p, p *= 10;
			if (v == Big_L) rhs.c.push_back (r), r = 0, v = 0, p = 1;
		}
		if (v != 0) rhs.c.push_back (r); 
		return in;
	}
	friend inline bool operator < (const Int &lhs, const Int &rhs)
	{ return lhs.Comp (rhs) < 0; }
	friend inline bool operator > (const Int &lhs, const Int &rhs)
	{ return lhs.Comp (rhs) > 0; }
	friend inline bool operator == (const Int &lhs, const Int &rhs)
	{ return lhs.Comp (rhs) == 0; }
	friend inline bool operator != (const Int &lhs, const Int &rhs)
	{ return lhs.Comp (rhs) != 0; }
#undef rg	
};
int Main ()
{
	Int a, b;
	std :: cin >> a >> b;
	for (; a != 0 || b != 0; )
	{
		if (a == 0) { std :: cout << b; return 0; }
	   	else if (b == 0) { std :: cout << a; return 0;}
		if (a < b) b -= a;
		else a -= b;
	}
	return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
