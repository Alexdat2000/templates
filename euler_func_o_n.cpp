//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;


const int N = 1e8 + 100;
int p[N], phi[N];
vector<int> primes;


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i < N; i++) {
        if (p[i] == 0) {
            p[i] = i;
            primes.push_back(i);
        }
        for (int x : primes) {
            if (x > p[i] || 1LL * x * i >= N)
                break;
            p[x * i] = x;
        }
    }

    int n;
    cin >> n;
    long long sm = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (p[i] == i) {
            phi[i] = i - 1;
        } else {
            if (i / p[i] % p[i] == 0) {
                phi[i] = (int) ((long long) phi[p[i]] * phi[i / p[i]] * p[i] / (p[i] - 1));
            } else {
                phi[i] = phi[p[i]] * phi[i / p[i]];
            }
        }
        sm += phi[i];
        if (i % 100 == 0) {
            cout << sm << " ";
            sm = 0;
        }
    }
    if (n % 100 != 0)
        cout << sm << endl;
    return 0;
}
