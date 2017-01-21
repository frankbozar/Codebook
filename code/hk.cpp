struct HK{
	int n, m;
	vector<int> d, p;
	vector<vector<int>> e;
	HK(const int _n, const int _m) : n(_n), m(_m), e(n+m+1){}
	void add_edge(int u, int v){
		e[u].push_back(n+v);
		e[n+v].push_back(u);
	}
	bool bfs(){
		d.assign(n+m+1, INF);
		queue<int> Q;
		for(int i=1; i<=n; i++)
			if( p[i]==0 ){
				d[i]=0;
				Q.push(i);
			}
		for(; !Q.empty(); Q.pop()){
			int u=Q.front();
			if( d[u]>d[0] ) break;
			for(int v : e[u])
				if( d[ p[v] ]==INF ){
					d[ p[v] ]=d[u]+1;
					Q.push(p[v]);
				}
		}
		return d[0]<INF;
	}
	bool dfs(int u){
		if( u==0 ) return true;
		for(auto v : e[u])
			if( d[ p[v] ]==d[u]+1 && dfs(p[v]) ){
				p[v]=u, p[u]=v;
				return true;
			}
		d[u]=INF;
		return false;
	}
	int operator()(){
		int ans=0;
		p.assign(n+m+1, 0);
		while( bfs() )
			for(int i=1; i<=n; i++)
				if( p[i]==0 && dfs(i) )
					ans++;
		return ans;
	}
};