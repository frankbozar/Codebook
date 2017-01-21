bool test(lld n, lld a, lld d){
	if( n==a ) return true;
	while( !(d&1) ) d>>=1;
	lld t=pow_mod(a, d, n);//a^d(mod n)
	while( d!=n-1 && t!=1 && t!=n-1 )
		t=t*t%n, d<<=1;
	return t==n-1 || d&1;
}
bool is_prime(lld n){
	if( n<2 ) return false;
	if( n<4 ) return true;
	if( !(n&1) ) return false;
	//int a[3]={2, 7, 61};//for int n
	int a[12]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for(int i=0; i<12; i++)
		if( !test(n, a[i], n-1) ) return false;
	return true;
}