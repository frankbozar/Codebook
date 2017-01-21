vector<lld> mod_eq(lld a, lld b, lld n){
	lld x, y, g=ext_gcd(a, n, x, y);
	vector<lld> ans;
	if( b%g==0 ){
		x=((x%n)+n)%n;
		ans.push_back(x*(b/g)%(n/g));
		for(lld i=1; i<g; i++)
			ans.push_back((ans[0]+i*n/g)%n);
	}
	return ans;
}