int phi[n], div[n];
void get_phi(){
	phi[1] = 1;
	for(int i=2; i<n; i++) div[i]=i;
	for(lld i=2; i<n; i++) if( div[i]==i )
		for(lld j=i*i; j<n; j+=i) div[j]=i;
	for(int i=2; i<n; i++){
		phi[i]=phi[ i/div[i] ];
		phi[i]*=div[i]-(i/div[i]%div[i]==0 ? 0 : 1);
	}
}
