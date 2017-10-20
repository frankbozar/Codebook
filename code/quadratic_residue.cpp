lld solve(lld a, lld p){
	if( a%p==0 ) return 0;
	lld q=p-1, z=1, s=0;
	for(; q>0 && !(q&1); q>>=1) s++;
	for(; pmd(z, p>>1, p)!=p-1; z=rnd(1, p));//rnd(l, r): [l, r)
	lld c=pmd(z, q, p), t=pmd(a, q, p), r=pmd(a, (q+1)>>1, p);
	for(lld i=1; t!=1; i=1){
		for(lld tt=t*t%p; i<s && tt!=1; i++, tt=tt*tt%p);
		if( i==s ) return -1;
		lld b=pmd(c, pmd(2, s-i-1, p), p);
		s=i; c=b*b%p; t=t*c%p; r=r*b%p;
	}
	return r;
}
