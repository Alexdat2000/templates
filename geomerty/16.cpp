#include <bits/stdc++.h>

#define double long double

using namespace std;

const double EPS = 1e-10;

struct point {
    double x, y;

    point(double a, double b) : x(a), y(b) {};

    point() = default;

    point operator-(point B) {
        return point(x - B.x, y - B.y);
    }
};

struct line {
    double a, b, c;

    line(point A, point B) {
        a = A.y - B.y;
        b = B.x - A.x;
        c = A.x * B.y - A.y * B.x;
    }

    point nor() {
        point x(-b, a);
        double ln = sqrtl(x.x * x.x + x.y * x.y);
        x.x /= ln, x.y /= ln;
        return x;
    }
};

double cross_prod(point A, point B) {  // [a, b]
    return A.x * B.y - A.y * B.x;
}

double dot_prod(point A, point B) {  // (a, b)
    return A.x * B.x + A.y * B.y;
}


bool point_on_ray(point A, point B, point C) {
    return dot_prod(A - B, C - B) >= -EPS;
}

double dist_point_point(point A, point B) {
    return sqrtl((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double dist_point_line(point A, point C, point D) {
    line l = line(C, D);
    return abs(A.x * l.a + A.y * l.b + l.c) / sqrtl(l.a * l.a + l.b * l.b);
}

point inter(line l1, line l2) {
    return point(-(l1.c * l2.b - l2.c * l1.b) / (l1.a * l2.b - l1.b * l2.a),
                 -(l1.a * l2.c - l2.a * l1.c) / (l1.a * l2.b - l1.b * l2.a));
}



double dist_point_seg(point A, point C, point D) {
    if (point_on_ray(A, C, D) && point_on_ray(A, D, C)) {
        return dist_point_line(A, C, D);
    }
    return min(dist_point_point(A, C), dist_point_point(A, D));
}

double dist_point_ray(point A, point C, point D) {
    if (point_on_ray(A, C, D)) {
        return dist_point_line(A, C, D);
    }
    return min(dist_point_point(A, C), dist_point_point(A, D));
}

double dist_seg_seg(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        point X = inter(l1, l2);
        if (point_on_ray(X, A, B) && point_on_ray(X, B, A) &&
            point_on_ray(X, C, D) && point_on_ray(X, D, C)) {
            return 0;
        }
    }

    return min({dist_point_seg(C, A, B), dist_point_seg(D, A, B), dist_point_seg(A, C, D),
                dist_point_seg(B, C, D)});
}

double dist_seg_ray(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        point X = inter(l1, l2);
        if (point_on_ray(X, A, B) && point_on_ray(X, B, A) &&
            point_on_ray(X, C, D)) {
            return 0;
        }
    }

    return min({dist_point_seg(C, A, B), dist_point_seg(D, A, B), dist_point_ray(A, C, D),
                dist_point_ray(B, C, D)});
}

double dist_seg_line(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        point X = inter(l1, l2);
        if (point_on_ray(X, A, B) && point_on_ray(X, B, A)) {
            return 0;
        }
    }

    return min({dist_point_seg(C, A, B), dist_point_seg(D, A, B), dist_point_line(A, C, D),
                dist_point_line(B, C, D)});
}

double dist_ray_ray(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        point X = inter(l1, l2);
        if (point_on_ray(X, A, B) && point_on_ray(X, C, D)) {
            return 0;
        }
    }

    return min({dist_point_ray(C, A, B), dist_point_ray(D, A, B), dist_point_ray(A, C, D),
                dist_point_ray(B, C, D)});
}

double dist_ray_line(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        point X = inter(l1, l2);
        if (point_on_ray(X, A, B)) {
            return 0;
        }
    }

    return min({dist_point_ray(C, A, B), dist_point_ray(D, A, B), dist_point_line(A, C, D),
                dist_point_line(B, C, D)});
}

double dist_line_line(point A, point B, point C, point D) {
    line l1 = line(A, B);
    line l2 = line(C, D);

    if (l1.a * l2.b - l1.b * l2.a != 0) {
        return 0;
    }

    return min({dist_point_line(C, A, B), dist_point_line(D, A, B), dist_point_line(A, C, D),
                dist_point_line(B, C, D)});
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    point A, B, C, D;
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;

    cout << fixed << setprecision(10);

    cout << dist_point_point(A, C) << endl;
    cout << dist_point_seg(A, C, D) << endl;
    cout << dist_point_ray(A, C, D) << endl;
    cout << dist_point_line(A, C, D) << endl;
    cout << dist_point_seg(C, A, B) << endl;
    cout << dist_seg_seg(A, B, C, D) << endl;
    cout << dist_seg_ray(A, B, C, D) << endl;
    cout << dist_seg_line(A, B, C, D) << endl;
    cout << dist_point_ray(C, A, B) << endl;
    cout << dist_seg_ray(C, D, A, B) << endl;
    cout << dist_ray_ray(A, B, C, D) << endl;
    cout << dist_ray_line(A, B, C, D) << endl;
    cout << dist_point_line(C, A, B) << endl;
    cout << dist_seg_line(C, D, A, B) << endl;
    cout << dist_ray_line(C, D, A, B) << endl;
    cout << dist_line_line(A, B, C, D) << endl;
    return 0;
}
