#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long lld;

struct set
{
    vector<int> p;
    set(int n) : p(n+1, -1){}
    
    int find(int x)
    {
        return p[x]<0 ? x : p[x]=find(p[x]);
    }
    
    bool join(int x, int y)
    {
        x=find(x);
        y=find(y);
        
        if( x==y )
            return false;
        
        p[x]=y;
        return true;
    }
};

struct edge
{
    int i, u, v, w, c;
    
    bool operator<(const edge& E) const
    {
        return w<E.w;
    }
};

struct lca
{
    const int N=20;
    int n;
    vector<int> h;
    vector<vector<int>> p, b;
    
    lca(const vector<vector<pair<int, int>>>& a) : n(a.size()-1), h(n+1, -1), p(N, vector<int>(n+1, -1)), b(N, vector<int>(n+1))
    {
        p[0][1]=1;
        b[0][1]=0;
        dfs(a, 1, 0);
        
        for(int i=1; i<N; i++)
        {
            for(int j=1; j<=n; j++)
            {
                p[i][j]=p[i-1][ p[i-1][j] ];
                b[i][j]=max(b[i-1][ p[i-1][j] ], b[i-1][j]);
            }
        }
    }
    
    void dfs(const vector<vector<pair<int, int>>>& a, int u, int d=1)
    {
        h[u]=d;
        
        for(int i=a[u].size()-1; i>=0; i--)
        {
            int v=a[u][i].first;
            int w=a[u][i].second;
            
            if( h[v]>=0 )
                continue;
            
            p[0][v]=u;
            b[0][v]=w;
            dfs(a, v, d+1);
        }
    }
    
    int operator()(int u, int v) const
    {
        int ans=0;
        
        if( h[u]>h[v] )
            swap(u, v);
        
        for(int i=0, d=h[v]-h[u]; d>0; d>>=1, i++)
        {
            if( d&1 )
            {
                ans=max(ans, b[i][v]);
                v=p[i][v];
            }
        }
        
        for(int i=0; u!=v; i++)
        {
            for(; i>0 && p[i][u]==p[i][v]; i--);
            ans=max(ans, max(b[i][u], b[i][v]));
            u=p[i][u];
            v=p[i][v];
        }
        
        return ans;
    }
};

int main()
{
    lld sum=0;
    int n, m, k, idx=0, ans=0;
    scanf("%d%d", &n, &m);
    vector<edge> e(m);
    
    for(int i=0; i<m; i++)
        e[i].i=i+1;
    
    for(int i=0; i<m; i++)
        scanf("%d", &e[i].w);
    
    for(int i=0; i<m; i++)
        scanf("%d", &e[i].c);
    
    for(int i=0; i<m; i++)
        scanf("%d%d", &e[i].u, &e[i].v);
    
    scanf("%d", &k);
    sort(e.begin(), e.end());
    vector<vector<pair<int, int>>> a(n+1);
    set S(n+1);
    
    for(int i=0; i<m; i++)
    {
        const edge& E=e[i];
        
        if( S.join(E.u, E.v) )
        {
            sum+=E.w;
            a[E.u].push_back({E.v, E.w});
            a[E.v].push_back({E.u, E.w});
        }
    }
    
    lca L(a);
    
    for(int i=0; i<m; i++)
    {
        const edge& E=e[i];
        int w=E.w-k/E.c;
        
        if( ans>w-L(E.u, E.v) )
        {
            ans=w-L(E.u, E.v);
            idx=i;
        }
    }
    
    e[idx].w-=k/e[idx].c;
    sort(e.begin(), e.end());
    S=set(n+1);
    printf("%lld\n", sum+ans);
    
    for(int i=0; i<m; i++)
    {
        const edge& E=e[i];
        
        if( S.join(E.u, E.v) )
            printf("%d %d\n", E.i, E.w);
    }
}
