#include<cstdlib>

#include<cstdio>
#include<iostream>
using namespace std;

template<class T, int N>
struct matrix
{
    static const int n=N>>1;
    T a[N][N];
    
    matrix<T, N>()
    {
        cerr << "helo" << endl ;
    }
    
    T* operator[](int i)
    {
        return &a[i][0];
    }
    
    const T* operator[](int i) const
    {
        return &a[i][0];
    }
    
    void read(int k=N)
    {
        ios::sync_with_stdio(false);
        
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
                a[i][j]=0;
            
            a[i][i]=static_cast<T>(1);
        }
        
        for(int i=0; i<k; i++)
            for(int j=0; j<k; j++)
                a[i][j]=rand()%10;//cin >> a[i][j];
    }
    
    matrix<T, N> operator*(const matrix<T, N>& B) const
    {
        const matrix<T, N>& A=*this;
        const matrix<T, n> A11=A(0, 0);
        const matrix<T, n> A12=A(0, 1);
        const matrix<T, n> A21=A(1, 0);
        const matrix<T, n> A22=A(2, 2);
        
        const matrix<T, n> B11=B(0, 0);
        const matrix<T, n> B12=B(0, 1);
        const matrix<T, n> B21=B(1, 0);
        const matrix<T, n> B22=B(2, 2);
        
        const matrix<T, n> M1=(A11+A22)*(B11+B22);
        const matrix<T, n> M2=(A21+A22)*(B11    );
        const matrix<T, n> M3=(A11    )*(B12-B22);
        const matrix<T, n> M4=(A22    )*(B21-B11);
        const matrix<T, n> M5=(A11+A12)*(B22    );
        const matrix<T, n> M6=(A21-A11)*(B11+B12);
        const matrix<T, n> M7=(A12-A22)*(B21+B22);
        
        matrix<T, N> C;
        C(0, 0, M1+M4-M5+M7);
        C(0, 1, M3+M5);
        C(1, 0, M2+M4);
        C(1, 1, M1-M2+M3+M6);
        return C;
    }
    
    void operator()(int x, int y, const matrix<T, n>& M)
    {
        int k= x ? n : 0 ;
        int l= y ? n : 0 ;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                a[i+k][j+l]=M[i][j];
    }
    
    matrix<T, n> operator()(int x, int y) const
    {
        matrix<T, n> ans;
        int k= x ? n : 0 ;
        int l= y ? n : 0 ;
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                ans[i][j]=a[i+k][j+l];
        
        return ans;
    }
    
    matrix<T, N> operator+(const matrix<T, N>& M) const
    {
        matrix<T, N> ans;
        
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                ans[i][j]=a[i][j]+M[i][j];
        
        return ans;
    }
    
    matrix<T, N> operator-(const matrix<T, N>& M) const
    {
        matrix<T, N> ans;
        
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                ans[i][j]=a[i][j]-M[i][j];
        
        return ans;
    }
};

template<class T>
struct matrix<T, 64>
{
    static const int N=64;
    T a[N][N];
    
    T* operator[](int i)
    {
        return &a[i][0];
    }
    
    const T* operator[](int i) const
    {
        return &a[i][0];
    }
    
    matrix<T, N> operator*(const matrix<T, N>& B) const
    {
        matrix<T, N> C;
        
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
            {
                C[i][j]=0;
                
                for(int k=0; k<N; k++)
                    C[i][j]+=a[i][k]*B[k][j];
            }
        
        return C;
    }
    
    matrix<T, N> operator+(const matrix<T, N>& M) const
    {
        matrix<T, N> ans;
        
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                ans[i][j]=a[i][j]+M[i][j];
        
        return ans;
    }
    
    matrix<T, N> operator-(const matrix<T, N>& M) const
    {
        matrix<T, N> ans;
        
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                ans[i][j]=a[i][j]-M[i][j];
        
        return ans;
    }
};

const int N=256;
matrix<int, N> A, B, C;

int main()
{
    int n;
    scanf("%d", &n);
    
    A.read(n);
    B.read(n);
    
    A=A*B;
    /*
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cout << C[i][j] << (j==n-1 ? '\n' : ' ') ;
    
    cout << endl ;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            int ans=0;
            
            for(int k=0; k<n; k++)
                ans+=A[i][k]*B[k][j];
            
            cout << ans << (j==n-1 ? '\n' : ' ') ;
        }
     */
}
