struct stable{
	int n, m, ans=0;//n: left size, m: right size
	vector<vector<int>> a;//left preference
	vector<int> b, c;//b: left match, c: right capacity
	vector<map<int, int>> M, PQ;//M: right preferencr, PQ: right match
	int operator()(){
		queue<int> Q;
		for(int i=1; i<=n; i++) Q.push(i);
		for(; !Q.empty(); Q.pop()){
			for(int u=Q.front(); !b[u] && !a[u].empty(); a[u].pop_back()){
				int v=a[u].back();
				if( (int)PQ[v].size()<c[v] ){
					PQ[v][ M[v][u] ]=u; b[u]=v; ans++;
				}
				else if( PQ[v].begin()->first<M[v][u] ){
					Q.push(PQ[v].begin()->second);
					b[PQ[v].begin()->second]=0;
					PQ[v].erase(PQ[v].begin());
					PQ[v][ M[v][u] ]=u;
					b[u]=v;
				}
			}
		}
		return ans;
	}
};
