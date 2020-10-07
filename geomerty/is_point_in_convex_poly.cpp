#include <bits/stdc++.h>

#define int long long

using namespace std;

struct point {
    int x = 0, y = 0;
    point(int a, int b): x(a), y(b) {};
    point()= default;
};

bool is_in_triangle(const point &a, const point &b, const point &c, const point &d);

point operator-(const point& a, const point& b) {
    return point(b.x - a.x, b.y - a.y);
}

int vec_prod(const point& a, const point& b) {
    return a.x * b.y - a.y * b.x;
}


bool is_in_triangle(const point &a, const point &b, const point &c, const point &d) {
    int x = vec_prod(b - a, d - a);
    int y = vec_prod(c - b, d - b);
    int z = vec_prod(a - c, d - c);
    return !(min({x, y, z}) < 0 && max({x, y, z}) > 0);
}

signed main() {
    int n, q, k;
    cin >> n >> q >> k;

    vector <point> poly(n);
    for (auto& i : poly)
        cin >> i.x >> i.y;

    int ans = 0;
    while (q--) {
        point o;
        cin >> o.x >> o.y;

        int l = 1, r = n - 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (vec_prod(poly[m] - poly[0], o - poly[0]) > 0)
                l = m;
            else
                r = m;
        }
        if (is_in_triangle(poly[0], poly[l], poly[l + 1], o))
            ans++;
    }
    if (ans >= k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
