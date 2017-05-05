vector<vector<int>> edg;
vector<pair<int, int>> brg;
int cut[N]={0}, dfn[N]={0}, low[N];
void tarjan_bcc(int u, int p=-1, int d=0){
	dfn[u]=low[u]=++d;
	int cnt=0;
	for(int v : edg[u]){
		if( v!=p && dfn[v]>0 ) low[u]=min(low[u], dfn[v]);
		else if( dfn[v]==0 ){
			cnt++;
			tarjan_bcc(v, u, d);
			low[u]=min(low[u], low[v]);
			if( d<low[v] ) brg.push_back(pair<int, int>(u, v));
			if( (p<0 && cnt>1) || (p>=0 && d<=low[v]) ) cut[u]=true;
		}
	}
}
