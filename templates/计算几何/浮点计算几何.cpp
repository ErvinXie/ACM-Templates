//浮点计算几何
int MAXN = 1e5 + 4;
double PI = acos(-1.0);
double INF = 1e100;
double deg_to_rad = 2 * PI / 360.0;
double EPS = 1e-6;

int sgn(double x) {
    if (abs(x) < EPS)
        return 0;
    else if (x < 0)
        return -1;
    else
        return 1;
}

struct Point {
    double x, y;

    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    double sqdis_to(Point b) {//未开平方的距离
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }

    double dis_to(Point b) {
        return sqrt(sqdis_to(b));
    }

    double length() {
        return dis_to(Point(0, 0));
    }

    friend Point operator+(Point a, Point b) {
        return Point(a.x + b.x, a.y + b.y);
    }

    friend Point operator-(Point a, Point b) {
        return Point(a.x - b.x, a.y - b.y);
    }

    friend Point operator*(double t, Point a) {
        return Point(t * a.x, t * a.y);
    }

    friend Point operator/(Point a, double t) {
        return Point(a.x / t, a.y / t);
    }

    friend double operator*(Point a, Point b) {
        return a.x * b.x + a.y * b.y;
    }

    bool operator==(Point b) {
        if (sgn(x - b.x) == 0 && sgn(y - b.y) == 0)
            return true;
        return false;
    }

    Point unit() {//单位向量，注意不能为0
        return (*this) / length();
    }

    double cross(Point b) {
        return x * b.y - y * b.x;
    }

    double cross(Point b, Point c) {
        return (b.x - x) * (c.y - y) - (b.y - y) * (c.x - x);
    }

    Point complex_mul(Point b) {
        return Point(x * b.x - y * b.y, x * b.y + y * b.x);
    }

    Point rotate(double rad) {
        return complex_mul(Point(cos(rad), sin(rad)));
    }

    double theta() {
        return atan2(y, x);
    }

    void debuge() {
        printf("(%lf %lf)\n", x, y);
    }
};


Point circumcenter(Point A, Point B, Point C) {//三角形外心
    Point ret;
    double a1 = B.x - A.x, b1 = B.y - A.y, c1 = (a1 * a1 + b1 * b1) / 2;
    double a2 = C.x - A.x, b2 = C.y - A.y, c2 = (a2 * a2 + b2 * b2) / 2;
    double d = a1 * b2 - a2 * b1;
    ret.x = A.x + (c1 * b2 - c2 * b1) / d;
    ret.y = A.y + (a1 * c2 - a2 * c1) / d;
    return ret;
}

double min_cover_circle(Point p[], Point &c, int n) {//最小覆盖圆 c为圆心，r为半径
    double r;
    random_shuffle(p, p + n);
    c = p[0];
    r = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].dis_to(c) > r + EPS){
            c = p[i];//第一个点
            r = 0;
            for (int j = 0; j < i; j++) {
                if (p[j].dis_to(c) > r + EPS){
                    //第二个点
                    c.x = (p[i].x + p[j].x) / 2;
                    c.y = (p[i].y + p[j].y) / 2;
                    r = p[j].dis_to(c);
                    for (int k = 0; k < j; k++) {
                        //第三个点
                        if (p[k].dis_to(c) > r + EPS){   //求外接圆圆心，三点必不共线
                            c = circumcenter(p[i], p[j], p[k]);
                            r = p[i].dis_to(c);
                        }
                    }
                }
            }
        }
    }
    return r;
}

struct Polygon{



};