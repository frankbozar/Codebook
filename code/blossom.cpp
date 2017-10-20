struct Graph{
	int n, st, ed, nb, ans=0;
	vector<vector<int>> edg;//1-base
	vector<int> pr, bk, ds;
	vector<bool> inq, inp, inb;
	queue<int> Q;
	Graph(int _n) : n(_n), edg(n+1), pr(n+1, 0), ds(n+1){}
	void add_edge(int u, int v){
		edg[u].push_back(v); edg[v].push_back(u);
	}
	int lca(int u, int v){
		inp.assign(n+1, false);
		for(u=ds[u]; ; u=ds[ bk[ pr[u] ] ]){
			inp[u]=true;
			if( u==st ) break;
		}
		for(v=ds[v]; !inp[v]; v=ds[ bk[ pr[v] ] ]);
		return v;
	}
	void upd(int u){
		while( ds[u]!=nb ){
			int v=pr[u];
			inb[ ds[u] ]=inb[ ds[v] ]=true;
			u=bk[v];
			if( ds[u]!=nb ) bk[u]=v;
		}
	}
	void blo(int u, int v){
		nb=lca(u, v);
		inb.assign(n+1, false);
		upd(u); upd(v);
		if( ds[u]!=nb ) bk[u]=v;
		if( ds[v]!=nb ) bk[v]=u;
		for(int tu=1; tu<=n; tu++) if( inb[ ds[tu] ] ){
			ds[tu]=nb;
			if( !inq[tu] ){ Q.push(tu); inq[tu]=true; }
		}
	}
	void flo()
	{
		bk.assign(n+1, 0);
		inq.assign(n+1, false);
		inq[st]=true;
		for(int i=1; i<=n; i++) ds[i]=i;
		for(ed=0; !Q.empty() ; Q.pop());
		for(Q.push(st); !Q.empty(); Q.pop()){
			int u=Q.front();
			for(int v : edg[u]) if( ds[u]!=ds[v] && pr[u]!=v ){
				if( v==st || pr[v]>0 && bk[ pr[v] ]>0 ) blo(u, v);
				else if( bk[v]==0 ){
					bk[v]=u;
					if( pr[v]<=0 ){ ed=v; return ;
					} else if( pr[v]>0 && !inq[ pr[v] ] ) Q.push(pr[v]);
				}
			}
		}
	}
	void aug(){
		for(int w, v, u=ed; u>0; u=w){
			v=bk[u]; w=pr[v];
			pr[v]=u; pr[u]=v;
		}
	}
	int operator()(){
		for(int u=1; u<=n; u++) if( pr[u]==0 )
		{
			st=u; flo();
			if( ed>0 ){
				aug(); ans++;
			}
		}
		return ans;
	}
};
