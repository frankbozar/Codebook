string lsr(string s){
	int n=s.length(), i=0, j=1;
	for(s+=s; i<n && j<n; j+=i==j){
		int k=0;
		while( k<n && s[i+k]==s[j+k] ) k++;
		(s[i+k]<=s[j+k] ? j : i)+=k+1;
	}
	return s.substr(i<n ? i : j, n);
}
