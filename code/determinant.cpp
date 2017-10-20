lld det(int n, lld m, vector<vector<lld>> a){
	lld div=1;
	for(int k=n-1; k>0; k--){
		if( a[k][k]==0 ) for(int i=0; i<k; i++) if( a[i][k]!=0 )
			swap(a[i], a[k]), div=m-div;
		for(int i=0; i<k; i++) for(int j=0; j<k; j++)
			a[i][j]=((a[i][j]*a[k][k]-a[i][k]*a[k][j])%m+m)%m;
		div=div*pmd(a[k][k], k-1, m)%m;
	}
	return a[0][0]*inv(div, m)%m;
}
