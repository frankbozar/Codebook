vector<point> convex_hull(vector<point> p){
	int n=p.size(), k=0;
	vector<point> h(n<<1);
	sort(p.begin(), p.end());
	for (int i=0; i<n; i++){//cross
		for(; k>=2 && (h[k-1]-h[k-2])/(p[i]-h[k-1])<=0; k--);
		h[k++]=p[i];
	}
	for (int t=k, i=n-2; i>=0; i--){//cross
		for(; k>t && (h[k-1]-h[k-2])/(p[i]-h[k-1])<=0; k--);
		h[k++]=p[i];
	}
	h.resize(k);
	return h;
}
