vector<vector<int>> edg;
int dfn[N]={0}, low[N], com[N]={0}, d=0;
stack<int> S;
void tarjan_scc(int u){
	dfn[u]=low[u]=++d;
	S.push(u);
	for(int v : edg[u]){
		if( !dfn[v] ) tarjan_scc(v);
		if ( !com[v] ) low[u]=min(low[u], low[v]);
	}
	if( d==low[u] ){
		for(bool f=true; f; S.pop()){
			f= S.top()!=u;
			com[S.top()]=u+1;
		}
	}
}
