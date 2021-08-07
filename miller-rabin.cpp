#include <bits/stdc++.h>

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        if (miller_test(n)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
