//d[] input degree sequence, sorted in non-increasing order, counting sort
//first check all d<n and sum(d) is even
//https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem
bool check(int d[], int n){
    int sum=0, m=0, a[N]={0}, b[N];//large n: lld sum, global a&b, clear a
    for(int i=0; i<n; i++){
        if( d[i]>=n ) return false;
        sum+=d[i], a[ d[i] ]++;
    }
    if( sum&1 ) return false;
    for(int i=n-1; i>0; i--) for(; a[i]>0; a[i]--) b[m++]=i;
    for(int l=0, r=0, i=m-1, k=0; k<m; k++){
        r+=(k<<1)+max(i-k, 0)-min(b[k], k);
        for(l+=b[k]; i>k && b[i]<=k; i--) r--;
        if( l>r ) return false;
    }
    return true;
}
