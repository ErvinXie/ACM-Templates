//
const double PI = acos(-1.0);
const double deg_rad = PI / 180.0;

class Qua {//Quaterion
public:
    Qua() {}

    Qua(double t, double x, double y, double z) : t(t), x(x), y(y), z(z) {}

    double t, x, y, z;

    Qua inv() {
        return Qua(t, -x, -y, -z);
    }

    friend Qua operator*(Qua l, Qua r) {
        Qua ans;
        ans.t = l.t * r.t - l.x * r.x - l.y * r.y - l.z * r.z;
        ans.x = l.t * r.x + l.x * r.t + l.y * r.z - l.z * r.y;
        ans.y = l.t * r.y + l.y * r.t + l.z * r.x - l.x * r.z;
        ans.z = l.t * r.z + l.z * r.t + l.x * r.y - l.y * r.x;
        return ans;
    }
};


class Point3 {
public:
    Point3() {}

    Point3(double x, double y, double z) : x(x), y(y), z(z) {}

    double x, y, z;

    double dis_to(Point3 b) {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
    }

    double length() {
        return dis_to(Point3(0, 0, 0));
    }

    friend Point3 operator+(Point3 l, Point3 r) {
        return Point3(l.x + r.x, l.y + r.y, l.z + r.z);
    };

    friend Point3 operator-(Point3 l, Point3 r) {
        return Point3(l.x - r.x, l.y - r.y, l.z - r.z);
    };

    Point3 operator*(double b) {
        return Point3(x * b, y * b, z * b);
    }

    friend double operator*(Point3 l, Point3 r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    };

    //叉乘
    Point3 cross(Point3 r) {
        return Point3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
    }

    Point3 rotate(Point3 axis, double theta) {
        //!!axis must be a unit vector
        Qua v(0, x, y, z);
        Qua q(cos(0.5 * theta), sin(0.5 * theta) * axis.x, sin(0.5 * theta) * axis.y, sin(0.5 * theta) * axis.z);
        v = (q * v) * q.inv();
        return Point3(v.x, v.y, v.z);
    }

    Point3 unit() {
        double len = length();
        return Point3(x / len, y / len, z / len);
    }

    void debug() {
        printf("(%lf,\t%lf,\t%lf)\n", x, y, z);
    }

};

class Segment {
public:

    Point3 u, v;

    Segment() {};

    Segment(Point3 u, Point3 v) : u(u), v(v) {};

    double dis_to(Point3 x) {
        if (((x - u) * (v - u)) * ((x - v) * (v - u)) <= 0) {
            return ((x - u).cross(v - u)).length() / (v - u).length();
        } else {
            return min(x.dis_to(u), x.dis_to(v));
        }
    }

    double dis_to(Segment b){
        if((v-u).cross(b.v-b.u).length()<=EPS){

        }
    }

};

class Point3r {
public:
    Point3r() {}

    Point3r(double phi, double theta, double r) : phi(phi), theta(theta), r(r) {}

    double phi, theta, r;//x-axis[-pi,pi] z-axis[0,pi] radius

    Point3 to_xyz() {
        Point3 re;
        re.z = cos(theta) * r;
        double xy = sin(theta) * r;
        re.x = cos(phi) * xy;
        re.y = sin(phi) * xy;
        return re;
    }
};

class Point3jw {
public:
    Point3jw() {}

    Point3jw(double lo, double la, double r) : lo(lo), la(la), r(r) {}

    double lo, la, r;//longitude[-180,180] latitude[-90,90] radius

    Point3 to_xyz() {
        Point3 re;
        re.z = cos((90 - la) * deg_rad) * r;
        double xy = sin((90 - la) * deg_rad) * r;
        re.x = cos(lo * deg_rad) * xy;
        re.y = sin(lo * deg_rad) * xy;
        return re;
    }
};