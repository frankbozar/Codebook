struct KM{
    static const int INF=2147483647;//long long
    int n;
    vector<int> match, vx, vy;
    vector<int> lx, ly, slack;//long long
    vector<vector<int>> edge;//long long
    KM(int _n) : n(_n), match(n, -1), lx(n, -INF), ly(n, 0), edge(n, vector<int>(n, 0)){}
    void add_edge(int x, int y, int w){//long long
        edge[x][y] = w;
    }
    bool dfs(int x){
        vx[x]=1;
        for(int y=0; y<n; y++){
            if( vy[y] ) continue;
            if( lx[x]+ly[y]>edge[x][y] )
                slack[y]=min(slack[y], lx[x]+ly[y]-edge[x][y]);
            else{
                vy[y]=1;
                if( match[y]==-1 || dfs(match[y]) ){
                    match[y]=x; return true;
                }
            }
        }
        return false;
    }
    int operator()(){
        for(int i=0; i<n; i++) for(int j=0; j<n; j++)
            lx[i]=max(lx[i], edge[i][j]);
        for(int i=0; i<n; i++) for(slack.assign(n, INF); ; ){
            vx.assign(n, 0); vy.assign(n, 0);
            if( dfs(i) ) break;
            int d=INF;// long long
            for(int j=0; j<n; j++)
                if( !vy[j] ) d=min(d, slack[j]);
            for(int j=0; j<n; j++){
                if( vx[j] ) lx[j]-=d;
                if( vy[j] ) ly[j]+=d;
                else slack[j]-=d;
            }
        }
        int res=0;
        for(int i=0; i<n; i++) res+=edge[match[i]][i];
        return res;
    }
};
