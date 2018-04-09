struct BK{
    int n;//0-base
    vector<bs> e, c;
    BK(int _n) : n(_n), e(n, 0){}
    void operator()(){
        bs P;
        for(int i=0; i<n; i++) P[i]=true;
        bk(0, P, 0);
    }
    void bk(bs R, bs P, bs X){
        if( P.none() && X.none() ){
            c.push_back(R); return;
        }
        int u=0; bs T(1);
        for(; u<n && !(P|X)[u]; u++);
        for(int i=0; i<n; i++, T<<=1){
            if( (P&~e[u])[i] ){
                bk(R|T, P&e[i], X&e[i]);
                P[i]=false, X[i]=true;
            }
        }
    }
};
