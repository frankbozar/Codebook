int phi[n], minDiv[n];
void get_phi(){
	phi[1] = 1;
	for(int i=2; i<n; i++) minDiv[i]=i;
	for(lld i=2; i<n; i++)
		if( minDiv[i]==i )
			for(lld j=i*i; j<n; j+=i) minDiv[j]=i;
	for(int i=2; i<n; i++){
		phi[i]=phi[ i/minDiv[i] ];
		phi[i]*=minDiv[i]-(i/minDiv[i])%minDiv[i]==0 ? 0 : 1);
	}
}