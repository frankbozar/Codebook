struct circle{
	point c;
	double r;
	circle(const point& _c, double _r) : c(_c), r(_r){}
	circle(const point& p, const point& q) : c((p+q)*0.5), r((c-p)()*(c-p)()){}
	circle(const point& A, const point& B, const point& C){
		point a=B-A, b=C-A;
		double c1=a()*a()*0.5, c2=b()*b()*0.5;
		double d=a^b;
		double x=A.x+(c1*b.y-c2*a.y)/d;
		double y=A.y+(a.x*c2-b.x*c1)/d;
		c=point(x, y);
		r=(c-A)()*(c-A)();
	}
	bool in(const point& p) const{
		return (p-c)()*(p-c)()<=r+EPS;
	}
};
circle solve(vector<point> p){
	random_shuffle(p.begin(), p.end());
	circle ans(point(), 0);
	for(int n=p.size(), i=0; i<n; i++){
	if( ans.in(p[i]) ) continue;
		ans=circle(p[i], 0);
		for(int j=0; j<i; j++){
			if( ans.in(p[j]) ) continue;
			ans=circle(p[i], p[j]);
			for(int k=0; k<j; k++){
				if( ans.in(p[k]) ) continue;
				ans=circle(p[i], p[j], p[k]);
			}
		}
	}
	ans.r=sqrt(ans.r);
	return ans;
}