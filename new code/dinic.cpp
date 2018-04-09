struct Dinic{
	struct edge{
		int t, c, r;
		edge(int _t, int _c, int _r): t(_t), c(_c), r(_r){}
	};
	vector<int> l, nxt;
	vector<vector<edge>> e;
	Dinic(int n) : e(n+1){}
	void add(int u, int v, int w){//directed
		e[u].push_back(edge(v, w, e[v].size()));
		e[v].push_back(edge(u, 0, e[u].size()-1));
	}
	edge& rev(const edge& E){
		return e[E.t][E.r];
	}
	bool bfs(int s, int t){
		l.assign(e.size(), INF);
		l[s]=1;
		queue<int> Q;
		for(Q.push(s); !Q.empty(); Q.pop()){
			s=Q.front();
			for(const edge& E : e[s])
				if( E.c>0 && l[E.t]>l[s]+1 ){
					l[E.t]=l[s]+1; Q.push(E.t);
				}
		}
		return l[t]<INF;
	}
	int dfs(int s, int t, int num=INF){
		if( s==t || num==0 ) return num;
		int ans=0;
		for(int& i=nxt[s]; num && i<e[s].size(); i+=num>0){
			edge& E=e[s][i];
			if( E.c>0 && l[s]+1==l[E.t] ){
				int tmp=dfs(E.t, t, min(num, E.c));
				rev(E).c+=tmp, ans+=tmp;
				E.c-=tmp, num-=tmp;
			}
		}
		return ans>0 ? ans : l[s]=0;
	}
	int operator()(int s, int t){
		int ans=0;
		for(; bfs(s, t); ans+=dfs(s, t)) nxt.assign(e.size(), 0);
		return ans;
	}
};
