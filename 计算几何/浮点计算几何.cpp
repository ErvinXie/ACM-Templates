
const int MAXN = 1e5+4;
const double PI = acos(-1.0);
const int INF = 0x3f3f3f3f;
const double rad_to_deg = 360/2/PI;
const double deg_to_rad = 2*PI/360;
const double EPS = 1e-6;
int sgn(double x){
    if(abs(x)<EPS)
        return 0;
    else if(x<0)
        return -1;
    else
        return 1;
}
struct Point {
    double x,y;
    bool operator < (const Point& b) const
    {return x<b.x;}
    Point(double x,double y):x(x),y(y){}
    Point(){}
    double sqdis_to(const Point&b){
        return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
    }
    double dis_to(const Point&b){
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }
    double length(){
        return dis_to(Point(0,0));
    }
    Point normalize(){
        return (*this)*(1/length());
    }
    
    friend double operator* (const Point &a,const Point &b) {
        return a.x*b.x+a.y*b.y;
    }
    Point operator * (const double &b) const{
        return Point(x*b,y*b);
    }
    friend Point operator *(double a,const Point &b){
        return Point(b.x*a,b.y*a);
    }
    friend Point operator + (const Point&a,const Point &b) {
        return Point(a.x+b.x,a.y+b.y);
    }
    friend Point operator - (const Point&a,const Point &b){
        return Point(a.x-b.x,a.y-b.y);
    }
    bool operator == (const Point &b) const{
        if(sgn(x-b.x)==0&&sgn(y-b.y)==0)
            return 1;
        return 0;
    }
    double cross_product(const Point&a, const Point &b){
        return (a.x-x)*(b.y-y)-(a.y-y)*(b.x-x);
    }
    double theta(){//和原点连线与x轴正方向的夹角，0～2*PI
        if(sgn(x)==0){
            if(sgn(y)>1)
                return PI/2;
            else if(sgn(y)==0)
                return 0;
            else
                return PI*3/2;
        }else if(sgn(y)==0){
            if(sgn(x)>0)
                return 0;
            else
                return PI;
        }else{
            double t = atan(y/x);
            if(sgn(x)<0)
                return t+PI;
            else{
                if(sgn(y)<0)
                    return t+2*PI;
                else
                    return t;
            }
        }
    }
    Point complex_mul(const Point&b)const{
        return Point(x*b.x-y*b.y,x*b.y+y*b.x);
    }
    Point rotate(double rad){
        return this->complex_mul(unit(rad));
    }
    Point rotate(const Point& b,double rad){
        Point d = *this-b;
        return b+d.rotate(rad);
    }
    static Point unit(double rad){
        return Point(cos(rad),sin(rad));
    }
    void debuge(){
        printf("(%lf %lf)\n",x,y);
    }
};

struct Circle{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,int r):c(c),r(r){}
    int relation(Point p){
        double d = sgn(p.dis_to(c)-r);
        if(d>0)
            return 0;//圆外
        else if(d==0)
            return 1;//圆上
        else
            return 2;//圆内
    }
    int relation(Circle b){
        double dis = c.dis_to(b.c);
        if(sgn(dis-r-b.r)>0){
            return 5;
        }else if(sgn(dis-r-b.r)==0){
            return 4;
        }else{
            double idi = abs(r-b.r);
            if(sgn(dis-idi)>0){
                return 3;
            }else if(sgn(dis-idi)==0){
                return 2;
            }else{
                return 1;
            }
        }
        //5 相离
        //4 外切
        //3 相交
        //2 内切
        //1 内含
    }
    int cross(Circle b,Point &c1,Point &c2){
        int rel = relation(b);
        if(rel==5||rel==1){
            return 0;
        }
        double R=b.r;
        Point dv = c-b.c;
        double t1=asin((R*R-r*r+dv*dv)/(2*R*sqrt(dv*dv))),t2=atan(dv.x/dv.y);
        if(sgn(dv.y)<0) t2-=PI;
        double theta1 = t1-t2,theta2 = PI-t1-t2;
        c1 = b.c+Point(R*cos(theta1),R*sin(theta1));
        c2 = b.c+Point(R*cos(theta2),R*sin(theta2));
        if(rel==4||rel==2)
            return 1;
        else
            return 2;
    }
}


/*三角形外心*/
Point circumcenter(Point A,Point B,Point C)
{
    Point ret;
    double a1=B.x-A.x,b1=B.y-A.y,c1=(a1*a1+b1*b1)/2;
    double a2=C.x-A.x,b2=C.y-A.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    ret.x=A.x+(c1*b2-c2*b1)/d;
    ret.y=A.y+(a1*c2-a2*c1)/d;
    return ret;
}


/*最小覆盖圆 c为圆心，r为半径 */
double min_cover_circle(Point *p,Point &c,int n)
{
    double r;
    random_shuffle(p,p+n);
    c=p[0]; r=0;
    for(int i=1;i<n;i++)
    {
        if(p[i].dis_to(c)>r+EPS)   //第一个点
        {
            c=p[i]; r=0;
            for(int j=0;j<i;j++)
                if(p[j].dis_to(c)>r+EPS)  //第二个点
                {
                    c.x=(p[i].x+p[j].x)/2;
                    c.y=(p[i].y+p[j].y)/2;
                    r=p[j].dis_to(c);
                    for(int k=0;k<j;k++)
                        if(p[k].dis_to(c)>r+EPS)  //第三个点
                        {   //求外接圆圆心，三点必不共线
                            c=circumcenter(p[i],p[j],p[k]);
                            r=p[i].dis_to(c);
                        }
                }
        }
    }
    return r;
}
