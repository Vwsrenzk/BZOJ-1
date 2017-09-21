#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>

const int Big_B = 1000000000; const int Big_L = 9;
using namespace std;
inline int intcmp_ (int a, int b) { if (a > b) return 1; return a < b ? -1 : 0; }
struct Int 
{
#define rg register
	std :: vector <int> c; Int () {} typedef long long LL; 
	Int (int x) { for (; x > 0; c.push_back (x % Big_B), x /= Big_B); }
	Int (LL x) { for (; x > 0; c.push_back (x % Big_B), x /= Big_B); }
	inline void CrZ () { for (; !c.empty () && c.back () == 0; c.pop_back ()); }
	inline Int &operator += (const Int &rhs)
	{
		c.resize (max (c.size (), rhs.c.size ())); rg int i, t = 0, S;
		for (i = 0, S = rhs.c.size (); i < S; ++ i)
			c[i] += rhs.c[i] + t, t = c[i] >= Big_B, c[i] -= Big_B & (-t);
		for (i = rhs.c.size (), S = c.size (); t && i < S; ++ i)
			c[i] += t, t = c[i] >= Big_B, c[i] -= Big_B & (-t);
		if (t) c.push_back (t); return *this;
	}
	inline Int &operator *= (const Int &rhs)
	{
		rg int na = c.size (), i, j, S, ai; 
		c.resize (na + rhs.c.size ()); LL t;
		for (i = na - 1; i >= 0; -- i)
		{
			ai = c[i], t = 0, c[i] = 0;
			for (j = 0, S = rhs.c.size (); j < S; ++ j)
			{
				t += c[i + j] + (LL) ai * rhs.c[j];
				c[i + j] = t % Big_B, t /= Big_B;
			}
			for (j = rhs.c.size (), S = c.size (); t != 0 && i + j < S; ++ j)
				t += c[i + j], c[i + j] = t % Big_B, t /= Big_B;
			assert (t == 0);
		}
		CrZ (); return *this;
	}
	friend inline Int operator + (const Int &lhs, const Int &rhs)
	{ Int res = lhs; return res += rhs; }
	friend inline Int operator * (const Int &lhs, const Int &rhs)
	{ Int res = lhs; return res *= rhs; }
	friend inline ostream &operator << (ostream &out, const Int &rhs)
	{ 
		if (rhs.c.size () == 0) out << "0";
		else 
		{
			out << rhs.c.back ();
			for (rg int i = rhs.c.size () - 2; i >= 0; -- i)
				out << setfill ('0') << setw (Big_L) << rhs.c[i];
		}
		return out;
	} 
#undef rg	
};
#define Max 100009
Int f[Max];

int Main ()
{
	int N; cin >> N; f[2] = 1; f[1] = 0;	
	for (register int i = 3; i <= N; i ++)
		f[i] = (i - 1) * (f[i - 1] + f[i - 2]);	
	cout << f[N];
	return 0;
}
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
