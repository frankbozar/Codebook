struct BF{
	struct edge{//directed edge u->v
		int u, v, w;
		edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w){}
	};
	int n;
	vector<int> d;
	vector<edge> e;
	BF(int _n) : n(_n){}//zero-base vertices
	void add(int u, int v, int w){//add an edge
		e.push_back(edge(u, v, w));
	}
	bool relax(){//does relaxation with all edges once
		bool any=false;
		for(const edge& E : e)
			if( d[E.v]>d[E.u]+E.w ) d[E.v]=d[E.u]+E.w, any=true;
		return any;
	}
	void operator()(int s){//compute SSSP start with s
		d.assign(n, INF); d[s]=0;
		for(int i=1; i<n; i++) if( !relax() ) break;
	}
	bool neg_cycle(){//detect negative cycle
		d.assign(n, 0);
		for(int i=0; i<n; i++) if( !relax() ) return false;
		return relax();
	}
	double karp_mmc(){//calculate the min mean cycle ratio
		double ans=INF;
		vector<vector<int>> d(n+1, vector<int>(n, INF));
		d[0].assign(n, 0);
		for(int i=1; i<=n; i++) for(const edge& E : e)
			d[i][E.v]=min(d[i][E.v], d[i-1][E.u]+E.w);
		for(int i=0; i<n; i++){
			double tmp=-INF;
			if( d[n][i]>=INF ) continue;
			for(int j=0; j<n; j++)
				tmp=max(tmp, (d[n][i]-d[j][i])/(double)(n-j));
			ans=min(ans, tmp);
		}
		return ans;
	}
};