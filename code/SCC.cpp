vector<vector<int>> edg;
int dfn[N]={0}, low[N], com[N]={0};
stack<int> S;
void tarjan_scc(int u, int d=0){
    dfn[u]=low[u]=++d;
    S.push(u);
    for(int v : edg[u]){
        if( !dfn[v] ) tarjan_scc(v, d);
        if ( !com[v] ) low[u]=min(low[u], low[v]);
    }
    if( d==low[u] ){
        for(int flag=1; flag; ){
            flag= S.top()!=u;
            com[S.top()]=u+1;
            S.pop();
        }
    }
}
