struct Graph{
	int n;
	vector<vector<int>> edge;//0-base
	vector<int> match, dis, ons, stk;
	Graph(int _n) : n(_n), edge(n, vector<int>(n, 0)), match(n){}
	void add_edge(int u, int v, int w){
		edge[u][v]=edge[v][u]=w;
	}
	bool SPFA(int u){
		if( ons[u] ) return true;
		stk.push_back(u); ons[u]=1;
		for(int v=0; v<n; v++){
			if( u!=v && match[u]!=v && !ons[v] ){
				int m=match[v];
				if( dis[m]>dis[u]-edge[v][m]+edge[u][v] ){
					dis[m]=dis[u]-edge[v][m]+edge[u][v];
					stk.push_back(v); ons[v]=1;
					if( SPFA(m) ) return true;
					stk.pop_back(); ons[v]=0;
				}
			}
		}
		stk.pop_back(); ons[u]=0; return false;
	}
	int operator()(){
		for (int i=0; i<n; i+=2) match[i]=i+1, match[i+1]=i;
		for(bool found=true; found; ){
			found=false; dis.assign(n, 0); ons.assign(n, 0);
			for(int i=0; i<n; i++){
				stk.clear();
				if( !ons[i] && SPFA(i) )
					for(found=true; stk.size()>=2; ){
						int u=stk.back(); stk.pop_back();
						int v=stk.back(); stk.pop_back();
						match[u]=v; match[v]=u;
					}
			}
		}
		int ans=0;
		for(int i=0; i<n; i++) ans+=edge[i][ match[i] ];
		return ans>>1;
	}
};
