#ifndef _BIGNUM_H
#define _BIGNUM_H

#include <string>
#include <iostream>

template<class T>
const T &max(const T &a,const T &b) {return a<b?b:a; }

using namespace std;

class Bignum {
public:
    Bignum(long int a=0):
        _data(new char[32]),
        _sign(a<0),
        _res(32),
        _l(0)
    { 
        a=a<0?-a:a;
        do _data[_l++]=a%10; while(a/=10);
        for(int i=_l;i<_res;++i) _data[i]=0;
    }

    Bignum(const Bignum &b):_data(0) { *this=b; }

    const Bignum &operator=(const Bignum &rhs) {
        set(rhs,rhs._l*2);
        return *this;
    }

    const Bignum &operator+=(const Bignum &rhs) {
        //cout << *this << "+" << rhs << "=";
        if (_sign != rhs._sign) sub(rhs);
        else add(rhs);
        if (isnull(*this)) _sign=false;
        //cout << *this << endl;
        return *this;
    }

    Bignum operator+(const Bignum &rhs) const {
        Bignum a(*this);
        return  a+=rhs;
    }
    
    const Bignum &operator-=(const Bignum &rhs) {
        //cout << *this << "-" << rhs << "=";
        if (_sign != rhs._sign) add(rhs);
        else sub(rhs);
        if (isnull(*this)) _sign=false;
        //cout << *this << endl;
        return *this;
    }

    Bignum operator-(const Bignum &rhs) const {
        Bignum a(*this);
        return  a-=rhs;
    }

    Bignum operator-() const {
        Bignum a(*this);
        a._sign=!a._sign;
        if (isnull(a)) a._sign=false;
        return  a;
    }
     
    const Bignum &operator*=(const Bignum &rhs) {
        return *this=(*this)*rhs;
    }

    Bignum operator*(const Bignum &rhs) const {
        //cout << *this << "*" << rhs << "=";
        Bignum acc,tmp;
        for(int i=rhs._l-1;i>=0;--i) {
            tmp=*this;
            tmp.mul(rhs._data[i]);
            acc.mul(10);
            acc+=tmp;
        }
        acc._sign=_sign^rhs._sign;
        if (isnull(acc)) acc._sign=false;
        //cout << acc << endl;
        return acc;
    }

    const Bignum &operator/=(const Bignum &rhs) {
        //cout << *this << "/" << rhs << "=" << div(rhs,false) << endl;
        return *this=div(rhs,false);
    }

    Bignum operator/(const Bignum &rhs) const {
        //cout << *this << "/" << rhs << "=" << div(rhs,false) << endl;
        return div(rhs,false);
    }

    const Bignum &operator%=(const Bignum &rhs) {
        //cout << *this << "%" << rhs << "=" << div(rhs,true) << endl;
        return *this=div(rhs,true);
    }

    Bignum operator%(const Bignum &rhs) const {
        //cout << *this << "%" << rhs << "=" << div(rhs,true) << endl;
        return  div(rhs,true);
    }
 
    bool operator<(const Bignum &rhs) const {
        if (_sign != rhs._sign) return _sign;
        if (_l!=rhs._l) return (_l<rhs._l) ^ _sign;
        return (*this-rhs)._sign;
    }

    bool operator==(const Bignum &rhs) const {
        if (_sign != rhs._sign) return false;
        if (_l!=rhs._l) return false;
        return isnull(*this-rhs);
    }

    bool operator<=(const Bignum &rhs) const { return !(rhs<*this); }
    bool operator>(const Bignum &rhs) const { return rhs<*this; }
    bool operator>=(const Bignum &rhs) const { return !(*this<rhs); }
    bool operator!=(const Bignum &rhs) const { return !(*this==rhs); }
  
    ~Bignum() { clear(); }

private:
    friend ostream &operator<<(ostream &lhs,const Bignum &rhs);
    friend istream &operator>>(istream &lhs,Bignum &rhs);
    friend Bignum abs(const Bignum &b);
    friend bool isnull(const Bignum &b);
    friend bool nless(const Bignum &a,const Bignum &b);

    void clear() {
        if (_data) delete []_data;
        _data=0;
        _l=_res=0; 
        _sign=false;
    }

    void set(const Bignum &b,int res) {
        int i;
        char *data=new char[res];
        for(i=0;i<b._l;++i) data[i]=b._data[i];
        while(i<res) data[i++]=0;
        if (_data) delete[] _data;
        _sign=b._sign;
        _res=res;
        _l=b._l;
        _data=data;
    }

    void add(const Bignum &rhs) {
        int i;
        if ((i=max(_l,rhs._l)+2)>_res) set(*this,i*2);
        for(i=0;i<rhs._l;++i) _data[i]+=rhs._data[i];
        _l=max(_l,rhs._l);
        fix();
    }

    void sub(const Bignum &rhs) {
        int i;
        if ((i=max(_l,rhs._l)+2)>_res) set(*this,i*2);
        for(i=0;i<rhs._l;++i) _data[i]-=rhs._data[i];
        _l=max(_l,rhs._l);
        fix();
    }

    void mul(char m) {
        int i;
        if ((i=_l+2)>_res) set(*this,i*2);
        for(i=0;i<_l;++i) _data[i]*=m;
        fix();
    }

    Bignum div(const Bignum &d,bool rem) const {
        int i,j;
        if (isnull(d)) throw std::string("Div by null");
        Bignum r,t(*this),td;
        td=abs(d);
        for(i=_l-1;i>=0;--i) {
            r.mul(10);
            r._data[0]=_data[i];
            j=0;
            while(!(r<td)) {
                r.sub(d);
                j++;
            }
            t._data[i]=j;
        }
        r._sign=t._sign=_sign^d._sign;
        r.fix();
        t.fix();
        if (rem) return r;
        return t;
    }

    void fix() {
        int r=0,i;
        for(i=0;i<_l;++i) { 
            _data[i]+=r;
            r=(_data[i]<0)?-1:(_data[i]/10); 
            _data[i]=(_data[i]+10)%10;
        }
        if (r<0) {
            for(i=0;i<_l;++i) _data[i]=9-_data[i];
            _data[0]+=1;
            fix();
            _sign=!_sign;
        } else if (r) _data[_l++]=r;
        while(_l>1 && !_data[_l-1]) --_l;
        if (_l==1 && !_data[0]) _sign=false;
    }

    char *_data;
    bool _sign;
    int _res,_l;
};

ostream & operator<<(ostream &lhs,const Bignum &rhs) {
    if (rhs._sign) lhs << '-';
    for(int i=rhs._l-1;i>=0;--i) lhs << char(rhs._data[i]+'0');
    return lhs;
}

istream & operator>>(istream &lhs,Bignum &rhs) {
		rhs=0;
    char c=' ';
    while(c==' ' || c=='\t' || c==10 || c==13) lhs.get(c);
    bool sign=((c=='-')?(lhs.get(c),true):false);
    while(c>='0' && c<='9') {
        rhs.mul(10);
        rhs._data[0]=c-'0';
        lhs.get(c);
    }
    lhs.putback(c);
    if (rhs!=0) rhs._sign=sign;
    return lhs;
}

Bignum abs(const Bignum &b) {
    Bignum ret(b);
    ret._sign=false;
    return ret;
}

Bignum sqrt(const Bignum &b) {
    Bignum x(1),x1(2);
    while(b<x*x || !(b<x1*x1)) {
        x=(x+b/x)/2;
        x1=x+1;
    }
    return x;
}

bool isnull(const Bignum &b) {
    return b._l==1 && b._data[0]==0;
}

bool nless(const Bignum &a,const Bignum &b) {
    if (a._l!=b._l) return (a._l<b._l);
    return (a-b)._sign;
}

#endif

