#include <bits/stdc++.h>

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
using namespace std;


int pow(int a, int n, int mod) {
    int ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return (int) ans;
}


int modlog(int a, int b, int mod) {  // return x: a ^ x = b (mod)
    int n = (int) sqrtl(mod) + 1;

    unordered_map <int, int> rems;
    rems.reserve(n);
    int now = 1;
    for (int i = 0; i < n; i++) {
        rems[now] = i;
        now = now * a % mod;
    }

    now = b;
    int mult = pow(pow(a, n, mod), mod - 2, mod);
    for (int i = 0; i < n; i++) {
        if (rems.count(now)) {
            return i * n + rems[now];
        }
        now = now * mult % mod;
    }
    return -1;
}

int primitive_root(int x) {
    vector <int> divs;
    int n = x - 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            divs.push_back(i);

        while (n % i == 0) {
            n /= i;
        }
    }
    if (n != 1)
        divs.push_back(n);


    for (int g = 2;; g++) {
        bool ok = true;
        for (int i : divs) {
            if (pow(g, (x - 1) / i, x) == 1) {
                ok = false;
                break;
            }
        }
        if (ok)
            return g;
    }
}

array <int, 3> extended_gcd(int a, int b) {
    if (a == 0) {
        return {b, 0, 1};
    }

    auto [d, x, y] = extended_gcd(b % a, a);
    return {d, y - (b / a) * x, x};
}

pair <int, int> dioph(int a, int b, int c, int mod) {  // return [x, y]: ax + by = c (mod)
    auto [g, x, y] = extended_gcd(a, b);
    if (c % g != 0) {
        return {-1, -1};
    }

    if (x < 0) {
        int step = b / g;
        int steps = (-x + step - 1) / step;
        x += step * steps;
        y -= (a / g) * steps;
    }
    return {x * (c / g), y * (c / g)};
}

int modroot(int a, int b, int mod) {  // return x: x ^ a = b (mod)
    int g = primitive_root(mod);
    int j = modlog(g, a, mod);
    auto [i, _] = dioph(b, mod - 1, j, mod);
    if (i == -1) {
        return -1;
    } else {
        return pow(g, i, mod);
    }
}

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int a, b, n;
        cin >> a >> b >> n;
        cout << modroot(a, b, n) << endl;
    }
    return 0;
}
