#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template<int N>
struct veb
{
    enum{n=N>>1, m=(1<<n)-1};
    veb<n> table, *child[1<<n];
    int mini=0, maxi=-1;
    
    veb()
    {
        memset(child, 0, sizeof(child));
    }
    
    void insert(int x)
    {
        if( mini>maxi )
        {
            mini=maxi=x;
            return ;
        }
        else if( mini==maxi )
        {
            /*
            mini=min(mini, x);
            maxi=max(maxi, x);
            x=maxi;
             */
            mini=x<mini ? x : mini ;
            maxi=x=maxi^mini^x;
        }
        else if( x<mini )
            swap(mini, x);
        else if( x>maxi )
            maxi=x;
        
        int hi=x>>n;
        
        if( child[hi]==NULL )
            child[hi]=new veb<n>;
        
        child[hi]->insert(x&m);
        
        if( child[hi]->mini==child[hi]->maxi )
            table.insert(hi);
    }
    
    void erase(int x)
    {
        if( x==mini && x==maxi )
        {
            maxi=-1;
            return ;
        }
        else if( x==mini )
        {
            x=mini=child[table.mini]->mini;
        }
        else if( x==maxi )
        {
            if( table.mini>table.maxi )
            {
                maxi=mini;
                return ;
            }
            else
            {
                maxi=child[table.maxi]->maxi;
            }
        }
        
        int hi=x>>n;
        child[hi]->erase(x&m);
        
        if( child[hi]->mini>child[hi]->maxi )
            table.erase(hi);
    }
    
    int next(int x=0) const
    {
        if( x>maxi )
            return -1;
        else if( x<=mini )
            return mini;
        
        int hi=x>>n;
        int lo=x&m;
        
        if( lo<=child[hi]->maxi )
            return (hi<<n)|child[hi]->next(lo);
        
        hi=table.next(hi+1);
        return (hi<<n)|child[hi]->mini;
    }
    
    void print(int le=0) const
    {
        if( mini>maxi )
            return ;
        
        if( N==32 )
            fprintf(stderr, "! ");
        
        fprintf(stderr, "%d ", le|mini);
        
        for(int i=0; i<=m; i++)
            if( child[i]!=NULL )
                child[i]->print(le|(i<<n));
        
        if( N==32 )
            fprintf(stderr, "\n");
    }
};

template<>
struct veb<4>
{
    int b=0, mini=0, maxi=-1;
    
    void insert(int x)
    {
        b|=1<<x;
        update();
    }
    
    void erase(int x)
    {
        b= b&(1<<x) ? b^(1<<x) : b ;
        update();
    }
    
    int next(int x) const
    {
        return b>>x==0 ? -1 : __builtin_ffs(b>>x)+x-1;
    }
    
    void update()
    {
        if( b==0 )
            maxi=-1;
        else
        {
            mini=__builtin_ffs(b)-1;
            maxi=(sizeof(int)<<3)-1-__builtin_clz(b);
        }
    }
    
    void print(int le) const
    {
        if( mini>maxi )
            return ;
        
        for(int i=0; i<16; i++)
            if( b&(1<<i) )
                fprintf(stderr, "%d ", le|i);
    }
};

/*
0 1
0 5
0 6
0 0
1 0
1 6
2 6
*/

int main()
{
    for(veb<32> V; ; )
    {
        int o, p;
        scanf("%d%d", &o, &p);
        
        if( o==0 )
            V.insert(p);
        else if( o==1 )
            V.erase(p);
        else
            fprintf(stderr, "%d\n", V.next(p));
        
        V.print();
    }
}
/*
const int N=1<<20;
char s[N]={0}, t[N]={0};
int a[N]={0}, n, m;

bool ok(const veb<32>& V)
{
    int p=0;
    
    for(int d=V.next(); d>=0; d=V.next(d+1))
        if( s[d]==t[p] )
            if( ++p>=m )
                return true;
    
    return false;
}

int main()
{
    scanf("%s%s", s, t);
    n=strlen(s);
    m=strlen(t);
    
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
        fprintf(stderr, "%d ", a[i]);
    }
    
    fprintf(stderr, "\n");
    
    int ans=-1, p=n;
    veb<32> V;
    
    for(int l=0, r=n; l<r; )
    {
        int x=(l+r)>>1;
        
        while( x<p )
            V.insert(a[--p]);
        
        while( x>p )
            V.erase(a[p++]);
        
        V.print();
        
        if( !ok(V) )
            r=x;
        else
        {
            l=x+1;
            ans=x;
        }
    }
    
    printf("%d\n", ans);
}
*/
