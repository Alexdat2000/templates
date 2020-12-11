#include <bits/stdc++.h>
#define double long double
#define int long long

using namespace std;

struct point {
    int x = 0, y = 0;

    point(int x_, int y_) : x(x_), y(y_) {};

    point() = default;

    int sq_len() {
        return x * x + y * y;
    }
};

point operator+(const point &a, const point &b) {
    return point(a.x + b.x, a.y + b.y);
}

point operator-(const point &a, const point &b) {
    return point(a.x - b.x, a.y - b.y);
}

point operator*(const point& a, int k) {
    return point(a.x * k, a.y * k);
}

point operator/(const point& a, int k) {
    return point(a.x / k, a.y / k);
}


int vmul(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

point start;

bool comp(const point& a, const point& b) {
    if (vmul(a - start, b - start) != 0)
        return vmul(a - start, b - start) > 0;
    return (a - start).sq_len() < (b - start).sq_len();
}

double dist(point A, point B) {
    return sqrtl((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector <point> poly(n);
    for (auto& i : poly)
        cin >> i.x >> i.y;

    start = *min_element(poly.begin(), poly.end(), [](point& a, point& b) { return make_pair(a.y, a.x) < make_pair(b.y, b.x);});
    sort(poly.begin(), poly.end(), comp);

    vector <point> hull;
    for (auto& i : poly) {
        while (hull.size() > 1 && vmul(hull.back() - hull[hull.size() - 2], i - hull[hull.size() - 2]) <= 0)
            hull.pop_back();
        hull.push_back(i);
    }

    return 0;
}
