#include <bits/stdc++.h>

#define double long double

using namespace std;

random_device rd;

const double EPS = 1e-9;

struct point {
    double x = 0, y = 0;

    point(double a, double b) : x(a), y(b) {};

    point() = default;

    double dist() {
        return sqrt(x * x + y * y);
    }

    double distsq() {
        return x * x + y * y;
    }

    point norm(double len = 0) {
        double ln = dist();
        return point(x * len / ln, y * len / ln);
    }

    point operator+(const point &A) {
        return point(x + A.x, y + A.y);
    }

    point operator-(const point &A) {
        return point(x - A.x, y - A.y);
    }
};

double dist(point A, point B) {
    return (A - B).dist();
}

struct circle {
    double x = 0, y = 0, r = 0;

    circle(double a, double b, double c) : x(a), y(b), r(c) {};

    circle() = default;

    point center() {
        return point(x, y);
    }

    bool checkpoint(point A) {
        return abs(dist(center(), A) * dist(center(), A) - r * r) < EPS;
    }
};

struct line {
    double a = 0, b = 0, c = 0;

    line(double x, double y, double z) : a(x), b(y), c(z) {};

    bool checkpoint(point A) {
        return abs(A.x * a + A.y * b + c) < EPS;
    }
};

double cross_prod(point A, point B) {
    return A.x * B.y - A.y * B.x;
}

double dot_prod(point A, point B) {
    return A.x * B.x + A.y * B.y;
}

point point_proj_on_line(point A, line l) {
    double len = abs(l.a * A.x + l.b * A.y + l.c) / sqrt(l.a * l.a + l.b * l.b);

    point normal = point(l.a, l.b).norm(len);
    if (l.checkpoint(A + normal))
        return A + normal;
    else if (l.checkpoint(A - normal))
        return A - normal;
    else
        assert(false);
    return point();
}

vector<point> circle_line_inters(circle A, line a) {
    point O = point_proj_on_line(A.center(), a);

    double ds = (O - A.center()).dist();
    if (ds > A.r) {
        return {};
    }

    point nw(-a.b, a.a);
    nw = nw.norm(sqrt(A.r * A.r - ds * ds));

    if (nw.dist() == 0)
        return {O - nw};
    else
        return {O - nw, O + nw};
}

vector<point> circle_inters(circle A, circle B) {
    if (A.x == B.x && A.y == B.y) {
        assert(A.r != B.r);  // circle are equal
        return {};
    }

    line rad_axis(2 * (A.x - B.x), 2 * (A.y - B.y),
                  (B.x * B.x + B.y * B.y - B.r * B.r) - (A.x * A.x + A.y * A.y - A.r * A.r));
    vector<point> ans = circle_line_inters(A, rad_axis);
    return ans;
}

double point_dist_on_circle(circle C, point A, point B) {
    double angle = abs(atan2(cross_prod(A - C.center(), B - C.center()), dot_prod(A - C.center(), B - C.center())));
    return min(angle * C.r, (2 * M_PI - angle) * C.r);
}

vector <point> points;
int n;

line midper(point A, point B) {
    point mid((A.x + B.x) / 2, (A.y + B.y) / 2);
    line ans(A.x - B.x, A.y - B.y, 0);
    ans.c = -ans.a * mid.x - ans.b * mid.y;
    return ans;
}

point line_inters(line x, line y) {
    double denom = x.a * y.b - x.b * y.a;
    assert(denom != 0);

    return point((y.c * x.b - x.c * y.b) / denom, (y.a * x.c - x.a * y.c) / denom);
}

circle find_common_circle(point a, point b, point c) {
    line x = midper(a, b), y = midper(a, c);

    if (x.a * y.b == x.b * y.a) {
        return circle(0, 0, 0);
    }

    point mid = line_inters(x, y);
    double dst = dist(a, mid);
    return circle(mid.x, mid.y, dst);
}

void make_ans(circle c1, circle c2) {
    vector <int> f, s;
    for (int i = 0; i < n; i++) {
        if (c1.checkpoint(points[i]))
            f.push_back(i + 1);
        if (c2.checkpoint(points[i]))
            s.push_back(i + 1);
    }
    cout << f.size() << " ";
    for (int i : f)
        cout << i << " ";
    cout << endl;
    cout << s.size() << " ";
    for (int i : s)
        cout << i << " ";
    cout << endl;
    exit(0);
}

void check(int a, int b, int c) {
    circle c1 = find_common_circle(points[a], points[b], points[c]);

    vector <point> second;
    for (int i = 0; i < n; i++) {
        if (!c1.checkpoint(points[i]))
            second.push_back(points[i]);
    }

    if (second.empty()) {
        make_ans(c1, circle(points[0].x, points[0].y, 0));
    } else if (second.size() == 1) {
        make_ans(c1, circle(second[0].x, second[0].y, 0));
    } else if (second.size() == 2) {
        make_ans(c1, circle((second[0].x + second[1].x) / 2, (second[0].y + second[1].y) / 2, dist(second[0], second[1]) / 2));
    } else {
        auto c2 = find_common_circle(second[0], second[1], second[2]);

        int cnt = 0;
        for (auto i : second) {
            cnt += c2.checkpoint(i);
        }
        if (cnt == second.size()) {
            make_ans(c1, c2);
        }
    }
}

signed main() {

    return 0;
}
