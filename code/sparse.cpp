const double EPS=1e-8;
const int N=10;
struct ST
{
	int n, m, a[N][N][1<<N][1<<N];
	void init(int _n, int _m){
		n=_n, m=_m;
		memset(a, 0, sizeof(a));
		for(int i=0; i<n; i++)
			for (int j=0; j<m; j++)
				scanf("%d", &a[0][0][i][j]);
		for(int u=1; u<=lg(n); u++){
			int u2=1<<u, u3=u2>>1;
			for(int i=0; i+u2<=n; i++)
				for (int j=0; j<m; j++)
					a[u][0][i][j]=max(a[u-1][0][i][j], a[u-1][0][i+u3][j]);
		}
		for(int u=0; u<=lg(n); u++)
			for(int v=1; v<=lg(m); v++){
				int u2=1<<u, v2=1<<v, v3=v2>>1;
				for(int i=0; i+u2<=n; i++)
					for(int j=0; j+v2<=m; j++)
						a[u][v][i][j]=max(a[u][v-1][i][j], a[u][v-1][i][j + v3]);
			}
	}
	int query(int l, int r, int u, int d){//[l, r)*[u, d)
		int x=lg(d-u), x2=1<<x;
		int y=lg(r-l), y2=1<<y;
		int maxv=max(a[x][y][u][l], a[x][y][d-x2][l]);
		maxv=max(maxv, a[x][y][u][r-y2]);
		return max(maxv, a[x][y][d-x2][r-y2]);
	}
	static int lg(double x){
		return log2(x)+EPS;
	}
} st;