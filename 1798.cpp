#include <iostream>
#include <cstring>
#include <cstdio>
#define Max 100005

using namespace std;

void read (long long &now)
{
    now = 0;
    char word = getchar ();
    bool temp = false;
    while (word < '0' || word > '9')
    {
        if (word == '-')
            temp = true;
        word = getchar ();
    }
    while (word >= '0' && word <= '9')
    {
        now = now * 10 + word - '0';
        word = getchar ();
    }
    if (temp)
        now = -now;
}

void write (long long now)
{
    char word[20];
    int Len = 0;
    if (now == 0)
        putchar ('0');
    if (now < 0)
    {
        putchar ('-');
        now = -now;
    }
    while (now)
    {
        word[++Len] = now % 10;
        now /= 10;
    }
    while (Len--)
        putchar (word[Len + 1] + '0');
}

long long M, N, Mod;

struct Segment
{
    
    struct Segment_Tree
    {
        long long l;
        long long r;
        long long Sum;
        long long Mul_flag;
        long long Add_flag;
        bool flag;
        
    };
    
    Segment_Tree tree[Max << 3];
    Segment_Tree *res, *L, *R;
    
    
    void Build (long long l, long long r, long long now)
    {
        tree[now].l = l;
        tree[now].r = r;
        if (l == r)
        {
            read (tree[now].Sum);
            return ;
        }
        long long Mid = (l + r) >> 1;
        Build (l, Mid, now << 1);
        Build (Mid + 1, r, now << 1 | 1);
        tree[now].Sum = (tree[now << 1].Sum + tree[now << 1 | 1].Sum) % Mod;
    }
    
    void Change_Add (long long l, long long r, long long now, long long to)
    {
        if (tree[now].l == l && tree[now].r == r)
        {
            tree[now].Add_flag = (tree[now].Add_flag + to) % Mod;
            tree[now].Sum = (tree[now].Sum + ((r - l + 1) * to)) % Mod;
            return ;
        }
        if (tree[now].Add_flag || tree[now].flag)
        {
            res = &tree[now];
            L = &tree[now << 1];
            R = &tree[now << 1 | 1];
            if (res->flag)
            {
                L->Sum = (L->Sum * res->Mul_flag) % Mod;
                R->Sum = (R->Sum * res->Mul_flag) % Mod;
                L->Add_flag = (L->Add_flag * res->Mul_flag) % Mod;
                R->Add_flag = (R->Add_flag * res->Mul_flag) % Mod;
                if (L->flag)
                    L->Mul_flag = (L->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    L->Mul_flag = res->Mul_flag;
                    L->flag = true;
                }
                if (R->flag)
                    R->Mul_flag = (R->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    R->Mul_flag = res->Mul_flag;
                    R->flag = true;
                }
                res->flag = false;
            }
            if (res->Add_flag)
            {
                L->Add_flag = (L->Add_flag + res->Add_flag) % Mod;
                R->Add_flag = (R->Add_flag + res->Add_flag) % Mod;
                L->Sum = (L->Sum + ((L->r - L->l + 1) % Mod) * res->Add_flag) % Mod;
                R->Sum = (R->Sum + ((R->r - R->l + 1) % Mod) * res->Add_flag) % Mod;
                res->Add_flag = 0;
            }
        }
        long long Mid = (tree[now].l + tree[now].r) >> 1;
        if (r <= Mid)
            Change_Add (l, r, now << 1, to);
        else if (l > Mid)
            Change_Add (l, r, now << 1 | 1, to);
        else
        {
            Change_Add (l, Mid, now << 1, to);
            Change_Add (Mid + 1, r, now << 1 | 1, to);    
        }
        tree[now].Sum = (tree[now << 1].Sum + tree[now << 1 | 1].Sum) % Mod;
    }
    
    void Change_Multiply (long long l, long long r, long long now, long long to)
    {
        if (tree[now].l == l && tree[now].r == r)
        {
            tree[now].Sum = (tree[now].Sum * to) % Mod;
            tree[now].Add_flag = (tree[now].Add_flag * to) % Mod;
            if (tree[now].flag)
                tree[now].Mul_flag = (tree[now].Mul_flag * to) % Mod;
            else
            {
                tree[now].flag = true;
                tree[now].Mul_flag = to;
            }
            return ;
        }
        if (tree[now].Add_flag || tree[now].flag)
        {
            res = &tree[now];
            L = &tree[now << 1];
            R = &tree[now << 1 | 1];
            if (res->flag)
            {
                L->Sum = (L->Sum * res->Mul_flag) % Mod;
                R->Sum = (R->Sum * res->Mul_flag) % Mod;
                L->Add_flag = (L->Add_flag * res->Mul_flag) % Mod;
                R->Add_flag = (R->Add_flag * res->Mul_flag) % Mod;
                if (L->flag)
                    L->Mul_flag = (L->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    L->Mul_flag = res->Mul_flag;
                    L->flag = true;
                }
                if (R->flag)
                    R->Mul_flag = (R->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    R->Mul_flag = res->Mul_flag;
                    R->flag = true;
                }
                res->flag = false;
            }
            if (res->Add_flag)
            {
                L->Add_flag = (L->Add_flag + res->Add_flag) % Mod;
                R->Add_flag = (R->Add_flag + res->Add_flag) % Mod;
                L->Sum = (L->Sum + ((L->r - L->l + 1) % Mod) * res->Add_flag) % Mod;
                R->Sum = (R->Sum + ((R->r - R->l + 1) % Mod) * res->Add_flag) % Mod;
                res->Add_flag = 0;
            }
        }
        long long Mid = (tree[now].l + tree[now].r) >> 1;
        if (r <= Mid)
            Change_Multiply (l, r, now << 1, to);
        else if (l > Mid)
            Change_Multiply (l, r, now << 1 | 1, to);
        else
        {
            Change_Multiply (l, Mid, now << 1, to);
            Change_Multiply (Mid + 1, r, now << 1 | 1, to);    
        }
        tree[now].Sum = (tree[now << 1].Sum + tree[now << 1 | 1].Sum) % Mod;
    }
    
    long long Query_sum (long long l, long long r, long long now)
    {
        if (tree[now].l == l && tree[now].r == r)
            return tree[now].Sum % Mod;
        if (tree[now].Add_flag || tree[now].flag)
        {
            res = &tree[now];
            L = &tree[now << 1];
            R = &tree[now << 1 | 1];
            if (res->flag)
            {
                L->Sum = (L->Sum * res->Mul_flag) % Mod;
                R->Sum = (R->Sum * res->Mul_flag) % Mod;
                L->Add_flag = (L->Add_flag * res->Mul_flag) % Mod;
                R->Add_flag = (R->Add_flag * res->Mul_flag) % Mod;
                if (L->flag)
                    L->Mul_flag = (L->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    L->Mul_flag = res->Mul_flag;
                    L->flag = true;
                }
                if (R->flag)
                    R->Mul_flag = (R->Mul_flag * res->Mul_flag) % Mod;
                else
                {
                    R->Mul_flag = res->Mul_flag;
                    R->flag = true;
                }
                res->flag = false;
            }
            if (res->Add_flag)
            {
                L->Add_flag = (L->Add_flag + res->Add_flag) % Mod;
                R->Add_flag = (R->Add_flag + res->Add_flag) % Mod;
                L->Sum = (L->Sum + ((L->r - L->l + 1) % Mod) * res->Add_flag) % Mod;
                R->Sum = (R->Sum + ((R->r - R->l + 1) % Mod) * res->Add_flag) % Mod;
                res->Add_flag = 0;
            }
        }
        tree[now].Sum = (tree[now << 1].Sum + tree[now << 1 | 1].Sum) % Mod;
        long long Mid = (tree[now].l + tree[now].r) >> 1;
        if (r <= Mid)
            return Query_sum (l, r, now << 1) % Mod;
        else if (l > Mid)
            return Query_sum (l, r, now << 1 | 1) % Mod;
        else
            return (Query_sum (l, Mid, now << 1) + Query_sum (Mid + 1, r, now << 1 | 1)) % Mod; 
    }
};

Segment Tree;

int main (int argc, char *argv[])
{
    read (N);
    read (Mod);
    Tree.Build (1, N, 1);
    long long type;
    long long l, r, z;
    read (M);
    for (int i = 1; i <= M; i++)
    {
        read (type);
        read (l);
        read (r);
        switch (type)
        {
            case 1:
            {
                read (z);
                Tree.Change_Multiply (l, r, 1, z);
                break;
            }
            case 2:
            {
                read (z);
                Tree.Change_Add (l, r, 1, z);
                break;
            }
            case 3:
            {
                write (Tree.Query_sum (l, r, 1));
                putchar ('\n');
                break;
            }
        }
    }    
    return 0;
}
