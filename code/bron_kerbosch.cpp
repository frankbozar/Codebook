typedef bitset<N> set;
vector<set> c, e;
void BronKerbosch(set R, set P, set X){
	if( P.none() && X.none() ){
		c.push_back(R); return;
	}
	int u=0;
	for(; u<n && !(P|X)[u]; u++);
	set T(1);
	for(int i=0; i<n; i++, T<<=1){
		if( (P&~e[u])[i] ){
			BronKerbosch(R|T, P&e[i], X&e[i]);
			P[i]=false, X[i]=true;
		}
	}
}