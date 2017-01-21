#include<bitset>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1<<20;//sum of all mumbers

struct SSS{
    int tot;
    bitset<N> ok;
    SSS(const vector<int>& a) : tot(0), ok(1){
        vector<int> c(N, 0);
        for(int x : a) tot+=x, c[x]++;
        for(int sum=0, i=1; i<=tot>>1; i++) if( c[i]>0 ){
            for(int m=min(tot>>1, sum+=i*c[i]), j=max(m-i+1, 1); j<=m; j++){
                int cnt=0;
                for(int k=0; k<c[i] && j>=i*k; k++) cnt+=ok[j-i*k];
                for(int k=j; k>0; k-=i){
                    cnt-=ok[k];
                    if( k>=i*c[i] ) cnt+=ok[k-i*c[i]];
                    if( cnt>0 ) ok[k]=true;
                }
            }
        }
    }
    bool operator[](int n) const{
        return n<0 || n>tot ? false : ok[min(n, tot-n)];
    }
};
