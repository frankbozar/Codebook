struct BCC{
	vector<vector<int>> edg, brg;
	vector<int> cut, dfn, low;
	BCC(const vector<vector<int>>& e) : edg(e), cut(e.size(), 0), dfn(e.size(), 0), low(e.size()){}
	void dfs(int u, int p=-1, int d=0){
		dfn[u]=low[u]=++d;
		int cnt=0;
		for(int v : edg[u]){
			if( v!=p && dfn[v]>0 ) low[u]=min(low[u], dfn[v]);
			else if( dfn[v]==0 ){
				cnt++;
				dfs(v, u, d);
				low[u]=min(low[u], low[v]);
				if( d<low[v] ) brg.push_back({u, v});
				if( (p<0 && cnt>1) || (p>=0 && d<=low[v]) ) cut[u]=true;
			}
		}
	}
};
