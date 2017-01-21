struct bit{
	int w, h;//1<=x<=w, 1<=y<=h
	vector<vector<int>> a;
	bit(int w, int h=1) : w(w), h(h), a(w+1, vector<int>(h+1, 0)){}
	void add(int x, int y=1, int val=1){
		for(; x<=w; x+=x&-x)
			for(int yy=y; yy<=h; yy+=yy&-yy)
				a[x][yy]+=val;
	}
	int query(int x, int y=1){
		int res=0;
		for(; x>0; x-=x&-x)
			for(int yy=y; yy>0; yy-=yy&-yy)
				res+=a[x][yy];
		return res;
	}
};