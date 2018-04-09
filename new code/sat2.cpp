struct SAT2{
	int n; SCC S;//0-base
	vector<int> x;
	SAT2(int _n) : n(_n), S(n<<1), x(n+1, 0){}
	int trans(int a){ return abs(a)-1<<1|a<0; }
	int rev(int a){ return (a>>1)+1; }
	void add_or(int a, int b){
		a=trans(a), b=trans(b);
		if( a>>1!=b>>1 ){
			S.add(a^1, b); S.add(b^1, a);
		}
		else if( a==b ) S.add(a^1, a);
	}
	void add_xor(int a, int b){
		add_or(a, b); add_or(-a, -b);
	}
	bool operator()(){
		S();
		for(int i=0; i<n<<1; i+=2) if( S.com[i]==S.com[i^1] ) return false;
		vector<vector<int>> edg(n<<1), var(n<<1);//generate one solution
		vector<bool> flg(n<<1, true);
		vector<int> deg(n<<1, 0);
		queue<int> Q;
		for(int u=0; u<n<<1; u++){
			var[ S.com[u]-1 ].push_back(u);
			for(int v : S.edg[u]) if( S.com[u]!=S.com[v] ){
				edg[ S.com[v]-1 ].push_back(S.com[u]-1);
				deg[ S.com[u]-1 ]++;
			}
		}
		for(int i=0; i<n<<1; i++) if( deg[i]==0 ) Q.push(i);
		for(; !Q.empty(); Q.pop()){
			int u=Q.front();
			for(int v : var[u]) if( (v&1 ? 1 : -1)*x[rev(v)]>0 ) flg[u]=false;
			for(int v : var[u]) x[rev(v)]=(v^flg[u])&1 ? 1 : -1 ;
			for(int v : edg[u]){
				flg[v]=flg[v]&&flg[u]; if( --deg[v]==0 ) Q.push(v);
			}
		}
		return true;
	}
};
