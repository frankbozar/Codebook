#define edge pair<int,int>
#define v first
#define w second
struct lca{
    const int H=20;
    int n;
    vector<int> h;
    vector<vector<int>> p, b;
    lca(const vector<vector<edge>>& e) ://one-base vertex index
        n(e.size()-1), h(n+1, -1), p(H, vector<int>(n+1, -1)), b(H, vector<int>(n+1)){
        p[0][1]=1; b[0][1]=0; dfs(e, 1, 0);
        for(int i=1; i<H; i++) for(int j=1; j<=n; j++){
            p[i][j]=p[i-1][ p[i-1][j] ];
            b[i][j]=max(b[i-1][ p[i-1][j] ], b[i-1][j]);//something on the path from root
        }
    }
    void dfs(const vector<vector<edge>>& e, int u, int d=0){
        h[u]=++d;
        for(const edge& E : e[u]){
            if( h[E.v]>=0 ) continue;
            p[0][E.v]=u; b[0][E.v]=E.w;
            dfs(e, E.v, d);
        }
    }
    int operator()(int u, int v) const{
        if( h[u]>h[v] ) swap(u, v);
        int ans=0;
        for(int i=0, d=h[v]-h[u]; d>0; d>>=1, i++)
            if( d&1 ) ans=max(ans, b[i][v]), v=p[i][v];
        for(int i=0; u!=v; i++){
            for(; i>0 && p[i][u]==p[i][v]; i--);
            ans=max(ans, max(b[i][u], b[i][v]));
            u=p[i][u], v=p[i][v];
        }
        return ans;
    }
};
