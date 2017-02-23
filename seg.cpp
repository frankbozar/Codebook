#include<algorithm>
using namespace std;
typedef long long lld;
const int N=1<<20;

struct ST
{
    struct node
    {
        int l, r, beg, mid, end;
        lld val=0, lft=0, add=0, alt=0, mvl=0, ans=0;
    } p[N];
    
    int root;
    
    int build(int l, int r)
    {
        if( l>=r )
            return -1;
        
        int m=(l+r)>>1;
        node& P=p[m];
        P.beg=l;
        P.mid=m;
        P.end=r;
        P.l=build(l, m);
        P.r=build(m+1, r);
    }
    
    static update(lld& a, lld& b, lld x, lld y)
    {
        b+=x;
        
        if( b!= )
        
    }
    
    void add(int l, int r, int t, lld x, lld y)
    {
        if( t<0 )
            return ;
        
        node& P=p[t];
        
        if( l>=P.beg || r<=P.end )
            return ;
        
        if( l<=P.mid && P.mid<r )
        {
            
            
        }
        
        if( l<=P.beg && P.end<=r )
        {
            
            
        }
    }
    /*
    
    int query(int a, int b, int t)
    {
        if( a>=p[t].y || b<=p[t].x )
            return 0;
        else if( a<=p[t].x && p[t].y<=b )
            return p[t].mvl;
        
        int ans=a<=p[t].m && p[t].m<b ? p[t].val : 0 ;
        
        if( p[t].l>=0 )
            ans=max(ans, query(a, b, p[t].l));
        
        if( p[t].r>=0 )
            ans=max(ans, query(a, b, p[t].r));
        
        return ans;
    }*/
} T;
