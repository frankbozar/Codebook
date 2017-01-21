void solve(const char* s){
	int l=strlen(s);
	vector<int> p(l+1, 1);
	for(int c=0, r=0, n=0, m=0, i=1; i<l; i++)
	{
		int j=(c<<1)-i;
		if( i>r )
			p[i]=0, n=i+1, m=i-1;
		else if( p[j]<r-i )
			p[i]=p[j], m=-1;
		else
			p[i]=r-i, n=r+1, m=(i<<1)-n;
		while( n<l && m>=0 && s[m]==s[n] )
			p[i]++, n++, m--;
		if( i+p[i]>r )
			c=i, r=i+p[i];
	}
}