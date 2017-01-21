struct costflow{
	struct edge{
		int t, f, c, r;//_c, c
		edge(int _t, int _f, int _c, int _r) : t(_t), f(_f), c(_c), r(_r){}
	};
	int n;
	vector<int> prv, plv, dis;//dis
	vector<vector<edge>> e;
	costflow(int _n) : n(_n), prv(n+1), plv(n+1), e(n+1){}
	void add(int u, int v, int f, int c){//c
		e[u].push_back(edge(v, f,  c, e[v].size()));
		e[v].push_back(edge(u, 0, -c, e[u].size()-1));
	}
	edge& rev(const edge& E){
		return e[E.t][E.r];
	}
	bool bfs(int s, int t){
		vector<bool> inq(n+1, false);
		dis.assign(n+1, INF);//INF
		dis[s]=0;
		queue<int> Q;
		for(Q.push(s); !Q.empty(); Q.pop()){
			s=Q.front(), inq[s]=0;
			for(int i=e[s].size()-1; i>=0; i--){
				const edge& E=e[s][i];
				if( dis[E.t]>dis[s]+E.c && E.f>0 ){
					dis[E.t]=dis[s]+E.c;
					prv[E.t]=s, plv[E.t]=i;
					if( !inq[E.t] ) Q.push(E.t), inq[E.t]=true;
				}
			}
		}
		return dis[t]<INF;
	}
	pair<int, int> operator()(int s, int t){//second
		int fl=0, cs=0;//cs
		for(int tf=INF; bfs(s, t); tf=INF){
			for(int v=t, u, l; v!=s; v=u){
				u=prv[v], l=plv[v];
				tf=min(tf, e[u][l].f);
			}
			for(int v=t, u, l; v!=s; v=u){
				u=prv[v], l=plv[v];
				rev(e[u][l]).f+=tf;
				e[u][l].f-=tf;
			}
			cs+=tf*dis[t], fl+=tf;
		}
		return pair<int, int>(fl, cs);//second
	}
};