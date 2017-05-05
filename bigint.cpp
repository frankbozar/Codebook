#include<cmath>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long lld;

class bigint
{
    friend ostream& operator<<(ostream&, const bigint&);
    friend istream& operator>>(istream&, bigint&);
    
private:
    bool neg;
    vector<int> val;
    
    void carry()
    {
        val.push_back(0);
        
        for(int i=0; i<length(); i++)
        {
            val[i+1]+=val[i]/10;
            val[i]%=10;
        }
    }
    
    void formalize()
    {
        carry();
        
        while( !val.empty() && val.back()==0 )
            val.pop_back();
        
        if( val.empty() )
            val.assign(1, 0);
        
        if( val.front()==0 )
            neg=false;
    }
    
    int length() const
    {
        return val.size();
    }
    
    int operator[](int i) const
    {
        return i<length() ? val[i] : 0 ;
    }
    
    int& operator[](int i)
    {
        return val[i];
    }
    
    void resize(int n)
    {
        neg=false;
        val.assign(n+1, 0);
    }
    
public:
    bigint(lld _val=0) : val(0)
    {
        neg=false;
        
        if( _val<0 )
            neg=true;
        
        for(_val=abs(_val); _val>0; _val/=10)
            val.push_back(_val%10);
        
        formalize();
    }
    
    bigint operator*(const bigint& b) const
    {
        const bigint& a=*this;
        
        if( a.neg && b.neg )
            return (-a)*(-b);
        else if( a.neg )
            return -((-a)*b);
        else if( b.neg )
            return -(a*(-b));
        
        int n=a.length();
        int m=b.length();
        bigint c;
        c.resize(n+m);
        
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            c[i+j]+=a[i]*b[j];
        
        c.formalize();
        return c;
    }
    
    bigint operator+(const bigint& b) const
    {
        const bigint& a=*this;
        
        if( a.neg && b.neg )
            return -((-a)+(-b));
        else if( a.neg )
            return b-(-a);
        else if( b.neg )
            return a-(-b);
        
        int n=max(a.length(), b.length());
        bigint c;
        c.resize(n);
        
        for(int i=0; i<n; i++)
            c[i]+=a[i]+b[i];
        
        c.formalize();
        return c;
    }
    
    bigint operator-(const bigint& b) const
    {
        const bigint& a=*this;
        
        if( b.neg )
            return a+(-b);
        else if( a.neg )
            return -((-a)+b);
        else if( a<b )
            return -(b-a);
        
        int n=max(a.length(), b.length());
        bigint c;
        c.resize(n);
        
        for(int i=0; i<n; i++)
        {
            c[i]+=a[i]-b[i];
            
            if( c[i]<0 )
            {
                c[i]+=10;
                c[i+1]--;
            }
        }
        
        c.formalize();
        return c;
    }
    
    bigint operator-() const
    {
        bigint b=*this;
        b.neg=!b.neg;
        return b;
    }
    
    bool operator<(const bigint& b) const
    {
        const bigint& a=*this;
        
        if( a.neg && b.neg )
            return (-b)<(-a);
        else if( b.neg )
            return false;
        else if( a.neg )
            return true;
        
        int n=max(a.length(), b.length());
        
        for(int i=0; i<n; i++)
        {
            if( a[i]<b[i] )
                return true;
            else if( b[i]<a[i] )
                return false;
        }
        
        return false;
    }
    
    bool operator>(const bigint& b) const
    {
        const bigint& a=*this;
        return b<a;
    }
    
    bool operator!=(const bigint& b) const
    {
        const bigint& a=*this;
        return a<b || b<a ;
    }
    
    bool operator==(const bigint& b) const
    {
        const bigint& a=*this;
        return !(a<b) && !(b<a);
    }
    
    bool operator<=(const bigint& b) const
    {
        const bigint& a=*this;
        return !(b<a);
    }
    
    bool operator>=(const bigint& b) const
    {
        const bigint& a=*this;
        return !(a<b);
    }
};

ostream& operator<<(ostream& out, const bigint& b)
{
    if( b.neg )
        cout << "-" ;
    
    for(int i=b.length()-1; i>=0; i--)
        cout << b[i] ;
    
    return out;
}

istream& operator>>(istream& in, bigint& b)
{
    string s;
    in >> s ;
    b.resize(s.length());
    
    if( s.front()=='-' )
    {
        b.neg=true;
        s=s.substr(1);
    }
    
    int n=s.length();
    
    for(int i=0; i<n; i++)
        b[i]=s[n-i-1]-'0';
    
    b.formalize();
    return in;
}

int main()
{
    
    for(int n; scanf("%d", &n) && n>0; )
    {
        bigint a(1);
        
        for(int i=1; i<=n; i++)
            a=a*i;
        
        cout << a << endl ;
    }
}
