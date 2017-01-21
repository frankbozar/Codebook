void failure(char *s, int f[]){
	f[0]=-1;
	for(int k, m=strlen(s), i=1; i<=m; i++){
		for(k=f[i-1]; k>=0 && s[k]!=s[i-1]; k=f[k]);
		f[i]=k+1;
	}
}
vector<int> KMP(char* s, char* t){//search for s in t
	int m=strlen(s), n=strlen(t), f[m+1];
	failure(s, f);
	vector<int> result;
	for(int k=0, i=0; i<n; ){
		if( k==-1 ) i++, k=0;
		else if( t[i]==s[k] ){
			i++, k++;
            if(k==m){
				result.push_back(i-m);
				k=f[k];
			}
		}else k=f[k];
	}
	return result;
}