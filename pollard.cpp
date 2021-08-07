#include <bits/stdc++.h>

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
using namespace std;

int f(int x, int n, int k) {
    return (int) (((__int128) x * x + k) % n);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int pow(int a_, int n, int mod) {
    __int128 a = a_;
    __int128 ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return (int) ans;
}

bool miller_test(int n) {  // is prime
    if (n == 1)
        return false;
    if (n == 2 || n == 3)
        return true;

    int d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        r++, d /= 2;
    }

    int REPEAT = 20;
    for (int _ = 0; _ < REPEAT; _++) {
        int a = (int) rng() % (n - 3) + 2;
        __int128 x = pow(a, d, n);

        if (x == 1 || x == n - 1) {
            continue;
        }

        bool ok = true;
        for (int q = 0; q < r - 1; q++) {
            x = x * x % n;
            if (x == n - 1) {
                ok = false;
                break;
            }
        }
        if (ok)
            return false;
    }
    return true;
}

vector <int> pollard(int x) {
    if (miller_test(x))
        return {x};

    while (true) {
        int k = rng() % x;
        int a = rng() % x;
        int b = f(a, x, k);

        while (true) {
            if (a == b) {
                break;
            }

            int g = gcd(abs(a - b), x);
            if (g != 1) {
                vector<int> ans, ans1 = pollard(g), ans2 = pollard(x / g);
                merge(all(ans1), all(ans2), back_inserter(ans));
                return ans;
            }
            a = f(a, x, k);
            b = f(f(b, x, k), x, k);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i : pollard(n)) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
