vector<vector<int>> edg;
vector<pair<int, int>> brg;
int cut[N], dfn[N], low[N];
void bridge_cut(int u, int p=-1, int d=0){
	dfn[u]=low[u]=d;
	int cnt=0;
	for(int v : edg[u]){
		if( v!=p && dfn[v]>=0 )
			low[u]=min(low[u], dfn[v]);
		else if( dfn[v]<0 ){
			bridge_cut(v, u, d+1);
			cnt++;
			low[u]=min(low[u], low[v]);
			if( (p<0 && cnt>1) || (p>=0 && dfn[u]<=low[v]) ) cut[u]=true;
			if( dfn[u]<low[v] ) brg.push_back(pair<int, int>(u, v));
		}
	}
}