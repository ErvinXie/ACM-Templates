const double eps = 1e-10;
inline int equal_to_0 (double a)
{
    if (a > eps) return 1;
    else if (a >= -eps) return 0;
    else return -1;
}
class Vector
{
public:
    double x, y;
    Vector (void) {}
    Vector (double x0, double y0) : x(x0), y(y0) {}
    double operator * (const Vector& a) const { return x * a.y - y * a.x; }
    double operator % (const Vector& a) const { return x * a.x + y * a.y; }
    Vector verti (void) const { return Vector(-y, x); }
    double length (void) const { return sqrt(x * x + y * y); }
    Vector adjust (double len)
    {
        double ol = len / length();
        return Vector(x * ol, y * ol);
    }
    Vector oppose (void) { return Vector(-x, -y); }
};
class point
{
public:
    double x, y;
    point (void) {}
    point (double x0, double y0) : x(x0), y(y0) {}
    Vector operator - (const point& a) const { return Vector(x - a.x, y - a.y); }
    point operator + (const Vector& a) const { return point(x + a.x, y + a.y); }
};
class segment
{
public:
    point a, b;
    segment (void) {}
    segment (point a0, point b0) : a(a0), b(b0) {}
    point intersect (const segment& s) const
    {
        Vector v1 = s.a - a, v2 = s.b - a, v3 = s.b - b, v4 = s.a - b;
        double s1 = v1 * v2, s2 = v3 * v4;
        double se = s1 + s2;
        s1 /= se, s2 /= se;
        return point(a.x * s2 + b.x * s1, a.y * s2 + b.y * s1);
    }
    point pverti (const point& p) const
    {
        Vector t = (b - a).verti();
        segment uv(p, p + t);
        return intersect(uv);
    }
    bool on_segment (const point& p) const
    {
        if (equal_to_0(min(a.x, b.x) - p.x) <= 0 && equal_to_0(p.x - max(a.x, b.x)) <= 0 &&
            equal_to_0(min(a.y, b.y) - p.y) <= 0 && equal_to_0(p.y - max(a.y, b.y)) <= 0) return true;
        else return false;
    }
};


double kuras_area (point a, point b, double cx, double cy,double radius)
{
    point ori(cx, cy);
    int sgn = equal_to_0((b - ori) * (a - ori));
    double da = (a - ori).length(), db = (b - ori).length();
    int ra = equal_to_0(da - radius), rb = equal_to_0(db - radius);
    double angle = acos(((b - ori) % (a - ori)) / (da * db));
    segment t(a, b); point h, u; Vector seg;
    double ans, dlt, mov, tangle;
    
    if (equal_to_0(da) == 0 || equal_to_0(db) == 0) return 0;
    else if (sgn == 0) return 0;
    else if (ra <= 0 && rb <= 0) return fabs((b - ori) * (a - ori)) / 2 * sgn;
    else if (ra >= 0 && rb >= 0)
    {
        h = t.pverti(ori);
        dlt = (h - ori).length();
        if (!t.on_segment(h) || equal_to_0(dlt - radius) >= 0)
            return radius * radius * (angle / 2) * sgn;
        else
        {
            ans = radius * radius * (angle / 2);
            tangle = acos(dlt / radius);
            ans -= radius * radius * tangle;
            ans += radius * sin(tangle) * dlt;
            return ans * sgn;
        }
    }
    else
    {
        h = t.pverti(ori);
        dlt = (h - ori).length();
        seg = b - a;
        mov = sqrt(radius * radius - dlt * dlt);
        seg = seg.adjust(mov);
        if (t.on_segment(h + seg)) u = h + seg;
        else u = h + seg.oppose();
        if (ra == 1) swap(a, b);
        ans = fabs((a - ori) * (u - ori)) / 2;
        tangle = acos(((u - ori) % (b - ori)) / ((u - ori).length() * (b - ori).length()));
        ans += radius * radius * (tangle / 2);
        return ans * sgn;
    }
}