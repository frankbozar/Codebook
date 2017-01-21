const double EPS=1e-12, INF=1e12;
int sign(double x){
	return x<-EPS ? -1 : x>EPS ;
}
double get(const vector<double>& coef, double x){
	double ans=0;
	for(int i=coef.size()-1; i>=0; i--)
		ans=ans*x+coef[i];
	return ans;
}
double find(const vector<double>& coef, int n, double lo, double hi){
	int sign_lo=sign(get(coef, lo));
	int sign_hi=sign(get(coef, hi));
	double m=INF;
	if( sign_lo==0 ) return lo;
	if( sign_hi==0 ) return hi;
	if( sign_lo==sign_hi ) return INF;
	for(int step=0; step<100 && hi-lo>EPS; step++){
		m=(hi+lo)*.5;
		int sign_m=sign(get(coef, m));
		if( sign_m==0 ) return m;
		(sign_m*sign_lo<0 ? hi : lo)=m;
	}
	return m;
}
vector<double> equation(vector<double>& coef, int n){
	vector<double> ans;
	if( n==1 )
		return sign(coef[1]) ? vector<double>(1, -coef[0]/coef[1]) : ans ;
	if( !sign(coef[n]) )
		return equation(coef, n-1);
	if( sign(coef[n])<0 )
		for(int i=0; i<=n; i++) coef[i]=-coef[i];
	vector<double> dcoef(n);
	for(int i=1; i<=n; i++) dcoef[i-1]=coef[i]*i;
	vector<double> droot=equation(dcoef, n-1);
	droot.insert(droot.begin(), n&1 ? -INF : INF);
	droot.insert(droot.end(), INF);
	for(int i=1; i<droot.size(); i++){
		double tmp=find(coef, n, droot[i-1], droot[i]);
		if( tmp<INF ) ans.push_back(tmp);
	}
	return ans;
}