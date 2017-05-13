#include<cmath>
#include<algorithm>
using namespace std;


#include<complex>
typedef complex<long double> cplx;
const double PI=acos(-1);
const int N=20, MAXN=1<<N;

struct fft{
    cplx omega[MAXN+1];
    fft(){
        for(int i=0; i<=MAXN; i++) omega[i]=cplx(cos(i*PI*2/MAXN), sin(i*PI*2/MAXN));
    }
    void operator()(cplx a[], int t, bool rev=false){
        int n=1<<t;
        for(int j=0, i=0; i<n; i++){
            if( j<i ) swap(a[i], a[j]);
            for(int k=n>>1; (j^=k)<k; k>>=1);
        }
        for(int d=t-1, i=2; i<=n; i<<=1, d--){
            int m=i>>1;
            for(int j=0; j<n; j+=i) for(int k=0; k<m; k++){
                const cplx& w=omega[ rev ? MAXN-(k<<d) : (k<<d) ];
                cplx z=a[j+m+k]*w; a[j+m+k]=a[j+k]-z; a[j+k]+=z;
            }
        }
        if( rev ) for(int i=0; i<n; i++) a[i]/=n;
    }
} F;

const int n=18;
cplx ans[1<<n], t[4][1<<n];
const char *s="SHCD";

int main()
{
    for(int a, b, c; scanf("%d%d%d", &a, &b, &c) && (a||b||c); )
    {
        for(int i=0; i<4; i++)
        {
            t[i][0]=0;
            
            for(int j=1; j<10; j++)
                t[i][j]=1;
        }
        
        for(int i=0; i<1<<n; i++)
            ans[i]=0;
        
        for(ans[0]=1; c>0; c--)
        {
            int x;
            char y;
            scanf("%d%c", &x, &y);
            
            for(int i=0; i<4; i++)
                if( s[i]==y )
                    t[i][x]=0;
        }
        
        for(int i=0; i<4; i++)
        {
            for(int i=0; i<10; i++)
                printf("%.0Lf ", ans[i].real());
            printf("\n");
            
            F(ans, n);
            F(ans, n, true);
            
            for(int i=0; i<10; i++)
                printf("%.0Lf ", ans[i].real());
            printf("\n");
            
            F(ans, n);
            
            F(t[i], n);
            
            for(int j=0; j<1<<n; j++)
                ans[j]*=t[i][j];
            
            F(ans, n, true);
            
            for(int j=1<<n-1; j<1<<n; j++)
                ans[j]=0;
        }
        
        for(int i=a; i<=b; i++)
            printf("%.0Lf\n", fabs(ans[i].real()));
    }
}

/*

12 20 2
4S 6H
0 0 0

*/
