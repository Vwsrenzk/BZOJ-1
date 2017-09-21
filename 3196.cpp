#include <cstdio>

#define Max 4000005
#define INF 1e9

void read (int &now)
{
    register char word = getchar ();
    int temp = 0;
    for (now = 0; word < '0' || word > '9'; word = getchar ())
        if (word == '-')
            temp = 1;
    for (; word >= '0' && word <= '9'; now = now * 10 + word - '0', word = getchar ());
    if (temp)
        now = -now;
}

int data[Max];

struct S_D 
{
    S_D *child[2], *father;
    
    int size, weigth;
    int key;
    
    S_D ()
    {
        this->child[0] = this->child[1] = NULL;
        this->father = NULL;
        
        this->size = this->weigth = 1;
        this->key = 0;
    }
    
    void Clear ()
    {
        this->child[0] = this->child[1] = NULL;
        this->father = NULL;
    }
    
    int Get_Pos ()
    {
        return this->father->child[1] == this;
    }
    
    inline void Updata ()
    {
        this->size = this->weigth;
        if (this->child[0])
            this->size += this->child[0]->size;
        if (this->child[1])
            this->size += this->child[1]->size;
    }
};

int Maxn = -INF;

inline int max (int a, int b)
{
    return a > b ? a : b;
}

inline int min (int a, int b)
{
    return a < b ? a : b;
}

struct X_D
{
    X_D *Left, *Right;
    
    int l, r;
    int Mid;
    
    X_D (int __l, int __r) : l (__l), r (__r)
    {
        Left = Right = NULL;
        Mid = __l + __r >> 1;
    }
};

int Answer;

class Splay_Tree_Type
{
    
    private :
        
        S_D *Root;
        
        void Rotate (S_D *now)
        {
            S_D *Father = now->father;
            int pos = now->Get_Pos () ^ 1;
            Father->child[pos ^ 1] = now->child[pos];
            if (now->child[pos])
                now->child[pos]->father = Father;
            if ((now->father = Father->father) != NULL)
                now->father->child[now->father->child[1] == Father] = now;
                
            Father->father = now;
            now->child[pos] = Father;
            
            Father->Updata ();
            now->Updata ();
        }
        
        void Splay (S_D *now)
        {
            for (S_D *Father; Father = now->father; this->Rotate (now))
                if (Father->father)
                    this->Rotate (now->Get_Pos () == Father->Get_Pos () ? Father : now);
        }
        
    public :
        
        void Insert (int x)
        {
            if (Root == NULL)
            {
                Root = new S_D ;
                Root->key = x;
                return ;
            }
            S_D *now = Root, *Father;
            for (; ; Father = now, now = now->child[x > now->key])
            {
                if (now == NULL)
                {
                    now = new S_D;
                    now->father = Father;
                    now->key = x;
                    Father->child[x > Father->key] = now;
                    this->Splay (now);
                    Root = now;
                    return ;
                }
                if (now->key == x)
                {
                    now->weigth ++;
                    this->Splay (now);
                    Root = now;
                    return ;
                }
            }
        }
        
        int Find_Rank (int x)
        {
            S_D *now = Root;
            int Answer = 0;
            for (; ; )
            {
                if (now == NULL)
                    return Answer;
                if (now->key == x)
                    return (now->child[0] ? now->child[0]->size : 0) + Answer;
                else if (now->key < x)
                {
                    Answer += (now->child[0] ? now->child[0]->size : 0) + now->weigth;
                    now = now->child[1];
                }
                else if (now->key > x)
                    now = now->child[0];
                    
            }
        }
        
        void Find (int x)
        {
            S_D *now;
            for (now = Root; (now != NULL && x != now->key); now = now->child[x > now->key]);
            
            this->Splay (now);
            Root = now;
            return ;
        }
        
        void Delete ()
        {
            S_D *now = Root;
            if (now->weigth > 1)
            {
                now->weigth --;
                now->size --;
                return ;
            }
            if (now->child[0] == NULL && now->child[1] == NULL)
            {
                 Root = NULL;
                 now->Clear ();
                 return ;
            }
            S_D *res;
            if (now->child[1] == NULL)
            {
                res = now;
                now->child[0]->father = NULL;
                Root = now->child[0];
                res->Clear ();
                return ;
            }
            if (now->child[0] == NULL)
            {
                res = now;
                now->child[1]->father = NULL;
                Root = now->child[1];
                res->Clear ();
                return ;
            }
            
            res = Root;
            S_D *res_pre = Find_Prefix_Pos ();
            this->Splay (res_pre);
            Root = res_pre;
            Root->child[1] = res->child[1];
            res->child[1]->father = Root;
            res->Clear ();
            Root->Updata ();
            return;
        }
        
        S_D *Find_Prefix_Pos () 
        {
            S_D *now = Root;
            for (now = now->child[0]; now->child[1]; now = now->child[1]);
            
            return now;
        }
        
        int Ask_Prefix (int x)
        {
            S_D *now = Root;
            for (; now;)
            {
                if (now->key < x)
                {
                    if (Answer < now->key)
                        Answer = now->key;
                    now = now->child[1];
                }
                else 
                    now = now->child[0];
            }
            return Answer;
        }
        
        int Ask_Suffix (int x)
        {
            S_D *now = Root;
            for (; now; )
            {
                if (now->key > x)
                {
                    if (Answer > now->key)
                        Answer = now->key;
                    now = now->child[0];
                }
                else 
                    now = now->child[1];
            }
            return Answer;
        }
};

Splay_Tree_Type Splay[Max];

class Segment_Tree_Type
{
    
    private :
        
        X_D *Root;
        void __Build_ (X_D *&now, int l, int r)
        {
            now = new X_D (l, r);
            if (l == r)
                return ;
            __Build_ (now->Left, l, now->Mid);
            __Build_ (now->Right, now->Mid + 1, r);
        }
        
        void __Insert_ (X_D *&now, int pos, int x, int _in)
        {
            Splay[_in].Insert (x);
            
            if (now->l == now->r)
                return ;
            if (pos <= now->Mid)
                __Insert_ (now->Left, pos, x, _in << 1);
            else 
                __Insert_ (now->Right, pos, x, _in << 1 | 1);
        }
                
        void __Query_Rank_ (X_D *&now, int l, int r, int k, int _in)
        {
            if (l <= now->l && now->r <= r)
            {
                Answer += Splay[_in].Find_Rank (k);
                return ;
            }
            
            if (l <= now->Mid)
                __Query_Rank_ (now->Left, l, r, k, _in << 1);
            if (now->Mid  < r)
                __Query_Rank_ (now->Right, l, r, k, _in << 1 | 1);
        }
        
        void __Change_ (X_D *&now, int pos, int x, int _in)
        {
            Splay[_in].Find (data[pos]);
            Splay[_in].Delete ();
            Splay[_in].Insert (x);
            
            if (now->l == now->r)
                return ;
                
            if (pos <= now->Mid)
                __Change_ (now->Left, pos, x, _in << 1);
            else 
                __Change_ (now->Right, pos, x, _in << 1 | 1); 
        }
        
        void __Query_Prefix_ (X_D *&now, int l, int r, int x, int _in)
        {
            if (l <= now->l && now->r <= r)
            {
                Answer = max (Answer, Splay[_in].Ask_Prefix (x));
                return ;
            }
            
            if (l <= now->Mid)
                __Query_Prefix_ (now->Left, l, r, x, _in << 1);
            if (now->Mid < r)
                __Query_Prefix_ (now->Right, l, r, x, _in << 1 | 1);
        }
        
        void __Query_Suffix_ (X_D *&now, int l, int r, int x, int _in)
        {
            if (l <= now->l && now->r <= r)
            {
                Answer = min (Answer, Splay[_in].Ask_Suffix (x));
                return ;
            }
            
            if (l <= now->Mid)
                __Query_Suffix_ (now->Left, l, r, x, _in << 1);
            if (r > now->Mid)
                __Query_Suffix_ (now->Right, l, r, x, _in << 1 | 1);
        }
        
    public :
        
        void Build (int l, int r)
        {
            __Build_ (Root, l, r);
            return ;
        }
        
        void Insert (int pos, int x)
        {
            __Insert_ (Root, pos, x, 1);
            return ;
        }
        
        int Query_Suffix (int l, int r, int k)
        {
            Answer = INF;
            __Query_Suffix_ (Root, l, r, k, 1);
            return Answer;
        }
        
        int Query_kth_number (int l, int r, int x)
        {
            int L, R, Mid;
            for (L = 0, R = Maxn + 1, Mid; L != R; )
            {
                Mid = L + R >> 1;
                Answer = 0;
                this->Query_Rank (l, r, Mid);
                
                if (Answer < x)
                    L = Mid + 1;
                else
                    R = Mid;
            }
            return L - 1;
        }
        
        int Query_Rank (int l, int r, int k)
        {
            Answer = 0;
            __Query_Rank_(Root, l, r, k, 1);
            return Answer;
        }
        
        int Query_Prefix (int l, int r, int k)
        {
            Answer = 0;
            __Query_Prefix_ (Root, l, r, k, 1);
            return Answer;
        }
        
        void Change (int pos, int x)
        {
            __Change_ (Root, pos, x, 1);
            return ;
        }
};

Segment_Tree_Type Seg;

int main (int argc, char *argv[])
{
    int N, M;
    read (N);
    read (M);
    
    Seg.Build (1, N);
    for (int i = 1; i <= N; i ++)
    {
        read (data[i]);
        
        Maxn = max (data[i], Maxn);
        Seg.Insert (i, data[i]); 
    }
    
    for (int type, x, y, z; M --; )
    {
        read (type);
        if (type == 1)
        {
            read (x);
            read (y);
            read (z);
            
            printf ("%d\n", Seg.Query_Rank (x, y, z) + 1);
        }
        else if (type == 2)
        {
            read (x);
            read (y);
            read (z);
            
            printf ("%d\n", Seg.Query_kth_number (x, y, z));
        }
        else if (type == 3)
        {
            read (x);
            read (z);
            
            Seg.Change (x, z);
            data[x] = z;
            Maxn = max (Maxn, x);
        }
        else if (type == 4)
        {
            read (x);
            read (y);
            read (z);
            
            printf ("%d\n", Seg.Query_Prefix (x, y, z));
        }
        else 
        {
            read (x);
            read (y);
            read (z);
            
            printf ("%d\n", Seg.Query_Suffix (x, y, z));
        }
    }
    return 0;
}
