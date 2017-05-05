struct SAT
{
	int n, m, rem, level;
	vector<vector<int>> C, CNT;//0: false, 1: true, 2: unassigned
	vector<int> X, STAT;//0: unassigned, 1: decided, 2: implied
	vector<vector<vector<int>>> POS;//0: false, 1: true
	vector<vector<int>> I;
	vector<int> UNIT;
	vector<vector<int>> ORDER;
	SAT(int _n, vector<vector<int>>& cnf) : n(_n), level(0), C(cnf), I(1){
		m=C.size();
		rem=n;
		for(vector<int> &c : C)
			CNT.push_back({ 0, 0, (int)c.size() });
		X.resize(n + 1);
		STAT.assign(n + 1, 0);
		POS.assign(n + 1, { {}, {} });
		for(int i=0; i<m; i++)
			for(int x : C[i])
				POS[abs(x)][x < 0 ? 0 : 1].push_back(i);
		for(vector<int> &c : C)
			if( c.size()==1 )
				UNIT.push_back(c[0]);
		for(int i=1; i<=n; i++)
			ORDER.push_back({ (int)(POS[i][0].size() + POS[i][1].size()), i });
		sort(ORDER.rbegin(), ORDER.rend());
	}
	bool assign(int x, int val, int stat){//assumption: x is unassigned
		rem--, X[x]=val, STAT[x]=stat;
		bool res=true;
		for(int i=0; i<2; i++)
			for(int c : POS[x][i]){
				CNT[c][2]--, CNT[c][val==i]++;
				if( CNT[c][2]==1 && CNT[c][1]==0 )
					for(int y : C[c])
						if( STAT[abs(y)]==0 ){
							UNIT.push_back(y);
							break;
						}
				res&= !(CNT[c][1]==0 && CNT[c][2]==0);
			}
		return res;
	}
	void unassign(int x){//assumption: x is assigned
		rem++, STAT[x]=0;
		for(int i=0; i<2; i++)
			for(int c : POS[x][i])
				CNT[c][2]++, CNT[c][X[x]==i]--;
	}
	bool imply(){
		while( !UNIT.empty() ){
			int x=UNIT.back(), val=x>0;
			UNIT.pop_back();
			if( STAT[abs(x)]!=0 && X[abs(x)]==val ) continue;
			if( STAT[abs(x)]!=0 && X[abs(x)]!=val ) return false;
			I.back().push_back(abs(x));
			if (!assign(abs(x), val, 2)) return false;
		}
		return true;
	}
	void unimply(){
		for(int x : I.back()) unassign(x);
		I.back().clear();
	}
	bool sol(){
		if( !imply() ) return false;
		if( rem==0 ) return true;
		int x;
		for(int i=0; STAT[ x=ORDER[i][1] ]; i++);
		level++, I.push_back({});
		assign(x, rand()&1, 1);
		if( sol() ) return true;
		unassign(x), unimply(), UNIT.clear();
		assign(x, X[x]^1, 1);
		if( sol() ) return true;
		unassign(x), unimply();
		level--, I.pop_back();
		return false;
	}
};