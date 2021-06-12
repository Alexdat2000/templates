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

int pow(int a, int n, int mod) {
    int ans = 1;
    while (n) {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
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

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(nullptr);

    int p;
    cin >> p;
    cout << primitive_root(p) << endl;
    return 0;
}