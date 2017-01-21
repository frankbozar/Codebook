struct suffixarray{
	char s[N];
	int rk[2][N], id[2][N], n, p, cnt[N], len[N], od[N], sar[N];
	struct comp{
		char *s;
		bool operator()(int i, int j) const{
			return s[i]<s[j];
		}
	} cmp;
	suffixarray(){
		scanf("%s", s);
		cmp.s=s;
		n=strlen(s), p=0;
		sa(); lcp();
    }
	int sr(int i, int t) const{//rank of shifted position
		return i+t<n ? rk[p][i+t] : -1 ;
	}
	bool check_same(int i, int j, int t) const{
		return rk[p][i]==rk[p][j] && sr(i,t)==sr(j,t) ;
	}
	void sa(){//length of array s
		memset(cnt, 0, sizeof(cnt));
		for(int i=0; i<n; i++){
			id[p][i]=i;
			rk[p][i]=s[i];
			cnt[ s[i] ]++;
		}
		for(int i=1; i<128; i++) cnt[i]+=cnt[i-1];
		sort(id[p], id[p]+n, cmp);
		for(int t=1; t<n; t<<=1){//least significant bit is already sorted
			for(int i=n-1;i>=0;i--){
				int now=id[p][i]-t;
				if( now>=0 ) id[p^1][ --cnt[ rk[p][now] ] ]=now;
            }
			for(int i=n-t; i<n; i++)
				id[p^1][ --cnt[ rk[p][i] ] ]=i;
			memset(cnt, 0, sizeof(cnt));
			int now=id[p^1][0];
            rk[p^1][now]=0;
            cnt[0]++;
			for(int i=1; i<n; i++){
				int pre=now;
				now=id[p^1][i];
				if( check_same(pre,now,t) )
					rk[p^1][now]=rk[p^1][pre];
				else
					rk[p^1][now]=rk[p^1][pre]+1;
				cnt[ rk[p^1][now] ]++;
			}
			p^=1;
			if(rk[p][now]==n-1) break;
			for(int i=1; i<n; i++) cnt[i]+=cnt[i-1];
		}
		memcpy(sar, id[p], sizeof(sar));
	}
	void lcp(){
        for(int i=0; i<n; i++) od[ sar[i] ]=i;
        for(int l=0, i=0; i<n; i++){
			l=!i ? 0 : len[ od[i-1] ] ? len[ od[i-1] ]-1 : 0 ;
			if( od[i] ){
				int pre=sar[ od[i]-1 ];
				while( pre+l<n && i+l<n && s[pre+l]==s[i+l] ) l++;
				len[ od[i] ]=l;
			}
			else len[0]=0;
		}
	}
};