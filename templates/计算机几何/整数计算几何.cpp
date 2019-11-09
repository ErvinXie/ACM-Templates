//整数计算几何
#include <cmath>

typedef long long ll;
const double PI = acos(-1.0);


struct Point {
    int x, y;

    //按x坐标排序
    bool operator<(const Point &b) const { return x < b.x; }

    Point() {}

    Point(int x, int y) : x(x), y(y) {}


    //平方距离
    ll sqdis_to(const Point &b) const {
        return (ll) (x - b.x) * (ll) (x - b.x) + (ll) (y - b.y) * (ll) (y - b.y);
    }

    //浮点距离
    double dis_to(const Point &b) const {
        return sqrt(sqdis_to(b));
    }

    //模长
    double length() {
        return sqrt(sqdis_to(Point(0, 0)));
    }

    //加减法
    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    //对位乘积
    Point digit_product(const Point &b) const {
        return Point(x * b.x, y * b.y);
    }

    //点乘 内积
    ll operator*(const Point &b) const {
        return (ll) x * (ll) b.x + (ll) y * (ll) b.y;
    }


    //叉积
    ll cross_product(const Point &b) const {
        return (ll) x * (ll) b.y - (ll) y * (ll) b.x;
    }

    //以此点为原点的叉积
    ll cross_product(const Point &a, const Point &b) const {
        return (a - *this).cross_product(b - *this);
    }

    //复数乘积
    Point complex_product(const Point &b) const {
        return Point(x * b.x - y * b.y, x * b.y + y * b.x);
    }

    friend Point operator*(const Point &a, int b) {
        return Point(a.x * b, a.y * b);
    }

    friend Point operator/(const Point &a, int b) {
        return Point(a.x / b, a.y / b);
    }

    //相等
    bool operator==(const Point &b) const {
        if (x == b.x && y == b.y)
            return true;
        else
            return false;
    }

    //于x抽正方向的夹角[0,2*PI)
    double theta() {//和原点连线与x轴正方向的夹角，0～2*PI
        return atan2(y,x);
    }

    bool point_in_polygen(Point p[], int n) const {
        //点需要逆时针排列
        //是否被包含在凸包内部，包含边界
        if (n == 1) {
            if (*this == p[0])
                return true;
            else
                return false;
        } else if (n == 2) {
            if (this->cross_product(p[0], p[1]) == 0 && (p[0] - *this) * (p[1] - *this) <= 0)
                return true;
            else
                return false;
        } else {
            for (int i = 0; i < n; i++) {
                if (p[i].cross_product(*this, p[(i + 1) % n]) > 0) {
                    return false;
                }
            }
            return true;
        }
    }

    friend bool seg_cross(Point &a,Point &b,Point &c,Point &d){
        if(a.cross_product(b,c)*a.cross_product(b,d)<0
           &&c.cross_product(d,a)*c.cross_product(d,b)<0){
            return true;
        }else{
            if(c.cross_product(a,b)==0&&(a-c)*(b-c)<=0)
                return true;
            if(d.cross_product(a,b)==0&&(a-d)*(b-d)<=0)
                return true;
            if(a.cross_product(c,d)==0&&(c-a)*(d-a)<=0)
                return true;
            if(b.cross_product(c,d)==0&&(c-b)*(d-b)<=0)
                return true;
        }
        return false;
    }

    void debug() {
        printf("(%d %d)\n", x, y);
    }

    void debugl() {
        printf("(%d %d)", x, y);
    }
};


//极角排序
Point O = Point(0, 0);//原点
bool rotate_cmp(Point a, Point b) {

    if ((a - O).cross_product(b - O) == 0)//如果两个点幅角相等，则近点靠前,近点靠前才能保证原点在第一个
        return O.sqdis_to(a) < O.sqdis_to(b);
    else
        return O.cross_product(a, b) > 0;
}

//Graham扫描法 O(n*log(n))
struct Graham {
    Point p[MAXN];//数据
    Point st[MAXN];//点栈
    int tail = 0;

    //solve之后：st中的点就是凸包，tail即是凸包中点的个数
    void solve(int n) {
        //找到y最小点
        int x = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].y < p[x].y || (p[i].y == p[x].y && p[i].x < p[x].x)) {
                x = i;
            }
        }
        //极角排序
        O = p[x];
        sort(p, p + n, rotate_cmp);

        //开始Graham
        tail = 0;
        st[tail++] = p[0];
        for (int i = 1; i < n; i++) {
            if (tail < 2) {
                //不能保证第二个点一定是凸包顶点
                st[tail++] = p[i];
            }
            while (st[tail - 2].cross_product(p[i], st[tail - 1]) >= 0 && tail >= 2) {
                tail--;
            }
            st[tail++] = p[i];
        }
    }

    bool point_in(Point &b) {
        return b.point_in_polygen(st, tail);
    }

    bool intersect(Graham &b) {
        //是否和另一个凸包相交

        //判断任意两边是否跨立
        //这里改成 >=2 会wa很奇怪
        if (tail == 2 && b.tail == 2)
            for (int i = 0; i < tail; i++) {
                for (int j = 0; j < b.tail; j++) {
                    if (st[i].cross_product(st[(i + 1) % tail], b.st[j]) *
                        st[i].cross_product(st[(i + 1) % tail], b.st[(j + 1) % b.tail]) < 0
                        && b.st[j].cross_product(b.st[(j + 1) % b.tail], st[i]) *
                           b.st[j].cross_product(b.st[(j + 1) % b.tail], st[(i + 1) % tail]) < 0)
                        return true;
                }
            }

        //其他情况相互判断有没有在其内部
        for (int i = 0; i < tail; i++) {
            if (b.point_in(st[i])) {
                return true;
            }
        }
        for (int i = 0; i < b.tail; i++) {
            if (point_in(b.st[i])) {
                return true;
            }
        }
        return false;
    }

    //RC旋转卡壳
    double rotating_caliper() {
        ll max_dis = 0;
        if (tail == 2) {
            max_dis = st[0].sqdis_to(st[1]);
        } else {
            st[tail] = st[0];
            int j = 2;
            for (int i = 0; i < tail; i++) {
                while (abs(st[i].cross_product(st[i + 1], st[j])) < abs(st[i].cross_product(st[i + 1], st[j + 1]))) {
                    j = (j + 1) % tail;
                }
                max_dis = max(max_dis, max(st[j].sqdis_to(st[i]), st[j].sqdis_to(st[i + 1])));
            }
        }
        return sqrt(max_dis);
    }

    void debug() {
        for (int i = 0; i < tail; i++)
            st[i].debug();
        cout << endl;
    }
};



