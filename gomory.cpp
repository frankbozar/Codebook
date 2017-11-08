void gomory(vector<vector<int>>& f, vector<int>& p, int n){
    f.assign(n+1, vector<int>(n+1, INF));//all pair min cut
    p.assign(n+1, 1);//tree edge
    for(int s=2; s<=n; s++){
        int t=p[s];
        Dinic F=D;
        int tmp=F(s, t);
        for(int i=1; i<s; i++) f[s][i]=f[i][s]=min(tmp, f[t][i]);
        for(int i=s+1; i<=n; i++) if( p[i]==t && F.l[i]<INF ) p[i]=s;
    }
}
