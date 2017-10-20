typedef complex<double> CD;
const double PI=acos(-1);
void fft(CD A[], int lgn, bool inv=false){
	int n=1<<lgn;
	for(int i=0, j=1; j<n-1; j++){
		for(int k=n>>1; k>(i^=k); k>>=1);
		if( j<i ) swap(A[i], A[j]);
	}
	for(int i=1; i<n; i<<=1){
		CD W(1, 0), Wn(cos(PI/i), sin((inv ? -PI : PI)/i));
		for(int j=0; j<n; j++){
			if( j&i ){
				W=CD(1, 0); continue;
			}
			CD x=A[j], y=A[j+i]*W;
			A[j]=x+y; A[j+i]=x-y;
			W*=Wn;
		}
	}
	if( inv ) for(int i=0; i<n; i++) A[i]/=n;
}
