struct SAT2{
    int n;
    vector<vector<int>> edg;
    vector<int> dfn, low, com;
    stack<int> S;
    SAT2(int _n) : n(_n), edg(n<<1), dfn(n<<1, 0), low(n<<1), com(n<<1, 0){}
    //void tarjan(int u, d=0);
    int trans(int a){
        return abs(a)-1<<1|a<0;
    }
	void add_or(int a, int b){
        a=trans(a), b=trans(b);
		if( a>>1!=b>>1 ){
            edg[a^1].push_back(b);
            edg[b^1].push_back(a);
		}
		else if( a==b )
            edg[a^1].push_back(a);
	}
    void add_xor(int a, int b){
        add_or(a, b);
        add_or(-a, -b);
    }
	bool solve(){
		for(int i=0; i<n<<1; i++) if( !dfn[i] ) tarjan_scc(i);
		for(int i=0; i<n<<1; i++) if( com[i]==com[i^1] ) return false;
		return true;
	}
};
