lld ext_gcd(lld a, lld b, lld& x, lld& y){
	if( b==0 ){
		x=1, y=0;
		return a;
	}
	lld g=ext_gcd(b, a%b, y, x);
	y-=x*(a/b);
	return g;
}