#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define endl "\n"
//#define len(x) (int) (x).size()
#define int long long

using namespace std;


const long double EPS = 1e-10;

struct Point {
    int x, y;

    Point(double x_, double y_) : x(x_), y(y_) {};

    Point() = default;

    long double len_sq() const { return x * x + y * y; };

    long double len() const { return sqrtl(x * x + y * y); };

    Point operator+(const Point &other) const {
        return Point(x + other.x, y + other.y);
    }

    Point &operator+=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point operator-(const Point &other) const {
        return Point(x - other.x, y - other.y);
    }

    Point &operator-=(const Point &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point operator*(const double &k) const {
        return Point(x * k, y * k);
    }

    Point &operator*=(const double &k) {
        x *= k;
        y *= k;
        return *this;
    }

    Point operator/(const double &k) const {
        return Point(x / k, y / k);
    }

    Point &operator/=(const double &k) {
        x /= k;
        y /= k;
        return *this;
    }

    long double dist(const Point &p) const { return (p - *this).len(); }

    long double dist_sq(const Point &p) const { return (p - *this).len_sq(); }

    bool operator<(const Point &p) const { return make_pair(x, y) < make_pair(p.x, p.y); }

    bool operator==(const Point &p) const { return make_pair(x, y) == make_pair(p.x, p.y); }

    Point norm() const { return Point(-y / len(), x / len()); }
};

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, Point p) {
    out << p.x << " " << p.y;
    return out;
}

int dot(const Point &a, const Point &b) {  // scalar, cos
    return a.x * b.x + a.y * b.y;
}

int cross(const Point &a, const Point &b) { // vec, sin
    return a.x * b.y - a.y * b.x;
}


struct Line {
    long double a, b, c;

    Line(const Point &a_, const Point &b_) : a(b_.y - a_.y),
                                             b(a_.x - b_.x),
                                             c((a_.y - b_.y) * a_.x + (b_.x - a_.x) * a_.y) {};

    Line(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {};

    Line() = default;

    long double point_val(const Point &p) const { return a * p.x + b * p.y + c; }

    long double ori_dist(const Point &p) const { return point_val(p) / sqrtl(a * a + b * b); }

    long double dist(const Point &p) const { return abs(point_val(p) / sqrtl(a * a + b * b)); }

    long double dist_sq(const Point &p) const { return point_val(p) * point_val(p) / (a * a + b * b); }

    bool is_paral(const Line &l) const { return a * l.b - l.a * b == 0; }

    Point inter(const Line &l) const {  // if 1 intersection point is guaranteed
        return Point(-(c * l.b - l.c * b) / (a * l.b - l.a * b),
                     -(a * l.c - l.a * c) / (a * l.b - l.a * b));
    }
};

istream &operator>>(istream &in, Line &l) {
    in >> l.a >> l.b >> l.c;
    return in;
}

ostream &operator<<(ostream &out, Line l) {
    out << l.a << " " << l.b << " " << l.c;
    return out;
}

bool point_on_line(const Point &a, const Point &b, const Point &p) { // p in (a, b)
    return abs(Line(a, b).point_val(p)) < EPS;
}

bool point_on_ray(const Point &a, const Point &b, const Point &p) { // p in [a, b)
    return point_on_line(a, b, p) && dot(b - a, p - a) >= 0;
}

bool point_on_seg(const Point &a, const Point &b, const Point &p) { // p in [a, b]
    return point_on_line(a, b, p) && dot(b - a, p - a) >= -EPS && dot(a - b, p - b) >= -EPS;
}

long double dist_ray_point(const Point &a, const Point &b, const Point &p) {
    if (dot(b - a, p - a) >= 0) {
        return Line(a, b).dist(p);
    } else {
        return a.dist(p);
    }
}

long double dist_seg_point(const Point &a, const Point &b, const Point &p) {
    if (dot(b - a, p - a) >= 0 && dot(a - b, p - b) >= 0) {
        return Line(a, b).dist(p);
    } else {
        return min(a.dist(p), b.dist(p));
    }
}

bool is_seg_int_1d(double a, double b, double c, double d) {
    return max(min(a, b), min(c, d)) <= min(max(a, b), max(c, d));
}

bool is_seg_int(const Point &a, const Point &b, const Point &c, const Point &d) {
    return is_seg_int_1d(a.x, b.x, c.x, d.x) &&
           is_seg_int_1d(a.y, b.y, c.y, d.y) &&
           cross(b - a, c - a) * cross(b - a, d - a) <= 0 &&
           cross(d - c, a - c) * cross(d - c, b - c) <= 0;
}


long double dist_segs(const Point &a, const Point &b, const Point &c, const Point &d) {
    if (is_seg_int(a, b, c, d)) {
        return 0;
    }
    return min({dist_seg_point(a, b, c),
                dist_seg_point(a, b, d),
                dist_seg_point(c, d, a),
                dist_seg_point(c, d, b)});
}

vector<Point> circ_point_tan(const Point &p0, const long double r, const Point &p1) {
    if (p0.dist_sq(p1) < r * r) {
        return {};
    } else if (p0.dist_sq(p1) == r * r) {
        return {p1};
    } else {
        cout << 2 << endl;
        long double hyp_sq = p0.dist_sq(p1) - r * r;
        long double p2p3l = r * sqrtl(hyp_sq) / p0.dist(p1);
        Point p3 = p1 + (p0 - p1) / p0.dist(p1) * sqrtl(hyp_sq - p2p3l * p2p3l);
        return {p3 + (p1 - p3).norm() * p2p3l, p3 - (p1 - p3).norm() * p2p3l};
    }
}

vector<Point> circ_line_int(const Point &p0, const long double r, Line l) {
    l.c = l.point_val(p0);
    Point p(-l.a * l.c / (l.a * l.a + l.b * l.b), -l.b * l.c / (l.a * l.a + l.b * l.b));
    if (l.c * l.c > r * r * (l.a * l.a + l.b * l.b) + EPS) {
        return {};
    } else if (abs(l.c * l.c - r * r * (l.a * l.a + l.b * l.b)) < EPS) {
        return {p + p0};
    } else {
        double d = r * r - l.c * l.c / (l.a * l.a + l.b * l.b);
        double mult = sqrtl(d / (l.a * l.a + l.b * l.b));
        return {Point(p.x + l.b * mult, p.y - l.a * mult) + p0,
                Point(p.x - l.b * mult, p.y + l.a * mult) + p0};
    }
}


vector<Point> circs_int(const Point &p0, const long double r0, Point p1, const long double r1) {
    if (p0 == p1) {
        if (r0 == r1) {
            return {Point(NAN, NAN)};
        } else {
            return {};
        }
    }
    p1 -= p0;
    auto ans = circ_line_int(Point(0, 0), r0,
                             Line(-2 * p1.x, -2 * p1.y, p1.x * p1.x + p1.y * p1.y + r0 * r0 - r1 * r1));
    for (auto &i: ans) {
        i += p0;
    }
    return ans;
}

bool is_point_in_poly(const Point &p0, const vector<Point> &poly) {
    Point p1 = Point(p0.x + 3e6, p0.y + 1);
    int cnt = 0;
    for (int i = 0; i < (int) poly.size(); i++) {
        if (point_on_seg(poly[i], poly[(i + 1) % poly.size()], p0)) {
            return true;
        }
        if (is_seg_int(p0, p1, poly[i], poly[(i + 1) % poly.size()])) {
            cnt++;
        }
    }
    return cnt % 2;
}


Point start(0, 0);

bool comp(const Point &a, const Point &b) {
    if (cross(a - start, b - start) != 0)
        return cross(a - start, b - start) > 0;
    return (a - start).len_sq() < (b - start).len_sq();
}


vector <Point> convex_hull(vector <Point> poly) {
    start = *min_element(poly.begin(), poly.end(),
                         [](Point &a, Point &b) { return make_pair(a.y, a.x) < make_pair(b.y, b.x); });
    sort(poly.begin(), poly.end(), comp);

    vector<Point> hull;
    for (auto &i: poly) {
        while (hull.size() > 1 && cross(hull.back() - hull[hull.size() - 2], i - hull[hull.size() - 2]) <= 0)
            hull.pop_back();
        hull.push_back(i);
    }
    return hull;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    return 0;
}
