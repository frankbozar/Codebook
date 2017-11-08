O(nmK)
n: number of vertices
m: number of edges
a: a[i][2]: edges
co: output
K, A, B, C, D, P: factors
int a[M][2], co[N], f[N], tf[N];
void ghash(){
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++) tf[j]=f[j]=1;
		for(int k=0; k<K; k++){
            for(int j=0; j<n; j++) f[j]*=A;
            for(int j=0; j<m; j++)
            {
                f[ a[j][0] ]+=tf[ a[j][1] ]*B;
                f[ a[j][1] ]+=tf[ a[j][0] ]*C;
            }
            f[i]+=D;
            for(int j=0; j<n; j++) tf[j]=f[j]%=P;
		}
        co[i]=f[i];
	}
    sort(co, co+n);
}
