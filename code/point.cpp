#include<cmath>

struct point{
    double x,y;
    point(double _x=0, double _y=0) : x(_x), y(_y){}
    point operator+(const point& p) const{//vector sum
        return point(x+p.x, y+p.y);
    }
    point operator-(const point& p) const{//vector difference
        return point(x-p.x, y-p.y);
    }
    point operator*(double s) const{//vector scaling
        return point(x*s, y*s);
    }
    point operator/(double f) const{//vector scaling
        return point(x/f, y/f);
    }
    double operator^(const point& P)const{//cross
        return x*P.y-y*P.x;
    }
    double operator&(const point& P)const{//dot
        return x*P.x+y*P.y;
    }
    double operator()() const{//square of length
        return x*x+y*y;
    }
    bool operator<(const point& P) const{
		return x==P.x ? y<P.y : x<P.x ;
	}
};