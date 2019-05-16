const int MAXN = 5e4+4;
const int INF = 0x3f3f3f3f;

struct Point {
    int x,y;
    
    bool operator < (const Point& b) const
    {return x<b.x;}
    
    Point(int x,int y):x(x),y(y){}
    Point(){}
    int sqdis_to(const Point&b)
    {
        return (x-b.x)*(x-b.x)+(y-b.y)*(y-b.y);
    }
    Point operator + (const int &b)const
    {
        return Point(x*b,y*b);
    }
    int operator * (const Point &b) const
    {
        return x*b.x+y*b.y;
    }
    int operator % (const Point &b)const
    {
        return x*b.y-y*b.x;
    }
    Point operator + (const Point &b) const
    {
        return Point(x+b.x,y+b.y);
    }
    Point operator - (const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    bool operator == (const Point &b) const
    {
        if(x==b.x&&y==b.y)
            return 1;
        return 0;
    }
    int cross_product(const Point&a, const Point &b)
    {
        return (a.x-x)*(b.y-y)-(a.y-y)*(b.x-x);
    }
    
    void debug()
    {
        printf("(%d %d)\n",x,y);
    }
}p[MAXN];

//极角排序
Point O;
bool rotate_cmp(Point a,Point b)
{
    if((a-O)%(b-O)==0)
        return O.sqdis_to(a)>O.sqdis_to(b);
    return (a-O)%(b-O)>0;
}

//------------求凸包前一定记得设置原点和极角排序！！-------

Point st[MAXN];
int tail=0;
void Graham(int n)
{
    tail=0;
    st[tail++]=O;
    for(int i=0;i<n;i++)
    {
        if(!(p[i]==O)){
            if(tail<2){
                st[tail++]=p[i];
            }
            else{
                bool ok=1;
                while((p[i]-st[tail-2])%(st[tail-1]-st[tail-2])==0)
                {
                    if(p[i].sqdis_to(st[tail-2])>st[tail-1].sqdis_to(st[tail-2])){
                        tail--;
                    }
                    else{
                        ok=0;
                        break;
                    }
                }
                if(!ok)continue;
                
                while((st[tail-1]-st[tail-2])%(p[i]-st[tail-2])<0)
                {
                    tail--;
                }
                st[tail++]=p[i];
            }
        }
        //        for(int i=0;i<tail;i++)
        //            st[i].debug();
        //        cout<<endl;
        
    }
}
//RC旋转卡壳
int rotating_caliper(Point v[],int n)
{
    int max_dis = 0;
    if (n == 2)
    {
        max_dis = v[0].sqdis_to(v[1]);
    }
    else
    {
        v[n]=v[0];
        int j = 2;
        for (int i = 0; i < n; ++i)
        {
            while (abs(v[i].cross_product(v[i + 1], v[j])) < abs(v[i].cross_product(v[i + 1], v[j + 1])))
            {
                j = (j + 1) % n;
            }
            max_dis = max(max_dis, max ( v[j].sqdis_to(v[i]), v[j].sqdis_to(v[i + 1] ) ) ) ;
        }
    }
    return max_dis;
}

