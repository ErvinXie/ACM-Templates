
//------------------手写Complex-----------
#include <cmath>
const int MAXN = 5e5+4;

const double PI = acos(-1.0);
struct complex
{
    double r,i;
    complex(double _r = 0,double _i = 0)
    {
        r = _r; i = _i;
    }
    complex operator +(const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator -(const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator *(const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
void change(complex y[],int len)
{
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++)
    {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
void fft(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j += h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
//----------------FWT----------------inv=1 正转换 inv=-1反转换


void FWT(long long a[],int len,int inv){
    for(int d=1;d<len;d<<=1){
        for(int m=d<<1,i=0;i<len;i+=m){
            for(int j=0;j<d;j++){
                long long x = a[i+j],y=a[i+j+d];
                a[i+j]=x+y;
                a[i+j+d]=x-y;
                if(inv<0){
                    a[i+j]>>=1;
                    a[i+j+d]>>=1;
                }
            }
        }
    }
}
