#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=1<<30;
const double EPS=1e-6;

struct edge
{
    int u, v;
    double w;
    edge(int _u=0, int _v=0, double _w=0) : u(_u), v(_v), w(_w){}
    
    void read()
    {
        scanf("%d%d%lf", &u, &v, &w);
    }
};

struct SCC
{
    vector<vector<int>> edg;
    vector<int> dfn, low, com;
    stack<int> S;
    int d=0, cnt=0;
    
    SCC(int n, const vector<edge>& e) : edg(n+1), dfn(n+1, 0), low(n+1, 0), com(n+1, 0)
    {
        for(const edge& E : e)
            edg[E.u].push_back(E.v);
        
        for(int i=1; i<=n; i++)
            if( !dfn[i] )
                dfs(i);
    }
    
    void dfs(int u)
    {
        dfn[u]=low[u]=++d;
        S.push(u);
        
        for(int v : edg[u])
        {
            if( !dfn[v] )
                dfs(v);
            
            if( !com[v] )
                low[u]=min(low[u], low[v]);
        }
        
        if( dfn[u]==low[u] )
        {
            cnt++;
            
            for(bool flag=true; flag; S.pop())
            {
                flag=S.top()!=u;
                com[S.top()]=cnt;
            }
        }
    }
};

struct howard
{
    int n;
    vector<edge> e;
    vector<double> d, w;
    vector<int> p;
    
    howard(int _n, const vector<edge>& _e) : n(_n), e(_e), d(n+1, INF), w(n+1), p(n+1)
    //1 - 4
    {
        for(const edge& E : e)
        {
            if( d[E.u]>E.w )
            {
                d[E.u]=w[E.u]=E.w;
                p[E.u]=E.v;
            }
        }
    }
    
    double operator()()
    {
        for(; ; )
        {
            double ld;
            int s;
            get_cycle(ld, s);
            reverse_dfs(ld, s);
            
            if( !improve(ld) )
                return ld;
        }
    }
    
    void get_cycle(double& ld, int& s)
    //6 - 10
    {
        ld=INF;
        s=0;
        vector<int> vis(n+1, 0);
        vector<double> dis(n+1, 0);
        
        for(int i=1; i<=n; i++)
        {
            vis[i]=1;
            
            for(int u=i; vis[u]>=0; u=p[u])
            {
                int v=p[u];
                
                if( !vis[v] )
                {
                    vis[v]=vis[u]+1;
                    dis[v]=dis[u]+w[u];
                }
                else if( vis[v]>0 )
                {
                    double len=(dis[u]+w[u]-dis[v])/(vis[u]+1-vis[v]);
                    
                    if( ld>len )
                    {
                        ld=len;
                        s=i;
                    }
                    
                    break;
                }
            }
            
            for(int u=i; vis[u]>=0; u=p[u])
                vis[u]=-1;
        }
    }
    
    void reverse_dfs(double ld, int s)
    //11 - 12
    {
        vector<vector<int>> pre(n+1);
        
        for(int i=1; i<=n; i++)
            if( i!=s )
                pre[ p[i] ].push_back(i);
        
        queue<int> Q;
        
        for(Q.push(s); !Q.empty(); Q.pop())
        {
            int v=Q.front();
            
            for(int u : pre[v])
            {
                d[u]=d[v]+w[u]-ld;
                Q.push(u);
            }
        }
    }
    
    bool improve(double ld)
    //13 - 18
    {
        bool ans=false;
        
        for(const edge& E : e)
        {
            double nd=d[E.v]+E.w-ld;
            double dt=d[E.u]-nd;
            
            if( dt>0 )
            {
                ans|=dt>EPS;
                d[E.u]=nd;
                w[E.u]=E.w;
                p[E.u]=E.v;
            }
        }
        
        return ans;
    }
};

int main()
{
    int ncase;
    scanf("%d", &ncase);
    
    for(int cases=1; cases<=ncase; cases++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<edge> e(m);
        
        for(edge& E : e)
            E.read();
        
        SCC S(n, e);
        vector<vector<edge>> f(S.cnt+1);
        vector<int> idx(n+1, 0), cnt(n+1, 0);
        
        for(int i=1; i<=n; i++)
            idx[i]=++cnt[ S.com[i] ];
        
        for(const edge& E : e)
            if( S.com[E.u]==S.com[E.v] )
                f[ S.com[E.u] ].push_back(edge(idx[E.u], idx[E.v], E.w));
        
        double ans=INF;
        
        for(int i=1; i<=S.cnt; i++)
        {
            if( f[i].empty() )
                continue;
            
            howard H(cnt[i], f[i]);
            ans=min(ans, H());
        }
        
        if( ans>=INF )
            printf("Case #%d: No cycle found.\n", cases);
        else
            printf("Case #%d: %.2f\n", cases, ans);
    }
}

/*

2
2 1
1 2 1
2 2
1 2 2
2 1 3

*/
