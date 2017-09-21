#include <cstdio>
#include <cmath>

void read (long long &now)
{
    now = 0;
    register char word = getchar ();
    while (word < '0' || word > '9')
        word = getchar ();
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
}

inline long long min (long long a, long long b)
{
    return a < b ? a : b;
}

inline long long max (long long a, long long b)
{
    return a > b ? a : b;
}

struct Segment_Tree_Date
{
    Segment_Tree_Date *Left, *Right;
    
    long long l, r;
    
    long long Mid;
    long long key;
    bool Flandre;
    
    Segment_Tree_Date ()
    {
        Left = NULL;
        Right = NULL;
        key = 0;
        Flandre = false;
    }
};

Segment_Tree_Date *Root;

class Segment_Tree_Type
{
    public :
        
        void Build (Segment_Tree_Date *&now, long long l, long long r)
        {
            now = new Segment_Tree_Date ;
            now->l = l;
            now->r = r;
            if (l == r)
            {
                read (now->key);
                if (now->key <= 1)
                    now->Flandre = true;
                return ;
            }
            now->Mid = l + r >> 1;
            Build (now->Left, l, now->Mid);
            Build (now->Right, now->Mid + 1, r);
            now->key = now->Left->key + now->Right->key;
            now->Flandre = now->Left->Flandre & now->Right->Flandre;
        }
        
        void Change_Section (Segment_Tree_Date *&now, long long l, long long r)
        {
            if (now->l == now->r)
            {
                now->key = (long long)sqrt (now->key);
                if (now->key <= 1)
                    now->Flandre = true;
                return ;
            }
            if (now->Flandre)
                return ;
            if (l <= now->Mid)
                Change_Section (now->Left, l, min (now->Mid, r));
            if (r > now->Mid)
                Change_Section (now->Right, max (now->Mid + 1, l), r);
            now->key = now->Left->key + now->Right->key;
            now->Flandre = now->Left->Flandre & now->Right->Flandre;
        }
        
        long long Query_Section (Segment_Tree_Date *&now, long long l, long long r)
        {
            if (l <= now->l && now->r <= r)
                return now->key;
            long long res = 0;
            if (l <= now->Mid)
                res += Query_Section (now->Left, l, min (now->Mid, r));
            if (r > now->Mid)
                res += Query_Section (now->Right, max (now->Mid + 1, l), r);
            return res;
        }
};

Segment_Tree_Type Tree;

long long N;

int main (int argc, char *argv[])
{
    read (N);
    Tree.Build (Root, 1, N); 
    long long x, y, type;
    for (read (N); N--; )
    {
        read (type);
        read (x);
        read (y);
        if (type)
            printf ("%lld\n", Tree.Query_Section (Root, min (x, y), max (x, y)));
        else
            Tree.Change_Section (Root, min (x, y), max (x, y)); 
    }
    return 0;
}
