#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#define EPS 1e-3
int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
#define flo double 
int P, Q, R;
flo D (flo x, flo y, flo _x, flo _y) 
{
    return sqrt ((x - _x) * (x - _x) + (y - _y) * (y - _y));
}
flo abs (flo a) { return a < 0 ? -a : a; }
flo Cal (flo Lx, flo Ly)
{
    flo lx = Cx, ly = Cy, rx = Dx, ry = Dy, Mx1, My1, Mx2, My2, r1, r2;
    for (; abs (rx - lx) > EPS || abs (ry - ly) > EPS; )
    {
        Mx1 = lx + (rx - lx) / 3, My1 = ly + (ry - ly) / 3;
        Mx2 = rx - (rx - lx) / 3, My2 = ry - (ry - ly) / 3;
        r1 = D (Lx, Ly, Mx1, My1) / R + D (Mx1, My1, Dx, Dy) / Q;   
        r2 = D (Lx, Ly, Mx2, My2) / R + D (Mx2, My2, Dx, Dy) / Q;
        if (r1 > r2) lx = Mx1, ly = My1;
        else rx = Mx2, ry = My2;
    }
    return D (Ax, Ay, Lx, Ly) / P + D (Lx, Ly, lx, ly) / R + D (lx, ly, Dx, Dy) / Q;
}
 
int Main ()
{
    scanf ("%d%d%d%d%d%d%d%d", &Ax, &Ay, &Bx, &By, &Cx, &Cy, &Dx, &Dy);
    scanf ("%d%d%d", &P, &Q, &R);    
    flo lx = Ax, ly = Ay, rx = Bx, ry = By, Mx1, My1, Mx2, My2;
    for (; abs (ry - ly) > EPS || abs (rx - lx) > EPS; )
    {
        Mx1 = lx + (rx - lx) / 3, My1 = ly + (ry - ly) / 3;
        Mx2 = rx - (rx - lx) / 3, My2 = ry - (ry - ly) / 3;
        if (Cal (Mx1, My1) > Cal (Mx2, My2)) lx = Mx1, ly = My1;
        else rx = Mx2, ry = My2;
    }
    printf ("%.2lf", Cal (lx, ly));
    return 0;
}
 
int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}
