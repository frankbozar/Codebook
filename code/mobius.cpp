int mu[n]={0};
void get_mu(){
	mu[1]=-1;
	for(int i=1; i<n; i++){
		mu[i]=-mu[i];
		for(int j=i<<1; j<n; j+=i) mu[j]+=mu[i];
	}
}