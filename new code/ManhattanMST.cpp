int N, n, m;
struct PT{int x, y, z, w, id;} p[N];
int dis(const PT& a, const PT& b){return abs(a.x-b.x)+abs(a.y-b.y);}
bool cpx(const PT& a, const PT& b){return a.x!=b.x ? a.x>b.x : a.y>b.y ;}
bool cpz(const PT& a, const PT& b){return a.z<b.z;}
struct E{int a, b, c;} e[N*8];//c is weight
bool operator<(const E& a, const E& b){return a.c<b.c;}
struct Node{int L, R, key;} node[N*4];
int s[N];
void init(int id, int L, int R){
	node[id]={L, R, -1};
	if( L==R ) return;
	init(id*2, L, (L+R)/2); init(id*2+1, (L+R)/2+1, R);
}
void ins(int id, int x){
	if( node[id].key==-1 || p[node[id].key].w>p[x].w ) node[id].key=x;
	if( node[id].L==node[id].R ) return;
	if( p[x].z<=(node[id].L+node[id].R)/2 ) ins(id*2,x);
	else ins(id*2+1,x);
}
int Q(int id, int L, int R){
	if( R<node[id].L || L>node[id].R ) return -1;
	if( L<=node[id].L && node[id].R<=R ) return node[id].key;
	int a=Q(id*2, L, R), b=Q(id*2+1, L, R);
	return b==-1 || a!=-1 && p[a].w<p[b].w ? a : b ;
}
void calc(){
	for(int i=0; i<n; i++) p[i].z=p[i].y-p[i].x, p[i].w=p[i].x+p[i].y;
	sort(p, p+n, cpz);
	int cnt=0;
	for(int j, i=0; i<n; i=j, cnt++){
		for(j=i+1; p[j].z==p[i].z && j<n; j++);
		for(int k=i; k<j; k++) p[k].z=cnt+1;
	}
	init(1, 1, cnt);
	sort(p, p+n, cpx);
	for(int i=0; i<n; i++){
		int j=Q(1, p[i].z, cnt);
		if( j!=-1 ) e[m++]={p[i].id, p[j].id, dis(p[i],p[j])};
		ins(1, i);
	}
}
int main(){
	m=0;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].id=s[i]=i;
	}
	calc(); for(int i=0; i<n; i++) p[i].y= -p[i].y;
	calc(); for(int i=0; i<n; i++) swap(p[i].x,p[i].y);
	calc(); for(int i=0; i<n; i++) p[i].x=-p[i].x;
	calc(); sort(e, e+m);//O(n) edges, need kruskal
}
