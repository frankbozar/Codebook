struct BCC{
	vector<vector<int>> edg, brg;
	vector<int> cut, dfn, low;
	BCC(int n) : edg(n+1), cut(n+1, 0), dfn(n+1, 0), low(n+1){}
	void add(int u, int v){
		edg[u].push_back(v); edg[v].push_back(u);
	}
	void dfs(int u, int p=-1, int d=0){
		dfn[u]=low[u]=++d;
		int cnt=0;
		for(int v : edg[u]){
			if( v!=p && dfn[v]>0 ) low[u]=min(low[u], dfn[v]);
			else if( dfn[v]==0 ){
				cnt++; dfs(v, u, d);
				low[u]=min(low[u], low[v]);
				if( d<low[v] ) brg.push_back({u, v});
				if( p<0 && cnt>1 || p>=0 && d<=low[v] ) cut[u]=true;
			}
		}
	}
};
