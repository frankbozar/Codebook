using ld = double;
vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
	ld d2 = (o1 - o2) * (o1 - o2);
	ld d = sqrt(d2);
	if (d < abs(r1-r2)) return {};
	if (d > r1+r2) return {};
	pdd u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
	double A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
	pdd v = A / (2*d2) * pdd(o1.S-o2.S, -o1.F+o2.F);
	return {u+v, u-v};
}
//
pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2, bool &res){
    double f1 = cross(p2, q1, p1);
    double f2 = -cross(p2, q2, p1);
    double f = (f1 + f2);
    if(fabs(f) < EPS) {
        res = false; return {};
    }
    res = true;
    return (f2 / f) * q1 + (f1 / f) * q2;
}
