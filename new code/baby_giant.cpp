lld solve(lld a, lld b, lld p){
	int sp=ceil(sqrt(p));
	map<lld, int> M;
	lld tmp=1;
	for(int i=0; i<sp && M.find(tmp)==M.end(); i++)
		M[tmp]=i, tmp=tmp*a%p;
	lld x, y;
	ext_gcd(tmp, p, x, y);
	tmp=(x+p)%p;
	for(int i=0; i<sp; i++){
		auto res = M.find(b);
		if( res!=M.end() ) return i*(lld)sp+res->second;
		b=b*tmp%p;
	}
	return -1;
}
