#include <cstdio>
#include <iostream>
 
#define Max 100001
#define INF 1e9 
#define Red true
#define Black false
 
const int BUF = 100000100; char Buf[BUF], *buf = Buf;
#define rg register 
#define Inline __attri\
bute__( ( optimize( "-O2" ) ) )
Inline void read (int &now)
{
    int temp = 0;
    for (now = 0; !isdigit (*buf); ++ buf)
        if (*buf == '-')
            temp = 1;
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
    if (temp)    
        now = -now;
}
 
struct R_D
{
    int key, size, weigth;
    bool color;
    
    R_D *father, *child[2];
    
    Inline void Fill (const int &__key, const bool &__color, const int &z, register R_D *now)
    {
        this->key = __key;
        this->color = __color;
        this->size = this->weigth = z;
        
        this->father = this->child[0] = this->child[1] = now;
    }
    
    Inline void Up ()
    {
        this->size = this->child[0]->size + this->child[1]->size + this->weigth;
    }
    
    Inline void Down ()
    {
        for (R_D *now = this; now->size; now = now->father)
            now->size --;
    }
    
    Inline int Get_Pos (const int &now) const
    {
        return this->key == now ? -1 : now > this->key;
    } 
};
 
 
class Red_Black_Tree
{
    
    private :
        
        int Top;
        
        R_D *Root, *null;
        R_D poor[Max], *Tail, *reuse[Max];
        
        
        Inline R_D *New (const int &key)
        {
            register R_D *now = null;
            if (!Top)
                now = Tail ++;
            else
                now = reuse[-- Top];
            now->Fill (key, Red, 1, null);
            return now;
        }
        
        Inline void Rotate (R_D *&now, const bool &pos)
        {
            register R_D *C = now->child[pos ^ 1];
            now->child[pos ^ 1] = C->child[pos];
            if (C->child[pos]->size)
                C->child[pos]->father = now;
            C->father = now->father;
            if (!now->father->size)
                Root = C;
            else 
                now->father->child[now->father->child[0] != now] = C;
            C->child[pos] = now;
            now->father = C;
            C->size = now->size;
            now->Up ();
        }
        
        Inline void Insert_Fill (register R_D *&now)
        {
            for (; now->father->color; )
            {
                R_D *Father = now->father, *Grand = Father->father;
                bool pos = Father == Grand->child[0];
                R_D *Uncle = Grand->child[pos];
                if (Uncle->color)
                {
                    Father->color = Uncle->color = Black;
                    Grand->color = Red;
                    now = Grand;
                }
                else if (now == Father->child[pos])
                    Rotate (now = Father, pos ^ 1);
                else
                {
                    Grand->color = Red;
                    Father->color = Black;
                    Rotate (Grand, pos);
                }
            }
            Root->color = Black;
        }
        
        Inline R_D *Find (R_D *now, int key)
        {
            for (; now->size && now->key != key; now = now->child[now->key < key]);
            return now;
        }
        
        Inline void Delete_Fill (register R_D *&now)
        {
            for (; now != Root && now->color == Black; )
            {
                register bool pos = now == now->father->child[0];
                R_D *Father = now->father, *Uncle = Father->child[pos];
                if (Uncle->color == Red)
                {
                    Uncle->color = Black;
                    Father->color = Red;
                    Rotate (now->father, pos ^ 1);
                    Uncle = Father->child[pos];
                }
                else if (Uncle->child[0]->color == Black && Uncle->child[1]->color == Black)
                {
                    Uncle->color = Red;
                    now = Father;
                }
                else
                {
                    if (Uncle->child[pos]->color == Black)
                    {
                        Uncle->child[pos ^ 1]->color = Black;
                        Uncle->color = Red;
                        Rotate (Uncle, pos);
                        Uncle = Father->child[pos];
                    }
                    Uncle->color = Father->color;
                    Uncle->child[pos]->color = Father->color = Black;
                    Rotate (Father, pos ^ 1);
                    break;
                }
            }
            now->color = Black;
        }
        
    public :
        
        Red_Black_Tree ()
        {
            Top = 0;
            Tail = &poor[Top];
            null = Tail ++;
            null->Fill (0, Black, 0, NULL);
            Root = null;
        }
        
        Inline void Insert (const int &key)
        {
            register R_D *now = Root, *Father = null;
            register int pos;
            for (; now->size; now = now->child[pos])
            {
                now->size ++;
                Father = now;
                pos = now->Get_Pos (key);
                if (pos == -1)
                {
                    now->weigth ++;
                    return ;
                }
            }
            now = New (key);
            if (Father->size)
                Father->child[key > Father->key] = now;
            else
                Root = now;
            now->father = Father;
            this->Insert_Fill (now); 
        }
        
        Inline void Delete (const int &key)
        {
            register R_D *res = Find (Root, key);
            if (!res->size)
                return ;
            if (res->weigth > 1)
            {
                res->weigth --;
                res->Down ();
                return ;
            }
            register R_D *Father = res, *now = null;
            
            if (res->child[0]->size && res->child[1]->size)
                for (Father = res->child[1]; Father->child[0]->size; Father = Father->child[0]);
            
            now = Father->child[!Father->child[0]->size];
            now->father = Father->father;
            if (!Father->father->size)
                Root = now;
            else
                Father->father->child[Father->father->child[1] == Father] = now;
            
            if (res != Father)
            {
                res->key = Father->key;
                res->weigth = Father->weigth;
            }
            
            Father->father->Down ();
    
            for (R_D *Fuck = Father->father; Father->weigth > 1 && Fuck->size && Fuck != res; Fuck->size -= Father->weigth - 1, Fuck = Fuck->father);
    
            if (Father->color == Black)
                Delete_Fill (now);
            
            reuse[Top ++] = Father;
        }
        
        Inline int Get_kth_number (register int k)
        {
            register int res;
            register R_D *now = Root;
            
            for (; now->size; )
            {
                res = now->child[0]->size;
                
                if (k <= res)
                    now = now->child[0];
                else if (res + 1 <= k && k <= res + now->weigth)
                    break;
                else 
                {
                    k -= res + now->weigth;
                    now = now->child[1];
                }
            }
            return now->key;
        }
        
        Inline int Get_rank (const int &key)
        {
            register int res, cur = 0;
            register R_D *now = Root;
            
            for (; now->size; )
            {
                res = now->child[0]->size;
                if (now->key == key)
                    break;
                else if (now->key > key)
                    now = now->child[0];
                else
                {
                    cur += res + now->weigth;
                    now = now->child[1];
                }
            }
            
            return cur + res + 1;
        }
        
        Inline int Find_Suffix (const int &key)
        {
            register int res = INF;
            
            for (R_D *now = Root; now->size; )
                if (now->key > key)
                {
                    res = now->key;
                    now = now->child[0];
                }
                else 
                    now = now->child[1];
            
            return res;
        
        }
        
        Inline int Find_Prefix (const int &key)
        {
            register int res = INF;
            
            for (R_D *now = Root; now->size; )
                if (now->key < key)
                {
                    res = now->key;
                    now = now->child[1];
                }
                else
                    now = now->child[0];
            return res;
        }
		int Size () { return Root->size; }
};
 
Red_Black_Tree A, B;
inline int min (int a, int b) { return a < b ? a : b; }
inline int abs (int a) { return a < 0 ? -a : a; }
#define Mod 1000000
int Main ()
{
    fread (buf, 1, BUF, stdin);
	int N; read (N); rg int i, Answer = 0; int t, x, p, s;
	for (i = 1; i <= N; ++ i)
	{
		read (t), read (x);
		if (t == 0)
		{
			if (B.Size ())
			{
				p = B.Find_Prefix (x);
				s = B.Find_Suffix (x);
				if (abs (x - p) == abs (x - s) || abs (x - p) < abs (x - s))
					B.Delete (p), Answer = (Answer + abs (x - p)) % Mod;
				else B.Delete (s), Answer = (Answer + abs (x - s)) % Mod;
			}
			else A.Insert (x);
		}
		else 
		{
			if (A.Size ())
			{
				p = A.Find_Prefix (x);
				s = A.Find_Suffix (x);
				if (abs (x - p) == abs (x - s) || abs (x - p) < abs (x - s))
					A.Delete (p), Answer = (Answer + abs (x - p)) % Mod;
				else A.Delete (s), Answer = (Answer + abs (x - s)) % Mod;
			}
			else B.Insert (x);
		}
	}
	printf ("%d", Answer);
}
int ZlycerQan = Main();
int main(int argc, char *argv[]){;}
