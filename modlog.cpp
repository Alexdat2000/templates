#include <bits/stdc++.h>

#define int long long
#define all(x) (x).begin(), (x).end()
using namespace std;


vector <int> prime_divs(int n) {
    vector <int> ans;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            ans.push_back(i);

        while (n % i == 0) {
            n /= i;
        }
    }
    if (n != 1)
        ans.push_back(n);
    return ans;
}

int pow(int a_, int n, int mod) {
    __int128 a = a_, ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return (int) ans;
}

int primitive_root(int x) {
    vector <int> divs = prime_divs(x - 1);

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

int modlog(int a, int b, int mod) {  // return x: a ^ x = b (mod)
    int n = (int) sqrtl(mod) + 1;

    unordered_map <int, int> rems;
    rems.reserve(n);
    __int128 now = 1;
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

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);

    int a, b, n;
    cin >> a >> b >> n;
    cout << modlog(a, b, n) << endl;
    return 0;
}
