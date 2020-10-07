#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const double EPS = 1e-9;

struct point {
    double x = 0, y = 0;
    point(double a, double b): x(a), y(b) {};
    point()= default;

    double dist() {
        return sqrt(x * x + y * y);
    }

    double distsq() {
        return x * x + y * y;
    }

    point norm(double len=0) {
        double ln = dist();
        return point(x * len / ln, y * len / ln);
    }

    point operator+(const point& A) {
        return point(x + A.x, y + A.y);
    }
    point operator-(const point& A) {
        return point(x - A.x, y - A.y);
    }
};

struct cycle {
    int x = 0, y = 0, r = 0;
    cycle(int a, int b, int c): x(a), y(b), r(c){};
    cycle()= default;

    point center() {
        return point(x, y);
    }
};

struct line {
    double a = 0, b = 0, c = 0;
    line(double x, double y, double z): a(x), b(y), c(z) {};

    bool checkpoint(point A) {
        return abs(A.x * a + A.y * b + c) < EPS;
    }
};


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

vector <point> cycle_line_inters(cycle A, line a) {
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

vector <point> cycle_inters(cycle A, cycle B) {
    if (A.x == B.x && A.y == B.y) {
        assert(A.r != B.r);  // cycle are equal
        return {};
    }

    line rad_axis(2 * (A.x - B.x), 2 * (A.y - B.y), (B.x * B.x + B.y * B.y - B.r * B.r) - (A.x * A.x + A.y * A.y - A.r * A.r));
    vector <point> ans = cycle_line_inters(A, rad_axis);
    return ans;
}

signed main() {
    cycle A, B;

    cin >> A.x >> A.y >> A.r >> B.x >> B.y >> B.r;

    if (A.x == B.x && A.y == B.y) {
        if (A.r == B.r) {
            cout << 3 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    }

    vector <point> ans = cycle_inters(A, B);
    cout << fixed << setprecision(20) << ans.size() << endl;
    for (auto& i : ans)
        cout << i.x << " " << i.y << endl;
    return 0;
}
