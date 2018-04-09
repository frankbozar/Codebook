struct BCC{
	int n, cnt=0;
	stack<int> S;
	vector<vector<int>> edg, brg;
	vector<int> cut, dfn, low, com;
	BCC(int _n) : n(_n), edg(n+1), cut(n+1, 0), dfn(n+1, 0), low(n+1), com(n+1){}
	void add(int u, int v){
		edg[u].push_back(v); edg[v].push_back(u);
	}
	void dfs(int u, int p=-1, int d=0){
		S.push(u); dfn[u]=low[u]=++d; int child=0;
		for(int v : edg[u]){
			if( v!=p && dfn[v]>0 ) low[u]=min(low[u], dfn[v]);
			else if( dfn[v]==0 ){ child++;
				dfs(v, u, d); low[u]=min(low[u], low[v]);
				if( d<low[v] ){
					cnt++; brg.push_back({u, v});
					for(int w; w=S.top(), S.pop(), com[w]=cnt, w!=v; );
				}
				if( p<0 && child>1 || p>=0 && d<=low[v] ) cut[u]=true;
			}
		}
	}
	void operator()(){
		for(int i=0; i<n; i++) if( !dfn[i] )//0-base or 1-base
			for(dfs(i), cnt++; !S.empty(); S.pop()) com[S.top()]=cnt;
	}
};
