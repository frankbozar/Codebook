inline lld f(lld x, lld n) {
	return (x*x+1)%n;
}
lld rho_fact(lld n) {
	for(lld x=2, y=2; ; ){
		x=f(x, n), y=f(f(y, n), n);
		lld d=gcd(abs(x-y), n);
		if( d>1 ) return d==n ? -1 : d ;
	}
}