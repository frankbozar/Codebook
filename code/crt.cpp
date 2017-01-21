lld CRT(int n, lld a[], lld m[]){
	for(int i=1; i<n; i++){
		lld x, y, g=ext_gcd(m[i-1], m[i], x, y);
		lld r=a[i]-a[i-1];
		if( r%g!=0 ) return -1;
		lld t=m[i]/g;
		x=(r/g*x%t+t)%t;
		a[i]=a[i-1]+m[i-1]*x;
		m[i]=m[i-1]*t;
	}
	return a[n-1];
}